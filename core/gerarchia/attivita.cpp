#include "attivita.h"

// Costruttore
Attivita::Attivita(unsigned int id, const QString& titolo, const QString& luogo, const QDateTime& orario)
    : id(id), titolo(titolo), luogo(luogo), orario(orario){}

// Costruttore di copia
Attivita::Attivita(const Attivita& a)
    : id(a.id), titolo(a.titolo), luogo(a.luogo), orario(a.orario){}

//Distruttore virtuale puro
Attivita::~Attivita() = default;

// Metodi get
unsigned int Attivita::getId() const{
    return id;
}

QString Attivita::getTitolo() const{
    return titolo;
}

QString Attivita::getLuogo() const{
    return luogo;
}

QDateTime Attivita::getOrario() const{
    return orario;
}

// Metodi set
void Attivita::setId(unsigned int newId){
    id = newId;
}

void Attivita::setTitolo(const QString& newTitolo){
    titolo = newTitolo;
}

void Attivita::setLuogo(const QString& newLuogo){
    luogo = newLuogo;
}

void Attivita::setOrario(const QDateTime& newOrario){
    orario = newOrario;
}