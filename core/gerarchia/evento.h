#ifndef EVENTO_H
#define EVENTO_H

#include "attivita.h"
#include <QString>
#include <QDateTime>

class Evento : public Attivita {
private:
    QString descrizione;

public:
    //Costruttore
    Evento(unsigned int = 0,
        const QString& = "SCONOSCIUTO",
        const QString& = "SCONOSCIUTO",
        const QDateTime& = QDateTime(),
        const QString& = ""
        );

    //Costruttore di copia
    Evento(const Evento&);

    //Distruttore virtuale
    ~Evento() override;

    //Metodi get
    QString getDescrizione() const;

    //Metodi set
    void setDescrizione(const QString&);
    /*
    //Metodo di clonazione per copia polimorfica
    virtual Evento* clone() const override;
    */
    /*
    //accept per Visitor
    virtual void accept(ActivityVisitorInterface&) const override;
    */
};

#endif // EVENTO_H

