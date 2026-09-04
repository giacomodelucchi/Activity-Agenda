#include "VistaElencoAttivita.h"

#include <QApplication>
#include <QBrush>           // per la colorazione delle righe della tabella
#include <QDateTime>
#include <QLabel>
#include <QLineEdit>
#include <QLocale>          // per la formattazione della data e dell'ora
#include <QMenu>
#include <QPushButton>
#include <QStyle>
#include <QToolButton>
#include <QTreeWidget>      // per la tabella delle attività
#include <QTreeWidgetItem>  
#include <QHeaderView>      // per la gestione delle intestazioni della tabella
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "../core/gerarchia/attivita.h"
#include "../core/gerarchia/evento.h"
#include "../core/gerarchia/eventoRicorrente.h"
#include "../core/gerarchia/lista.h"

class OrdinalTreeWidgetItem : public QTreeWidgetItem {
public:
    using QTreeWidgetItem::QTreeWidgetItem;

    bool operator<(const QTreeWidgetItem& other) const override {
        if (const QTreeWidget* tree = treeWidget()) {
            int column = tree->sortColumn();
            if (column == 2) {
                QDateTime a = data(column, Qt::UserRole).toDateTime();
                QDateTime b = other.data(column, Qt::UserRole).toDateTime();
                if (a != b) return a < b;
            } else {
                QString a = text(column);
                QString b = other.text(column);
                if (a != b) return a < b;
            }
            QDateTime a = data(2, Qt::UserRole).toDateTime();
            QDateTime b = other.data(2, Qt::UserRole).toDateTime();
            if (a != b) return a < b;
            return text(0) < other.text(0);
        }
        return QTreeWidgetItem::operator<(other);   //se non c'è un QTreeWidget associato, usa l'ordinamento predefinito
    }
};

VistaElencoAttivita::VistaElencoAttivita(QWidget* parent)
    : QWidget(parent)
{
    auto mainLayout = new QVBoxLayout(this);
    auto* topLayout = new QHBoxLayout();

    search = new QLineEdit(this);
    search->setPlaceholderText(tr("Cerca..."));
    
    addButton = new QToolButton(this);
    addButton->setText(tr("Aggiungi"));
    addButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogNewFolder));
    addButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addButton->setPopupMode(QToolButton::InstantPopup); 
    QMenu* addMenu = new QMenu(this);
    addMenu->addAction(style()->standardIcon(QStyle::SP_FileIcon), tr("Evento"), this, [this](){ onAddRequested(VistaElencoAttivita::TipoEvento); });
    addMenu->addAction(style()->standardIcon(QStyle::SP_DialogOpenButton), tr("Evento ricorrente"), this, [this](){ onAddRequested(VistaElencoAttivita::TipoEventoRicorrente); });
    addMenu->addAction(style()->standardIcon(QStyle::SP_DirIcon), tr("Lista"), this, [this](){ onAddRequested(VistaElencoAttivita::TipoLista); });
    addButton->setMenu(addMenu);

    deleteButton = new QPushButton(style()->standardIcon(QStyle::SP_TrashIcon), tr("Elimina"), this);
    deleteButton->setEnabled(false);
    
    topLayout->addWidget(search);
    topLayout->addStretch();
    topLayout->addWidget(addButton);
    topLayout->addWidget(deleteButton);

    //lista delle attività, implementata come QTreeWidget per permettere la visualizzazione di più colonne e la selezione multipla
    list = new QTreeWidget(this);   
    list->setColumnCount(4);
    list->setHeaderLabels({tr("Titolo"), tr("Luogo"), tr("Orario"), tr("Tipo")});
    list->setRootIsDecorated(false);
    list->setSortingEnabled(true);
    list->setAlternatingRowColors(true);
    list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    list->header()->setSectionsClickable(true);
    list->header()->setSectionResizeMode(QHeaderView::Stretch);
    list->setStyleSheet(
        "QTreeWidget { background: white; border: none; }"
        "QTreeWidget::item:selected { background: #c8dcff; }");

    emptyStateLabel = new QLabel(tr("Nessuna attività disponibile. Aggiungi o carica un file JSON."), this);
    emptyStateLabel->setAlignment(Qt::AlignCenter);
    emptyStateLabel->setVisible(false);

    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(list);
    mainLayout->addWidget(emptyStateLabel);

    connect(list, &QTreeWidget::itemClicked, this, &VistaElencoAttivita::onItemClicked);
    connect(search, &QLineEdit::textChanged, this, &VistaElencoAttivita::onSearchTextChanged);
    connect(deleteButton, &QPushButton::clicked, this, &VistaElencoAttivita::onDeleteSelected);
    connect(list, &QTreeWidget::itemSelectionChanged, this, [this]() {
        deleteButton->setEnabled(!selectedActivityIds().isEmpty());
    });
}

void VistaElencoAttivita::setMemoria(Memoria* m)
{
    memoria = m;
    refreshList();
}

