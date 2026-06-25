#include "eventoRicorrente.h"
//Costruttore
EventoRicorrente::EventoRicorrente(unsigned int id,
                 const QString& titolo,
                const QString& luogo,
                const QDateTime& orario,
               Frequenza frequenza,
               unsigned int numOccorrenze,
               bool illimitata
               )
    : Evento(id, titolo, luogo, orario), frequenza(frequenza), numOccorrenze(illimitata ? 0 : numOccorrenze), illimitata(illimitata)
{}

//Costruttore di copia
EventoRicorrente::EventoRicorrente(const EventoRicorrente& er)
    : Evento(er), frequenza(er.frequenza), numOccorrenze(er.numOccorrenze), illimitata(er.illimitata){}

//Distruttore virtuale
EventoRicorrente::~EventoRicorrente() = default;

//Metodi get
Frequenza EventoRicorrente::getFrequenza() const{
    return frequenza;
}

unsigned int EventoRicorrente::getNumOccorrenze() const{
    return numOccorrenze;
}

bool EventoRicorrente::isIllimitata() const{
    return illimitata;
}

//Metodi set
void EventoRicorrente::setFrequenza(Frequenza newFrequenza){
    frequenza = newFrequenza;
}

void EventoRicorrente::setNumOccorrenze(unsigned int newNumOccorrenze){
    numOccorrenze = newNumOccorrenze;
}

void EventoRicorrente::setIllimitata(bool newIllimitata){
    illimitata = newIllimitata;
}

/*
//accept per Visitor
void EventoRicorrente::accept(ActivityVisitorInterface& visitor) const{
    visitor.visitEventoRicorrente(*this);
}
*/
/*
//Metodo di clonazione per copia polimorfica
EventoRicorrente* EventoRicorrente::clone() const{
    return new EventoRicorrente(*this);
}
*/


