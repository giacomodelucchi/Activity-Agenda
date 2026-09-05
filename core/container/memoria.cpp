#include "memoria.h"
#include "../gerarchia/attivita.h"

bool Memoria::aggiungi(std::unique_ptr<Attivita> attivita) {
    if (!attivita) return false;
    const unsigned int id = attivita->getId();
    const auto risultato = memoriaAttivita.insert({id, std::move(attivita)});
    if (!risultato.second) return false;    //l'inserimento non è avvenuto perché esiste già un'attività con lo stesso id
    modificheNonSalvate = true;
    return true;
}

bool Memoria::rimuovi(const Attivita* attivita) {
    if (!attivita) return false;
    return rimuoviPerId(attivita->getId());
}

bool Memoria::rimuoviPerId(unsigned int idAttivita) {
    auto risultato = memoriaAttivita.erase(idAttivita);

    if (risultato > 0) {
        modificheNonSalvate = true;
        return true;
    }
    return false;
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

bool Memoria::haModificheNonSalvate() const {
    return modificheNonSalvate;
}

void Memoria::salvaEffettuato() {
    modificheNonSalvate = false;
}

void Memoria::modificaEffettuata(){
    modificheNonSalvate = true;
}