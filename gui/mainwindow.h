#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

class QStackedWidget;
class QPushButton;

#include "../core/container/memoria.h"
#include "../core/jsonIO/jsonIO.h"

class VistaElencoAttivita;
class VistaDettaglioAttivita;
class VistaEditorAttivita;

class MainWindow : public QMainWindow {
    Q_OBJECT  

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private:
    Memoria memoria;    //container per la gestione delle attività
    JsonIO jsonIO;      //oggetto per la gestione di input/output JSON

    QStackedWidget* stacked = nullptr;
    VistaElencoAttivita* elenco = nullptr;
    VistaDettaglioAttivita* dettaglio = nullptr;
    VistaEditorAttivita* editor = nullptr;
    unsigned int currentActivityId = 0;

private slots:  
    void onLoad();
    void onSave();
    void showElenco();                      // mostra la vista elenco con tutte le attività
    void showDettaglio(unsigned int id);    // mostra la vista dettaglio per l'attività con l'id specificato
    void showEditor(unsigned int id);       // mostra la vista editor per l'attività con l'id specificato
    void addActivity(int type);             // crea una nuova attività del tipo selezionato

private:
    unsigned int nextActivityId() const;
};

#endif // MAINWINDOW_H
