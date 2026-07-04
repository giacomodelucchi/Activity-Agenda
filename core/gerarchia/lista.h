#ifndef LISTA_H
#define LISTA_H

#include "attivita.h"
#include "voceLista.h"

#include <QString>
#include <QVector>
#include <QDateTime>

class Lista : public Attivita {
private:
    QVector<VoceLista> elementi;

public:
    Lista(unsigned int = 0,
          const QString& = "SCONOSCIUTO",
          const QString& = "SCONOSCIUTO",
          const QDateTime& = QDateTime(),
          const QVector<VoceLista>& = QVector<VoceLista>());

    Lista(const Lista&);
    ~Lista() override;

    unsigned int numeroVoci() const;
    const VoceLista& getVoce(unsigned int indice) const;
    void setElementi(const QVector<VoceLista>& newElementi);

    bool aggiungiVoce(const VoceLista& voce);
    bool rimuoviVoce(unsigned int indice);
    bool spostaVoce(unsigned int origine, unsigned int destinazione);
    bool setStatoVoce(unsigned int indice, bool stato);
};

#endif // LISTA_H