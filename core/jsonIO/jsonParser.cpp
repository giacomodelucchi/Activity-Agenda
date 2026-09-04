#include "jsonParser.h"
#include "../gerarchia/frequenza.h"

#include <QDateTime>
#include <QJsonValue>

namespace {
struct CommonActivityFields {
    unsigned int id;
    QString titolo;
    QString luogo;
    QDateTime orario;
};

QJsonObject commonFieldsToJson(const Attivita& attivita, const QString& tipo)
{
    QJsonObject obj;
    obj["tipo"] = tipo;
    obj["id"] = static_cast<int>(attivita.getId());
    obj["titolo"] = attivita.getTitolo();
    obj["luogo"] = attivita.getLuogo();
    obj["orario"] = attivita.getOrario().toString(Qt::ISODate);
    return obj;
}

CommonActivityFields commonFieldsFromJson(const QJsonObject& obj)
{
    return {
        static_cast<unsigned int>(obj.value("id").toInt()),
        obj.value("titolo").toString(),
        obj.value("luogo").toString(),
        QDateTime::fromString(obj.value("orario").toString(), Qt::ISODate)
    };
}
}

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
    QJsonObject obj = commonFieldsToJson(evento, "Evento");
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
    QJsonObject obj = commonFieldsToJson(lista, "Lista");

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
    const CommonActivityFields fields = commonFieldsFromJson(obj);
    return std::make_unique<Evento>(fields.id, fields.titolo, fields.luogo,
                                    fields.orario, obj.value("descrizione").toString());
}

std::unique_ptr<Attivita> JsonParser::jsonToEventoRicorrente(const QJsonObject& obj) {
    const CommonActivityFields fields = commonFieldsFromJson(obj);
    Frequenza f = stringToFrequenza(obj.value("frequenza").toString());
    unsigned int num = static_cast<unsigned int>(obj.value("numOccorrenze").toInt());
    bool ill = obj.value("illimitata").toBool();
    return std::make_unique<EventoRicorrente>(fields.id, fields.titolo, fields.luogo,
                                              fields.orario, obj.value("descrizione").toString(),
                                              f, num, ill);
}

std::unique_ptr<Attivita> JsonParser::jsonToLista(const QJsonObject& obj) {
    const CommonActivityFields fields = commonFieldsFromJson(obj);
    QVector<VoceLista> elementi;
    QJsonArray arr = obj.value("elementi").toArray();
    for (const QJsonValue& v : arr) {
        if (v.isObject()) elementi.append(jsonToVoceLista(v.toObject()));
    }
    return std::make_unique<Lista>(fields.id, fields.titolo, fields.luogo,
                                   fields.orario, elementi);
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