#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <QJsonObject>
#include <QJsonArray>

#include "../gerarchia/attivita.h"
#include "../gerarchia/evento.h"
#include "../gerarchia/eventoRicorrente.h"
#include "../gerarchia/lista.h"
#include "../gerarchia/voceLista.h"

class JsonParser{
private:
    //restituisce un QJsonObject contenete i dati di un oggetto Attivita
    QJsonObject AttivitaToJson(const Attivita&) const;
    //crea l'oggetto rappresentato nel QJsonObject e ne restituisce un riferimento
    Attivita& JsonToAttivita(const QJsonObject&) const;
public:
    //Costruttore
    JsonParser(const QString& = "SCONOSCIUTO");
}