#include "lista.h"

//Costruttore
Lista::Lista(unsigned int id,
             const QString& titolo,
             const QVector<VoceLista>& elementi)
            : Attivita(id, titolo),
            elementi(elementi)
            {}

//Costruttore di copia
Lista::Lista(const Lista& l)
    : Attivita(l),
    elementi(l.elementi)
{}

//Distruttore virtuale
Lista::~Lista() = default;

const QVector<VoceLista>& Lista::getElementi() const{
    return elementi;
}

//Metodi set
void Lista::setElementi(const QVector<VoceLista>& newElementi){
    elementi = newElementi;
}

//GESTIONE VOCI LISTA

//Aggiunge una voce in coda
bool Lista::aggiungiVoce(const VoceLista& voce){
    if(elementi.contains(voce))     //per questo serve operator== di VoceLista
        return false;
    else
    {
        elementi.push_back(voce);
        return true;
    }
}

//Rimuove una voce specifica
bool Lista::rimuoviVoce(unsigned int indice)
{
    if (indice >= static_cast<unsigned int>(elementi.size()))
        return false;

    elementi.removeAt(indice);
    return true;
}

// Sposta una voce
bool Lista::spostaVoce(unsigned int origine,
                       unsigned int destinazione)
{
    if (origine >= static_cast<unsigned int>(elementi.size()) ||
        destinazione >= static_cast<unsigned int>(elementi.size()))
    {
        return false;
    }

    elementi.move(origine, destinazione);
    return true;
}

bool Lista::setStatoVoce(unsigned int indice, bool stato)
{
    if (indice >= static_cast<unsigned int>(elementi.size()))
        return false;

    elementi[indice].setCompletata(stato);
    return true;
}

const VoceLista& Lista::getVoce(unsigned int indice) const
{
    return elementi.at(indice);
}

unsigned int Lista::numeroVoci() const
{
    return static_cast<unsigned int>(elementi.size());
}

