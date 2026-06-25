#include "attivita.h"

// Costruttore
Attivita::Attivita(unsigned int id, const QString& titolo)
    : id(id), titolo(titolo){}

// Costruttore di copia
Attivita::Attivita(const Attivita& a)
    : id(a.id), titolo(a.titolo){}

//Distruttore virtuale puro
Attivita::~Attivita() = default;

// Metodi get
unsigned int Attivita::getId() const{
    return id;
}

QString Attivita::getTitolo() const{
    return titolo;
}

// Metodi set
void Attivita::setId(unsigned int newId){
    id = newId;
}

void Attivita::setTitolo(const QString& newTitolo){
    titolo = newTitolo;
}