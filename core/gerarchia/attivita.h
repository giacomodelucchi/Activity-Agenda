#ifndef ATTIVITA_H
#define ATTIVITA_H

#include <QString>
#include <QDateTime>

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

        //Metodi get
        unsigned int getId() const;
        QString getTitolo() const;
        QString getLuogo() const;
        QDateTime getOrario() const;

        //Metodi set
        void setId(unsigned int);
        void setTitolo(const QString&);
        void setLuogo(const QString&);
        void setOrario(const QDateTime&);
        /*
        //accept virtuale puro per Visitor
        virtual void accept(ActivityVisitorInterface&) const = 0;
*/
        /*
        //Metodo di clonazione per copia polimorfica
        virtual Attivita* clone() const = 0;
*/
};

#endif // ATTIVITA_H