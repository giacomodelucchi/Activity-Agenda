#ifndef VISTAEDITORATTIVITA_H
#define VISTAEDITORATTIVITA_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTime>
#include <QDateTimeEdit>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QSpinBox>
#include <QCheckBox>

#include "../core/gerarchia/attivita.h"
#include "../core/gerarchia/evento.h"
#include "../core/gerarchia/eventoRicorrente.h"
#include "../core/gerarchia/lista.h"
#include "VistaEditorLista.h"
#include "../core/gerarchia/attivitaVisitor.h"

class VistaEditorAttivita : public QWidget, public AttivitaVisitor {
    Q_OBJECT
public:
    explicit VistaEditorAttivita(QWidget* parent = nullptr);
    void editActivity(Attivita* a);
    bool hasUnsavedChanges() const;

    //Visitor
    void visit(Evento&) override;
    void visit(EventoRicorrente&) override;
    void visit(Lista&) override;

signals:
    void saved(unsigned int id);
    void cancelled(unsigned int id);

private slots:
    void onSave();
    void onCancel();
    void markDirty();   //segnala che l'editor ha modifiche non salvate rispetto all'attività visuallizzata

private:
    enum class VisitorMode {
        Loading,
        Saving
    };
        
    VisitorMode visitorMode = VisitorMode::Loading;   //per distinguere se l'editor sta caricando i dati dell'attività corrente o salvando le modifiche apportate dall'utente

    QFormLayout* formLayout = nullptr;
    Attivita* current = nullptr;        //attività che sta venendo modificata nell'editor
    
    //campi comuni
    QLineEdit* titleEdit = nullptr;
    QTextEdit* descriptionEdit = nullptr;
    QLineEdit* locationEdit = nullptr;
    QDateTimeEdit* dateTimeEdit = nullptr;

    //campi di EventoRicorrente
    QComboBox* frequenzaCombo;
    QSpinBox* numOccorrenzeSpin;
    QCheckBox* illimitataCheck;

    //editor per oggetti Lista
    VistaEditorLista* listaEditor = nullptr;

    QPushButton* saveButton = nullptr;
    QPushButton* cancelButton = nullptr;
    bool dirty = false;                 //indica se l'editor ha modifiche non salvate rispetto all'attività corrente
};

#endif // VISTAEDITORATTIVITA_H