// Aggiorna la lista delle attività visualizzate, viene chiamata dopo ogni modifica alla memoria o al filtro di ricerca
void VistaElencoAttivita::refreshList()
{
    list->clear();
    if (!memoria) return;

    unsigned int visibleCount = 0;
    const QDateTime now = QDateTime::currentDateTime();

    //ricerca della prossima data in cui verrà svolta un'attività
    QDate prossimaData;
    memoria->perOgniAttivita([now, &prossimaData](const Attivita& a) {
        QDateTime dt = a.getOrario();

        if (!dt.isValid())
            return;

        // ignora le attività già passate
        if (dt < now)
            return;

        if (!prossimaData.isValid() || dt.date() < prossimaData)
            prossimaData = dt.date();
    });

    memoria->perOgniAttivita([this, &visibleCount, now, prossimaData](const Attivita& a){
        auto placeholder = [this](const QString& value){      
            return value.trimmed().isEmpty() ? tr("Non specificato") : value;   // se il campo è vuoto, mostra "Non specificato"
        };

        //applicazione valori di default generici per tutte le attività
        QString titolo = placeholder(a.getTitolo());
        QString luogo = placeholder(a.getLuogo());
        QString orario = tr("Non specificato");
        QString tipo = tr("Attività");
        QColor bgColor = QColor(255, 240, 220);

        //colorazione e tipo specifici a seconda del tipo di attività, tramite il Visitor
        tipoAttivita.clear();
        coloreAttivita = QColor();
        a.accept(*this);
        if (!tipoAttivita.isEmpty()) tipo = tipoAttivita;
        if (coloreAttivita.isValid()) bgColor = coloreAttivita;

        OrdinalTreeWidgetItem* item = new OrdinalTreeWidgetItem(list);  // OrdinalTreeWidgetItem per ordinamento personalizzato

        QDateTime orarioQt = a.getOrario(); 
        if (orarioQt.isValid()) {
            orario = QLocale::system().toString(orarioQt, QLocale::ShortFormat);
        }

        // Imposta i valori delle colonne della tabella per l'attività corrente
        item->setText(0, titolo);   
        item->setText(1, luogo);
        item->setText(2, orario);
        item->setText(3, tipo);
        item->setData(0, Qt::UserRole, static_cast<int>(a.getId()));    // inserisce l'ID dell'attività come dato utente nella prima colonna
        item->setData(2, Qt::UserRole, orarioQt);

        // personalizzazione delle righe della tabella a seconda del tipo di attività e dello stato (passata, prossima, ecc.)
        for (int col = 0; col < list->columnCount(); ++col) {
            item->setBackground(col, bgColor);
        }
        if (orarioQt.isValid()) {
            if (orarioQt < now) {                                       // attività passata
                for (int col = 0; col < list->columnCount(); ++col)
                    item->setForeground(col, Qt::lightGray);
            }
            else if (orarioQt.date() == prossimaData) {                 // attività del prossimo giorno utile
                for (int col = 0; col < list->columnCount(); ++col)
                    item->setBackground(col, QColor(255, 250, 190));
                QFont f = item->font(0);
                f.setBold(true);
                item->setFont(0, f);    
            }
        }
        visibleCount++;         // serve a contare quante attività sono visibili dopo il filtraggio
    });

    emptyStateLabel->setVisible(visibleCount == 0); // mostra il messaggio di stato vuoto se non ci sono attività 
    list->setVisible(visibleCount > 0);             // rende visibile la tabella solo se ci sono attività
    deleteButton->setEnabled(false);                
}

// chiamata quando un elemento della tabella viene cliccato
void VistaElencoAttivita::onItemClicked(QTreeWidgetItem* item, int)
{
    if (!item) return;
    unsigned int id = static_cast<unsigned int>(item->data(0, Qt::UserRole).toInt());
    emit activitySelected(id);
}

// chiamato quando l'utente clicca sul pulsante "Elimina" dopo aver selezionato una o più attività nella tabella
void VistaElencoAttivita::onDeleteSelected()
{
    QVector<unsigned int> ids = selectedActivityIds();
    if (ids.isEmpty()) return;
    emit deleteSelectedRequested(ids);
}

// chiamata quando l'utente clicca sul pulsante "Aggiungi" e seleziona un tipo di attività da aggiungere
void VistaElencoAttivita::onAddRequested(int type)
{
    emit addRequested(type);
}

// chiamata quando il testo della barra di ricerca cambia
void VistaElencoAttivita::onSearchTextChanged(const QString& text)
{
    const QString filtro = text.trimmed();
    int visibleCount = 0;
    for (int i = 0; i < list->topLevelItemCount(); ++i) {
        QTreeWidgetItem* it = list->topLevelItem(i);
        bool match = filtro.isEmpty() || it->text(0).contains(filtro, Qt::CaseInsensitive)
            || it->text(1).contains(filtro, Qt::CaseInsensitive)
            || it->text(2).contains(filtro, Qt::CaseInsensitive)
            || it->text(3).contains(filtro, Qt::CaseInsensitive);
        it->setHidden(!match);
        if (match) visibleCount++;
    }
    emptyStateLabel->setVisible(visibleCount == 0);
    list->setVisible(visibleCount > 0);
}

QVector<unsigned int> VistaElencoAttivita::selectedActivityIds() const
{
    QVector<unsigned int> ids;  // conterrà gli ID delle attività selezionate nella tabella
    const auto selectedItems = list->selectedItems();
    for (QTreeWidgetItem* item : selectedItems) {
        ids.append(static_cast<unsigned int>(item->data(0, Qt::UserRole).toInt())); // ricava l'ID dell'attività dalla prima colonna della tabella
    }
    return ids;
}

void VistaElencoAttivita::clearSelection()
{
    list->clearSelection();
    deleteButton->setEnabled(false);
}
/*
==============================================================================================
Implementazione dei metodi del Visitor per la diversa colorazione delle righe della tabella a seconda del tipo di attività
==============================================================================================
*/
void VistaElencoAttivita::visit(const Evento&){
    tipoAttivita = tr("Evento");
    coloreAttivita = QColor(220, 235, 255);
}

void VistaElencoAttivita::visit(const EventoRicorrente&){
    tipoAttivita = tr("Ricorrenza");
    coloreAttivita = QColor(220, 255, 220);
}

void VistaElencoAttivita::visit(const Lista&){
    tipoAttivita = tr("Lista");
    coloreAttivita = QColor(255, 240, 220);
}
