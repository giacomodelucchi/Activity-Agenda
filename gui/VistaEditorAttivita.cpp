#include "VistaEditorAttivita.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QLabel>
#include <QPushButton>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QHeaderView>

#include "../core/gerarchia/evento.h"
#include "../core/gerarchia/eventoRicorrente.h"
#include "../core/gerarchia/lista.h"
#include "../core/gerarchia/voceLista.h"

VistaEditorAttivita::VistaEditorAttivita(QWidget* parent)
    : QWidget(parent)
{
    auto* mainLayout = new QVBoxLayout(this);
    auto* formLayout = new QFormLayout();

    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText(tr("Titolo"));
    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText(tr("Descrizione"));
    descriptionEdit->setAcceptRichText(false);
    locationEdit = new QLineEdit(this);
    locationEdit->setPlaceholderText(tr("Luogo"));
    dateTimeEdit = new QDateTimeEdit(this);
    dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
    dateTimeEdit->setCalendarPopup(true);

    itemsLabel = new QLabel(this);
    itemList = new QTreeWidget(this);
    itemList->setColumnCount(2);
    itemList->setHeaderLabels({tr("Completata"), tr("Voce")});
    itemList->setRootIsDecorated(false);
    itemList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    itemList->header()->setSectionResizeMode(QHeaderView::Stretch);
    itemList->setVisible(false);

    saveButton = new QPushButton(tr("Salva"), this);
    cancelButton = new QPushButton(tr("Annulla"), this);

    auto* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(tr("Titolo:"), titleEdit);
    formLayout->addRow(tr("Descrizione:"), descriptionEdit);
    formLayout->addRow(tr("Luogo:"), locationEdit);
    formLayout->addRow(tr("Orario:"), dateTimeEdit);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(itemsLabel);
    mainLayout->addWidget(itemList);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &VistaEditorAttivita::onSave);
    connect(cancelButton, &QPushButton::clicked, this, &VistaEditorAttivita::onCancel);
    connect(titleEdit, &QLineEdit::textChanged, this, &VistaEditorAttivita::markDirty);
    connect(descriptionEdit, &QTextEdit::textChanged, this, &VistaEditorAttivita::markDirty);
    connect(locationEdit, &QLineEdit::textChanged, this, &VistaEditorAttivita::markDirty);
    connect(dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &VistaEditorAttivita::markDirty);
    connect(itemList, &QTreeWidget::itemChanged, this, &VistaEditorAttivita::markDirty);
}

void VistaEditorAttivita::editActivity(Attivita* a)
{
    current = a;
    dirty = false;

    if (!a) {
        titleEdit->clear();
        descriptionEdit->clear();
        descriptionEdit->setVisible(true);
        locationEdit->clear();
        dateTimeEdit->setDateTime(QDateTime::currentDateTime());
        itemList->clear();
        itemsLabel->clear();
        itemList->setVisible(false);
        saveButton->setEnabled(false);
        cancelButton->setEnabled(false);
        dirty = false;
        return;
    }

    titleEdit->setText(a->getTitolo());
    descriptionEdit->setVisible(true);
    descriptionEdit->clear();
    locationEdit->clear();
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    itemList->clear();
    itemList->setVisible(false);
    itemsLabel->clear();
    saveButton->setEnabled(true);
    cancelButton->setEnabled(true);

    if (const EventoRicorrente* er = dynamic_cast<const EventoRicorrente*>(a)) {
        descriptionEdit->setText(er->getDescrizione());
        locationEdit->setText(er->getLuogo());
        dateTimeEdit->setDateTime(er->getOrario());
        itemsLabel->setText(tr("Modifica i dettagli dell'evento ricorrente."));
    } else if (const Evento* ev = dynamic_cast<const Evento*>(a)) {
        descriptionEdit->setText(ev->getDescrizione());
        locationEdit->setText(ev->getLuogo());
        dateTimeEdit->setDateTime(ev->getOrario());
        itemsLabel->setText(tr("Modifica i dettagli dell'evento."));
    } else if (const Lista* lista = dynamic_cast<const Lista*>(a)) {
        descriptionEdit->setVisible(false);
        locationEdit->setText(lista->getLuogo());
        dateTimeEdit->setDateTime(lista->getOrario().isValid() ? lista->getOrario() : QDateTime::currentDateTime());
        itemsLabel->setText(tr("Elementi della lista (solo visualizzazione)."));
        itemList->setVisible(true);
        itemList->clear();
        for (unsigned int i = 0; i < lista->numeroVoci(); ++i) {
            const VoceLista& voce = lista->getVoce(i);
            auto* item = new QTreeWidgetItem(itemList);
            item->setText(1, voce.getTesto());
            item->setCheckState(0, voce.isCompletata() ? Qt::Checked : Qt::Unchecked);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
        }
    } else {
        descriptionEdit->setVisible(true);
    }
}

void VistaEditorAttivita::onSave()
{
    if (!current) return;
    current->setTitolo(titleEdit->text());

    if (auto* ev = dynamic_cast<Evento*>(current)) {
        ev->setDescrizione(descriptionEdit->toPlainText());
        ev->setLuogo(locationEdit->text());
        ev->setOrario(dateTimeEdit->dateTime());
    }
    if (auto* lista = dynamic_cast<Lista*>(current)) {
        lista->setLuogo(locationEdit->text());
        lista->setOrario(dateTimeEdit->dateTime());
        for (int i = 0; i < itemList->topLevelItemCount(); ++i) {
            QTreeWidgetItem* item = itemList->topLevelItem(i);
            lista->setStatoVoce(static_cast<unsigned int>(i), item->checkState(0) == Qt::Checked);
        }
    }

    dirty = false;
    emit saved(current->getId());
}

void VistaEditorAttivita::onCancel()
{
    if (!current) return;
    dirty = false;
    emit cancelled(current->getId());
}

void VistaEditorAttivita::markDirty()
{
    if (!current) return;
    dirty = true;
}

bool VistaEditorAttivita::hasUnsavedChanges() const
{
    return dirty;
}
