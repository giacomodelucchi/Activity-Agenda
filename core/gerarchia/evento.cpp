#include "evento.h"
//Costruttore
Evento::Evento(unsigned int id,
       const QString& titolo,
       const QString& luogo,
       const QDateTime& orario
       )
    : Attivita(id, titolo), luogo(luogo), orario(orario){}

//Costruttore di copia
Evento::Evento(const Evento& e)
    : Attivita(e), luogo(e.luogo), orario(e.orario){}

//Distruttore virtuale
Evento::~Evento() = default;

//Metodi get
QString Evento::getLuogo() const{
    return luogo;
}
QDateTime Evento::getOrario() const{
    return orario;
}

//Metodi set
void Evento::setLuogo(const QString& newLuogo){
    luogo = newLuogo;
}
void Evento::setOrario(const QDateTime& newOrario){
    orario = newOrario;
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


