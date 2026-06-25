#ifndef LISTA_H
#define LISTA_H

#include "attivita.h"
#include "voceLista.h"

#include <QString>
#include <QVector>

class Lista : public Attivita {
private:
    QVector<VoceLista> elementi;

public:
    //Costruttore
    Lista(unsigned int = 0,
          const QString& = "SCONOSCIUTO",
          const QVector<VoceLista>& = QVector<VoceLista>());

    //Costruttore di copia
    Lista(const Lista&);

    //Distruttore virtuale
    ~Lista() override;

    //Metodi get
    const QVector<VoceLista>& getElementi() const;

    //Metodi set
    void setElementi(const QVector<VoceLista>&);

    //Gestione voci della lista
    bool aggiungiVoce(const VoceLista&);             //per aggiungere una voce in coda alla lista
    bool rimuoviVoce(unsigned int);             //per cancellare una determinata voce dalla lista
    bool spostaVoce(unsigned int, unsigned int);    //per spostare una voce all'interno della lista
    bool setStatoVoce(unsigned int, bool);         //cambia lo stato di una determinata voce

    const VoceLista& Lista::getVoce(unsigned int) const; //leggere una voce specifica (ad es per stampare a schermo la lista) se esce dai bound lancia un'eccezione std::out_of_range
    unsigned int numeroVoci() const;        //conoscere il numnero di voci in lista

    /*
    //Metodo di clonazione per copia polimorfica
    virtual Lista* clone() const override;
    */

    /*
    //accept per Visitor
    virtual void accept(ActivityVisitorInterface&) const override;
    */
};

#endif // LISTA_H