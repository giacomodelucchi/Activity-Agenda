#include "jsonParser.h"
#include "../gerarchia/frequenza.h"

#include <QDateTime>
#include <QJsonValue>

//Costruttore
JsonParser::JsonParser(const QString& source)
    : source(source) {}

// ============================================================
// VISITOR
// ============================================================
void JsonParser::visit(const Evento& evento){
    result = eventoToJson(evento);
}

void JsonParser::visit(const EventoRicorrente& evento){
    result = eventoRicorrenteToJson(evento);
}

void JsonParser::visit(const Lista& lista){
    result = listaToJson(lista);
}


// ============================================================
// API PUBBLICA
// ============================================================

// costruisce un QJsonObject a partire da un'Attivita
QJsonObject JsonParser::AttivitaToJson(const Attivita& att) {
    JsonParser parser;

    // Il polimorfismo decide quale visit() chiamare.
    att.accept(parser);

    return parser.result;
}

// costruisce un'Attivita a partire da un QJsonObject
std::unique_ptr<Attivita> JsonParser::JsonToAttivita(const QJsonObject& obj) {
    const QString tipo = obj.value("tipo").toString();
    if (tipo == "EventoRicorrente") return jsonToEventoRicorrente(obj);
    if (tipo == "Evento") return jsonToEvento(obj);
    if (tipo == "Lista") return jsonToLista(obj);

    // se il tipo non è riconosciuto, ritorna nullptr
    qWarning() << "JsonParser::JsonToAttivita tipo non riconosciuto:" << tipo;
    return nullptr;
}

// ============================================================
// SERIALIZZAZIONE
// ============================================================

QJsonObject JsonParser::eventoToJson(const Evento& evento) {
    QJsonObject obj;
    obj["tipo"] = "Evento";
    obj["id"] = static_cast<int>(evento.getId());
    obj["titolo"] = evento.getTitolo();
    obj["luogo"] = evento.getLuogo();
    obj["orario"] = evento.getOrario().toString(Qt::ISODate);
    obj["descrizione"] = evento.getDescrizione();
    return obj;
}

QJsonObject JsonParser::eventoRicorrenteToJson(const EventoRicorrente& er) {
    QJsonObject obj = eventoToJson(er);
    obj["tipo"] = "EventoRicorrente";   //viene sovrascritto il tipo "Evento" con "EventoRicorrente"
    obj["frequenza"] = frequenzaToString(er.getFrequenza());
    obj["numOccorrenze"] = static_cast<int>(er.getNumOccorrenze());
    obj["illimitata"] = er.isIllimitata();
    return obj;
}

QJsonObject JsonParser::listaToJson(const Lista& lista) {
    QJsonObject obj;
    obj["tipo"] = "Lista";
    obj["id"] = static_cast<int>(lista.getId());
    obj["titolo"] = lista.getTitolo();
    obj["luogo"] = lista.getLuogo();
    obj["orario"] = lista.getOrario().toString(Qt::ISODate);

    QJsonArray arr;
    for (unsigned int i = 0; i < lista.numeroVoci(); ++i) {
        arr.append(voceListaToJson(lista.getVoce(i)));
    }
    obj["elementi"] = arr;
    return obj;
}

QJsonObject JsonParser::voceListaToJson(const VoceLista& voce) {
    QJsonObject obj;
    obj["testo"] = voce.getTesto();
    obj["completata"] = voce.isCompletata();
    return obj;
}

// ============================================================
// DESERIALIZZAZIONE
// ============================================================

std::unique_ptr<Attivita> JsonParser::jsonToEvento(const QJsonObject& obj) {
    unsigned int id = static_cast<unsigned int>(obj.value("id").toInt());
    QString titolo = obj.value("titolo").toString();
    QString luogo = obj.value("luogo").toString();
    QDateTime orario = QDateTime::fromString(obj.value("orario").toString(), Qt::ISODate);
    QString descrizione = obj.value("descrizione").toString();
    return std::make_unique<Evento>(id, titolo, luogo, orario, descrizione);
}

std::unique_ptr<Attivita> JsonParser::jsonToEventoRicorrente(const QJsonObject& obj) {
    unsigned int id = static_cast<unsigned int>(obj.value("id").toInt());
    QString titolo = obj.value("titolo").toString();
    QString luogo = obj.value("luogo").toString();
    QDateTime orario = QDateTime::fromString(obj.value("orario").toString(), Qt::ISODate);
    QString descrizione = obj.value("descrizione").toString();
    Frequenza f = stringToFrequenza(obj.value("frequenza").toString());
    unsigned int num = static_cast<unsigned int>(obj.value("numOccorrenze").toInt());
    bool ill = obj.value("illimitata").toBool();
    return std::make_unique<EventoRicorrente>(id, titolo, luogo, orario, descrizione, f, num, ill);
}

std::unique_ptr<Attivita> JsonParser::jsonToLista(const QJsonObject& obj) {
    unsigned int id = static_cast<unsigned int>(obj.value("id").toInt());
    QString titolo = obj.value("titolo").toString();
    QString luogo = obj.value("luogo").toString();
    QDateTime orario = QDateTime::fromString(obj.value("orario").toString(), Qt::ISODate);
    QVector<VoceLista> elementi;
    QJsonArray arr = obj.value("elementi").toArray();
    for (const QJsonValue& v : arr) {
        if (v.isObject()) elementi.append(jsonToVoceLista(v.toObject()));
    }
    return std::make_unique<Lista>(id, titolo, luogo, orario, elementi);
}

VoceLista JsonParser::jsonToVoceLista(const QJsonObject& obj) {
    QString testo = obj.value("testo").toString();
    bool comp = obj.value("completata").toBool();
    return VoceLista(testo, comp);
}

// Mappatura Frequenza <-> string
QString JsonParser::frequenzaToString(Frequenza f) {
    switch (f) {
        case Frequenza::Giornaliera: return "Giornaliera";
        case Frequenza::Settimanale: return "Settimanale";
        case Frequenza::Mensile:    return "Mensile";
        case Frequenza::Annuale:    return "Annuale";
        default:                    return "Nessuna";
    }
}

Frequenza JsonParser::stringToFrequenza(const QString& s) {
    if (s == "Giornaliera") return Frequenza::Giornaliera;
    if (s == "Settimanale") return Frequenza::Settimanale;
    if (s == "Mensile")    return Frequenza::Mensile;
    if (s == "Annuale")    return Frequenza::Annuale;
    return Frequenza::Nessuna;
}