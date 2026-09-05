#ifndef VISTAEDITORLISTA_H
#define VISTAEDITORLISTA_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>

#include "../core/gerarchia/lista.h"

class VistaEditorLista : public QWidget
{
    Q_OBJECT

public:
    explicit VistaEditorLista(QWidget* parent = nullptr);

    void setLista(Lista* lista);
    void applyChanges(Lista& lista) const;  //applica le modifiche apportate dall'utente alla lista passata come parametro

signals:
    void modified();

private slots:
    void aggiungiVoce();
    void eliminaVoce();
    void aggiornaVoce(QListWidgetItem*);
    void aggiornaPulsanteElimina();

private:
    void aggiornaVista();

    Lista* currentLista = nullptr;
    QVector<VoceLista> elementiDiLavoro;    //vettore che contiene le voci della lista mentre l'utente le modifica nell'editor

    QListWidget* voceList = nullptr;

    QPushButton* addButton = nullptr;
    QPushButton* removeButton = nullptr;
};

#endif