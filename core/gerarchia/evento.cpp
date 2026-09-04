#include "evento.h"
//Costruttore
Evento::Evento(unsigned int id,
       const QString& titolo,
       const QString& luogo,
       const QDateTime& orario,
       const QString& descrizione
       )
    : Attivita(id, titolo, luogo, orario), descrizione(descrizione){}

//Costruttore di copia
Evento::Evento(const Evento& e)
    : Attivita(e), descrizione(e.descrizione){}

//Distruttore virtuale
Evento::~Evento() = default;

// Visitor
void Evento::accept(AttivitaVisitor& visitor){
    visitor.visit(*this);
}

void Evento::accept(AttivitaConstVisitor& visitor) const{
    visitor.visit(*this);
}

//Metodi get
QString Evento::getDescrizione() const{
    return descrizione;
}

//Metodi set
void Evento::setDescrizione(const QString& newDescrizione){
    descrizione = newDescrizione;
}



