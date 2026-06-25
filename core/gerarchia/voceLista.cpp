#include "voceLista.h"

//Costruttore
VoceLista::VoceLista(const QString& testo, bool completata)
    : testo(testo),
    completata(completata)
{}

//Costruttore di copia
VoceLista::VoceLista(const VoceLista& other)
    : testo(other.testo),
    completata(other.completata)
{}

//Metodi get
const QString& VoceLista::getTesto() const{
    return testo;
}

bool VoceLista::isCompletata() const{
    return completata;
}

//Metodi set
void VoceLista::setTesto(const QString& newTesto){
    testo = newTesto;
}

void VoceLista::setCompletata(bool stato){
    completata = stato;
}

//overloading operatori
bool VoceLista::operator==(const VoceLista& vl) const{      //considero due voci uguali se hanno lo stesso testo
    return testo == vl.testo;

}