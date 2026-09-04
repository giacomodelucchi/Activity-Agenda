#ifndef ATTIVITA_H
#define ATTIVITA_H

#include <QString>
#include <QDateTime>
#include "attivitaVisitor.h"
#include "attivitaConstVisitor.h"

class Attivita {
    private:
        unsigned int id;
        QString titolo;
        QString luogo;
        QDateTime orario;
    
    public:
        //Costruttore
        Attivita(unsigned int = 0, const QString& = "SCONOSCIUTO", const QString& = "SCONOSCIUTO", const QDateTime& = QDateTime());

        //Costruttore di copia
        Attivita(const Attivita&);

        //Distruttore virtuale puro
        virtual ~Attivita() = 0;

        // Visitor per oggetti modificabili
        virtual void accept(AttivitaVisitor&) = 0;

        // Visitor per oggetti const
        virtual void accept(AttivitaConstVisitor&) const = 0;
            
        //Metodi get
        unsigned int getId() const;
        QString getTitolo() const;
        QString getLuogo() const;
        virtual QDateTime getOrario() const;

        //Metodi set
        void setId(unsigned int);
        void setTitolo(const QString&);
        void setLuogo(const QString&);
        virtual void setOrario(const QDateTime&);
};

#endif // ATTIVITA_H