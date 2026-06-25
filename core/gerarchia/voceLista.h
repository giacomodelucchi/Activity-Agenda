#ifndef VOCELISTA_H
#define VOCELISTA_H

#include <QString>

    class VoceLista {
    private:
        QString testo;
        bool completata;    //true se completata, false altrimenti

    public:
        //Costruttore
        VoceLista(const QString& = "SCONOSCIUTO", bool = false);

        //Costruttore di copia
        VoceLista(const VoceLista&);

        //Metodi get
        const QString& getTesto() const;
        bool isCompletata() const;

        //Metodi set
        void setTesto(const QString&);
        void setCompletata(bool);

        //overloading operatori
        bool operator==(const VoceLista&) const;

    };

#endif // VOCELISTA_H
