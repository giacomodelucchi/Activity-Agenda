#ifndef JSONPARSER_H
#define JSONPARSER_H

#include "../container/memoria.h"
#include <memory>
#include <QJsonObject>
#include <QJsonArray>
#include <QString>

#include "../gerarchia/attivita.h"
#include "../gerarchia/evento.h"
#include "../gerarchia/eventoRicorrente.h"
#include "../gerarchia/lista.h"
#include "../gerarchia/voceLista.h"

class JsonParser{
private:
    QString source; //indirizzo del file JSON da cui leggere o scrivere
    
    static QJsonObject eventoToJson(const Evento&);
    static QJsonObject eventoRicorrenteToJson(const EventoRicorrente&);
    static QJsonObject listaToJson(const Lista&);
    static QJsonObject voceListaToJson(const VoceLista&);

    static std::unique_ptr<Attivita> jsonToEvento(const QJsonObject&);
    static std::unique_ptr<Attivita> jsonToEventoRicorrente(const QJsonObject&);
    static std::unique_ptr<Attivita> jsonToLista(const QJsonObject&);
    static VoceLista jsonToVoceLista(const QJsonObject&);

    
    public:
    explicit JsonParser(const QString& source = "SCONOSCIUTO"); //explicit per evitare conversioni implicite da QString a JsonParser
    
    static QJsonObject AttivitaToJson(const Attivita&);
    static std::unique_ptr<Attivita> JsonToAttivita(const QJsonObject&);

    static QString frequenzaToString(Frequenza);    
    static Frequenza stringToFrequenza(const QString&);
};

#endif // JSONPARSER_H