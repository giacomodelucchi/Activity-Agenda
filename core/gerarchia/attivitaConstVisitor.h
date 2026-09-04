#ifndef ATTIVITACONSTVISITOR_H
#define ATTIVITACONSTVISITOR_H

class Evento;
class EventoRicorrente;
class Lista;

// visitor per la gerarchia Attivita usato per leggere gli oggetti senza modificarli
class AttivitaConstVisitor
{
public:
    virtual ~AttivitaConstVisitor() = default;

    virtual void visit(const Evento&) = 0;
    virtual void visit(const EventoRicorrente&) = 0;
    virtual void visit(const Lista&) = 0;
};

#endif // ATTIVITACONSTVISITOR_H