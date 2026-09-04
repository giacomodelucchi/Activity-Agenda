#include "eventoRicorrente.h"
//Costruttore
EventoRicorrente::EventoRicorrente(unsigned int id,
                 const QString& titolo,
                const QString& luogo,
                const QDateTime& orario,
                const QString& descrizione,
               Frequenza frequenza,
               unsigned int numOccorrenze,
               bool illimitata
               )
    : Evento(id, titolo, luogo, orario, descrizione), 
    frequenza(frequenza), 
    numOccorrenze(illimitata ? 0 : numOccorrenze), 
    illimitata(illimitata),
    dataInizio(orario)
{}

//Costruttore di copia
EventoRicorrente::EventoRicorrente(const EventoRicorrente& er)
    : Evento(er), frequenza(er.frequenza), numOccorrenze(er.numOccorrenze), illimitata(er.illimitata), dataInizio(er.dataInizio){}

//Distruttore virtuale
EventoRicorrente::~EventoRicorrente() = default;

// Visitor
void EventoRicorrente::accept(AttivitaVisitor& visitor) {
    visitor.visit(*this);
}

void EventoRicorrente::accept(AttivitaConstVisitor& visitor) const
{
    visitor.visit(*this);
}

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
     if (newNumOccorrenze < 1)
        numOccorrenze = 1;
    else
        numOccorrenze = newNumOccorrenze;
}

void EventoRicorrente::setIllimitata(bool newIllimitata){
    illimitata = newIllimitata;
}

/*
quando si richiede l'orario di un evento ricorrente, 
viene calcolata la prossima occorrenza futura rispetto alla data attuale
*/
QDateTime EventoRicorrente::getOrario() const
{
    if (!dataInizio.isValid())
        return QDateTime();

    if (frequenza == Frequenza::Nessuna)
        return dataInizio;

    QDateTime prossimo = dataInizio;
    QDateTime adesso = QDateTime::currentDateTime();

    unsigned int occorrenza = 1;   

    while (prossimo < adesso)
    {
        // abbiamo già raggiunto l'ultima occorrenza
        if (!illimitata && occorrenza >= numOccorrenze)
            return prossimo;

        switch (frequenza)
        {
        case Frequenza::Giornaliera:
            prossimo = prossimo.addDays(1);
            break;

        case Frequenza::Settimanale:
            prossimo = prossimo.addDays(7);
            break;

        case Frequenza::Mensile:
            prossimo = prossimo.addMonths(1);
            break;

        case Frequenza::Annuale:
            prossimo = prossimo.addYears(1);
            break;

        case Frequenza::Nessuna:
        default:
            return prossimo;
        }

        ++occorrenza;
    }

    return prossimo;
}

void EventoRicorrente::setOrario(const QDateTime& dt){
    Evento::setOrario(dt);
    dataInizio = dt;
}

