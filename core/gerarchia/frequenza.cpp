#include "frequenza.h"

QString frequenzaToString(Frequenza freq) {
    switch (freq) {
        case Frequenza::Giornaliera: return "Giornaliera";
        case Frequenza::Settimanale: return "Settimanale";
        case Frequenza::Mensile:    return "Mensile";
        case Frequenza::Annuale:    return "Annuale";
        default:                    return "Nessuna";
    }
}

Frequenza stringToFrequenza(const QString& str) {
    if (str == "Giornaliera") return Frequenza::Giornaliera;
    if (str == "Settimanale") return Frequenza::Settimanale;
    if (str == "Mensile")    return Frequenza::Mensile;
    if (str == "Annuale")    return Frequenza::Annuale;
    return Frequenza::Nessuna;
}