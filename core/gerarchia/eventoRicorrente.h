#ifndef EVENTORICORRENTE_H
#define EVENTORICORRENTE_H

#include "evento.h"
#include <QString>
#include <QDateTime>

enum class Frequenza {
    Nessuna,
    Giornaliera,
    Settimanale,
    Mensile,
    Annuale
};

class EventoRicorrente : public Evento {
private:
    Frequenza frequenza;
    unsigned int numOccorrenze;
    bool illimitata;

public:
    //Costruttore
    EventoRicorrente(unsigned int = 0,
                     const QString& = "SCONOSCIUTO",
                     const QString& = "SCONOSCIUTO",
                     const QDateTime& = QDateTime(),
                    Frequenza = Frequenza::Nessuna,
                     unsigned int = 0,
                     bool = false);

    //Costruttore di copia
    EventoRicorrente(const EventoRicorrente&);

    //Distruttore virtuale
    ~EventoRicorrente() override;

    //Metodi get
    Frequenza getFrequenza() const;
    unsigned int getNumOccorrenze() const;
    bool isIllimitata() const;

    //Metodi set
    void setFrequenza(Frequenza);
    void setNumOccorrenze(unsigned int);
    void setIllimitata(bool);

    /*
    //Metodo di clonazione per copia polimorfica
    virtual EventoRicorrente* clone() const override;
    */

    /*
    //accept per Visitor
    virtual void accept(ActivityVisitorInterface&) const override;
    */
};

#endif // EVENTORICORRENTE_H