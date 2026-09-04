#ifndef ATTIVITAVISITOR_H
#define ATTIVITAVISITOR_H

class Evento;
class EventoRicorrente;
class Lista;

//Visitor per la gerarchia Attivita usato per modificare gli oggetti
class AttivitaVisitor{
public:
    virtual ~AttivitaVisitor() = default;   

    virtual void visit(Evento&) = 0;
    virtual void visit(EventoRicorrente&) = 0;
    virtual void visit(Lista&) = 0;
};

#endif // ATTIVITAVISITOR_H