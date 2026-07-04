#ifndef FREQUENZA_H
#define FREQUENZA_H

#include <QString>

enum class Frequenza {
    Nessuna,
    Giornaliera,
    Settimanale,
    Mensile,
    Annuale
};

QString frequenzaToString(Frequenza freq);
Frequenza stringToFrequenza(const QString& str);

#endif // FREQUENZA_H
