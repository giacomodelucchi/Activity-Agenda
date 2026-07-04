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

//Metodi get
QString Evento::getDescrizione() const{
    return descrizione;
}

//Metodi set
void Evento::setDescrizione(const QString& newDescrizione){
    descrizione = newDescrizione;
}

/*
//accept per Visitor
void Evento::accept(ActivityVisitorInterface& visitor) const{
    visitor.visitEvento(*this);
}
*/
/*
//Metodo di clonazione per copia polimorfica
Evento* Evento::clone() const{
    return new Evento(*this);
}
*/


