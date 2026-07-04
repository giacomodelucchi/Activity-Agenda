#include "mainwindow.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QStatusBar>
#include <QVBoxLayout>
#include <QStyle>
#include <QDateTime>

#include "VistaElencoAttivita.h"
#include "VistaDettaglioAttivita.h"
#include "VistaEditorAttivita.h"
#include "../core/gerarchia/evento.h"
#include "../core/gerarchia/eventoRicorrente.h"
#include "../core/gerarchia/lista.h"
#include "../core/gerarchia/voceLista.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), jsonIO()
{
    // Top bar con pulsanti di navigazione e azioni file
    QWidget* topBar = new QWidget(this);
    auto* topLayout = new QHBoxLayout(topBar);
    topLayout->setContentsMargins(8, 4, 8, 4);
    topLayout->setSpacing(10);

    QPushButton* loadButton = new QPushButton(tr("Carica JSON"), this);
    QPushButton* saveButton = new QPushButton(tr("Salva JSON"), this);

    topLayout->addStretch();
    topLayout->addWidget(loadButton);
    topLayout->addWidget(saveButton);

    setMenuWidget(topBar);

    connect(loadButton, &QPushButton::clicked, this, &MainWindow::onLoad);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::onSave);

    // Widget impilati per le diverse viste
    stacked = new QStackedWidget(this);

    elenco = new VistaElencoAttivita(this);
    dettaglio = new VistaDettaglioAttivita(this);
    editor = new VistaEditorAttivita(this);

    elenco->setMemoria(&memoria);   // Passaggio il riferimento alla memoria al widget elenco

    stacked->addWidget(elenco);
    stacked->addWidget(dettaglio);
    stacked->addWidget(editor);

    setCentralWidget(stacked);

    // COLLEGAMENTI TRA LE VISTE
    // Quando un'attività viene selezionata nell'elenco, mostra il dettaglio
    connect(elenco, &VistaElencoAttivita::activitySelected, this, &MainWindow::showDettaglio);
    connect(elenco, &VistaElencoAttivita::deleteSelectedRequested, this, [this](const QVector<unsigned int>& ids){
        if (ids.isEmpty()) return;
        auto result = QMessageBox::question(this, tr("Conferma eliminazione"), tr("Eliminare le attività selezionate?"));
        if (result != QMessageBox::Yes) return;
        for (unsigned int id : ids) {
            memoria.rimuoviPerId(id);
        }
        elenco->refreshList();
        showElenco();
    });
    connect(elenco, &VistaElencoAttivita::addRequested, this, &MainWindow::addActivity);
    
    // Quando un'attività viene richiesta per la modifica dal dettaglio, mostra l'editor
    connect(dettaglio, &VistaDettaglioAttivita::editRequested, this, &MainWindow::showEditor);
    connect(dettaglio, &VistaDettaglioAttivita::deleteRequested, this, [this](unsigned int id){
        auto result = QMessageBox::question(this, tr("Conferma eliminazione"), tr("Eliminare questa attività?"));
        if (result != QMessageBox::Yes) return;
        memoria.rimuoviPerId(id);
        elenco->refreshList();
        showElenco();
    });
    connect(dettaglio, &VistaDettaglioAttivita::backRequested, this, &MainWindow::showElenco);
    
    // Quando un'attività viene salvata nell'editor, aggiorna l'elenco e mostra il dettaglio
    connect(editor, &VistaEditorAttivita::saved, this, [this](unsigned int id){
        elenco->refreshList();
        showDettaglio(id);
    });

    connect(editor, &VistaEditorAttivita::cancelled, this, [this](unsigned int id){
        showDettaglio(id);
    });

    showElenco();   // la vista iniziale è l'elenco delle attività
    statusBar()->showMessage(tr("Pronto")); 
}

MainWindow::~MainWindow() = default;

// chiamata quando l'utente seleziona "Carica JSON" 
void MainWindow::onLoad()
{
    if (stacked->currentWidget() == editor && editor->hasUnsavedChanges()) {
        auto result = QMessageBox::warning(this, tr("Modifiche non salvate"),
            tr("Stai modificando un'attività non salvata. Vuoi continuare e perdere le modifiche?"),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No);
        if (result != QMessageBox::Yes) return;
    }

    QString path = QFileDialog::getOpenFileName(this, tr("Apri file JSON"), QString(), tr("JSON Files (*.json)"));
    if (path.isEmpty()) return;

    if (!path.endsWith(".json", Qt::CaseInsensitive)) {
        QMessageBox::warning(this, tr("Errore"), tr("Selezionare un file JSON."));
        return;
    }

    jsonIO.setFilePath(path);
    if (jsonIO.load(memoria)) {
        elenco->refreshList();
        showElenco();
        statusBar()->showMessage(tr("File caricato"));
    } else {
        statusBar()->showMessage(tr("Errore caricamento"));
    }
}

// chiamata quando l'utente seleziona "Salva JSON"
void MainWindow::onSave()
{
    if (stacked->currentWidget() == editor && editor->hasUnsavedChanges()) {
        auto result = QMessageBox::warning(this, tr("Modifiche non salvate"),
            tr("Stai modificando un'attività non salvata. Vuoi continuare e perdere le modifiche?"),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No);
        if (result != QMessageBox::Yes) return;
    }

    QString path = QFileDialog::getSaveFileName(this, tr("Salva file JSON"), QString(), tr("JSON Files (*.json)"));
    if (path.isEmpty()) return;
   
    jsonIO.setFilePath(path);
    if (jsonIO.save(memoria)) {
        elenco->refreshList();
        showElenco();
        statusBar()->showMessage(tr("File salvato"));
    } else {
        statusBar()->showMessage(tr("Errore salvataggio"));
    }
}

void MainWindow::showElenco()
{
    currentActivityId = 0;
    elenco->clearSelection();
    elenco->refreshList();
    stacked->setCurrentWidget(elenco);
}

void MainWindow::showDettaglio(unsigned int id)
{
    currentActivityId = id;
    const Attivita* a = memoria.cercaPerId(id);
    dettaglio->setActivity(a);
    stacked->setCurrentWidget(dettaglio);
}

void MainWindow::showEditor(unsigned int id)
{
    currentActivityId = id;
    Attivita* a = memoria.cercaPerId(id);
    editor->editActivity(a);
    stacked->setCurrentWidget(editor);
}

void MainWindow::addActivity(int type)
{
    unsigned int newId = nextActivityId();
    std::unique_ptr<Attivita> newActivity;

    switch (type) {
        case VistaElencoAttivita::TipoEventoRicorrente:
            newActivity = std::make_unique<EventoRicorrente>(newId, QString(), QString(), QDateTime(), QString(), Frequenza::Nessuna, 0, false);
            break;
        case VistaElencoAttivita::TipoLista:
            newActivity = std::make_unique<Lista>(newId, QString(), QString(), QDateTime(), QVector<VoceLista>());
            break;
        case VistaElencoAttivita::TipoEvento:
        default:
            newActivity = std::make_unique<Evento>(newId, QString(), QString(), QDateTime(), QString());
            break;
    }

    Attivita* rawPointer = newActivity.get();
    memoria.aggiungi(std::move(newActivity));
    showEditor(rawPointer->getId());
}

unsigned int MainWindow::nextActivityId() const
{
    unsigned int maxId = 0;
    memoria.perOgniAttivita([&](const Attivita& a){
        if (a.getId() > maxId) {
            maxId = a.getId();
        }
    });
    return maxId + 1;
}
