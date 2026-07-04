#include "memoria.h"
#include "../gerarchia/attivita.h"

void Memoria::aggiungi(std::unique_ptr<Attivita> attivita) {
    if (!attivita) return;
    memoriaAttivita.insert({attivita->getId(), std::move(attivita)});
}

bool Memoria::rimuovi(const Attivita* attivita) {
    if (!attivita) return false;
    return rimuoviPerId(attivita->getId());
}

bool Memoria::rimuoviPerId(unsigned int idAttivita) {
    return memoriaAttivita.erase(idAttivita) > 0;
}

void Memoria::svuotaMemoria() {
    memoriaAttivita.clear();
}

bool Memoria::contieneId(unsigned int idAttivita) const {
    return memoriaAttivita.find(idAttivita) != memoriaAttivita.end();
}

const Attivita* Memoria::cercaPerId(unsigned int idAttivita) const {
    auto it = memoriaAttivita.find(idAttivita);
    if (it != memoriaAttivita.end()) {
        return it->second.get();
    }
    return nullptr;
}

Attivita* Memoria::cercaPerId(unsigned int idAttivita) {
    auto it = memoriaAttivita.find(idAttivita);
    if (it != memoriaAttivita.end()) {
        return it->second.get();
    }
    return nullptr;
}

unsigned int Memoria::size() const {
    return static_cast<unsigned int>(memoriaAttivita.size());
}