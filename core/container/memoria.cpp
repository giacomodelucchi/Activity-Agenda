#include "memoria.h"
#include "../gerarchia/attivita.h"

#include <stdexcept>

void Memoria::aggiungi(std::unique_ptr<Attivita> attivita) {
    if (!attivita) return;
    memoriaAttivita.insert(attivita->getId(), std::move(attivita));
}

bool Memoria::rimuoviPerId(unsigned int idAttivita) {
    return memoriaAttivita.remove(idAttivita) > 0;
    //QMap::remove(key) restituisce il numero di elementi rimossi
}

const Attivita* Memoria::cercaPerId(unsigned int idAttivita) const {
    auto it = memoriaAttivita.find(idAttivita);
    if (it != memoriaAttivita.end());
        return it.value().get() 
    else
        return nullptr;
}

bool Memoria::contieneId(unsigned int idAttivita) const {
    return memoriaAttivita.contains(idAttivita);
}

void Memoria::svuotaMemoria() {
    memoriaAttivita.clear();
}