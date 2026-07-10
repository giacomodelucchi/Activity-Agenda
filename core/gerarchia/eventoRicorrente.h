#ifndef EVENTORICORRENTE_H
#define EVENTORICORRENTE_H

#include "evento.h"
#include "frequenza.h"
#include <QString>
#include <QDateTime>

class EventoRicorrente : public Evento {
private:
    Frequenza frequenza;
    unsigned int numOccorrenze;
    bool illimitata;
    QDateTime dataInizio;   //data da cui inizia la ricorrenza

public:
    //Costruttore
    EventoRicorrente(unsigned int id = 0,
                     const QString& titolo = "SCONOSCIUTO",
                     const QString& luogo = "SCONOSCIUTO",
                     const QDateTime& orario = QDateTime(),
                     const QString& descrizione = QString(),
                     Frequenza frequenza = Frequenza::Nessuna,
                     unsigned int numOccorrenze = 1,
                     bool illimitata = false);

    //Costruttore di copia
    EventoRicorrente(const EventoRicorrente&);

    //Distruttore virtuale
    ~EventoRicorrente() override;

    //Metodi get
    Frequenza getFrequenza() const;
    unsigned int getNumOccorrenze() const;
    bool isIllimitata() const;
    QDateTime getOrario() const override;

    //Metodi set
    void setFrequenza(Frequenza);
    void setNumOccorrenze(unsigned int);
    void setIllimitata(bool);
    void setOrario(const QDateTime&) override;
};

#endif // EVENTORICORRENTE_H