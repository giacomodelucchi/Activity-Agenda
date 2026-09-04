#ifndef EVENTO_H
#define EVENTO_H

#include "attivita.h"
#include <QString>
#include <QDateTime>
#include "attivitaVisitor.h"
#include "attivitaConstVisitor.h"

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

    //Visitor
    void accept(AttivitaVisitor&) override;
    void accept(AttivitaConstVisitor&) const override;

    //Metodi get
    QString getDescrizione() const;

    //Metodi set
    void setDescrizione(const QString&);
};

#endif // EVENTO_H

