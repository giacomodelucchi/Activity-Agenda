#ifndef MEMORIA_H
#define MEMORIA_H

#include <memory>
#include <QMap>

class Attivita;
//rappresenta la memoria per gli oggetti Attivita creati
//gli id delle Attivita sono la chiave della mappa, mentre i valori sono unique pointers agli oggetti Attivita
class Memoria {
private:
    QMap<unsigned int, std::unique_ptr<Attivita>> memoriaAttivita;
public:
    //Costruttore
    Memoria() = default;

    //Copia vietata per mantenere unici gli unique pointers
    Memoria(const Memoria&) = delete;
    
    //Distruttore 
    ~Memoria() = default;

    //Metodi get
    const QMap<unsigned int, std::unique_ptr<Attivita>>& items() const;

    //Metodi
    void aggiungi(std::unique_ptr<Attivita> attivita);
    
    bool rimuovi(const Attivita* attivita);
    bool rimuoviPerId(unsigned int idAttivita);
    void svuotaMemoria();
    
    bool contieneId(unsigned int idAttivita) const;
    const Attivita* cercaPerId(unsigned int idAttivita) const;
    
    unsigned int size() const;
};

#endif // MEMORIA_H