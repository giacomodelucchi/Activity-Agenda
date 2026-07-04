#ifndef MEMORIA_H
#define MEMORIA_H

#include <map>
#include <memory>

class Attivita;

class Memoria {
private:
    std::map<unsigned int, std::unique_ptr<Attivita>> memoriaAttivita;
public:
    Memoria() = default;
    Memoria(const Memoria&) = delete;
    ~Memoria() = default;

    void aggiungi(std::unique_ptr<Attivita> attivita);
    bool rimuovi(const Attivita* attivita);
    bool rimuoviPerId(unsigned int idAttivita);
    void svuotaMemoria();

    bool contieneId(unsigned int idAttivita) const;
    const Attivita* cercaPerId(unsigned int idAttivita) const;
    Attivita* cercaPerId(unsigned int idAttivita);
    unsigned int size() const;

    template <typename Func>
    void perOgniAttivita(Func&& fn) const {
        for (const auto& entry : memoriaAttivita) {
            if (entry.second) {
                fn(*entry.second);
            }
        }
    }
};

#endif // MEMORIA_H