#include "jsonIO.h"

namespace {
bool isValidVoceLista(const QJsonValue& value)  //verifica se un oggetto JSON rappresenta una voce di lista valida
{
    if (!value.isObject()) return false;
    const QJsonObject obj = value.toObject();
    return obj.value("testo").isString()
        && obj.value("completata").isBool();
}

bool isValidActivityObject(const QJsonObject& obj)  //verifica se un oggetto JSON rappresenta un'attività valida
{
    const QString tipo = obj.value("tipo").toString();
    const bool commonFieldsValid = obj.value("id").isDouble()
        && obj.value("titolo").isString()
        && obj.value("luogo").isString()
        && obj.value("orario").isString();

    if (!commonFieldsValid) return false;

    if (tipo == "Evento" || tipo == "EventoRicorrente") {
        if (!obj.value("descrizione").isString()) return false;
        if (tipo == "EventoRicorrente") {
            if (!obj.value("frequenza").isString()
                || !obj.value("numOccorrenze").isDouble()
                || !obj.value("illimitata").isBool()) {
                return false;
            }

            const QString frequenza = obj.value("frequenza").toString();
            const bool frequenzaValida = frequenza == "Nessuna"
                || frequenza == "Giornaliera"
                || frequenza == "Settimanale"
                || frequenza == "Mensile"
                || frequenza == "Annuale";
            const int numOccorrenze = obj.value("numOccorrenze").toInt();
            return frequenzaValida
                && (obj.value("illimitata").toBool() || numOccorrenze > 0);
        }
        return true;
    }

    if (tipo == "Lista") {
        if (!obj.value("elementi").isArray()) return false;
        for (const QJsonValue& voce : obj.value("elementi").toArray()) {
            if (!isValidVoceLista(voce)) return false;
        }
        return true;
    }

    return false;
}
}

JsonIO::JsonIO(const QString& filePath) : filePath(filePath) {}

void JsonIO::setFilePath(const QString& newFilePath) {
    filePath = newFilePath;
}

QString JsonIO::getFilePath() const {
    return filePath;
}

bool JsonIO::save(const Memoria& memoria) const {
    QJsonArray array;
    memoria.perOgniAttivita([&array](const Attivita& att) { //passaggio di una lambda che converte ogni Attivita in QJsonObject e lo aggiunge all'array
        array.append(JsonParser::AttivitaToJson(att));
    });

    QJsonDocument documentoQJson(array);    //crea un documento JSON a partire dall'array di Attivita

    QFile file(filePath);   //apre il file per la scrittura

    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Impossibile aprire il file per scrittura:" << filePath;
        return false;
    }
    file.write(documentoQJson.toJson(QJsonDocument::Indented)); //scrive il documento JSON nel file con indentazione 
    file.close();
    return true;
}

JsonIO::LoadResult JsonIO::load(Memoria& activities) const {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Impossibile aprire il file per lettura:" << filePath;
        return LoadResult::Failed;
    }

    const QByteArray fileData = file.readAll();
    file.close();

    QJsonParseError parseError;
    const QJsonDocument documento = QJsonDocument::fromJson(fileData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Errore in JsonIO::load:" << parseError.errorString();
        return LoadResult::Failed;
    }

    if (!documento.isArray()) {
        qWarning() << "Errore in JsonIO::load: manca un array di Attivita nel file JSON";
        return LoadResult::Failed;
    }

    activities.svuotaMemoria(); // opzionale, se vuoi ricominciare da zero

    const QJsonArray array = documento.array(); //ottiene l'array di Attivita dal documento JSON
    bool partial = false;
    for (const QJsonValue& valore : array) {
        if (!valore.isObject()) {
            qWarning() << "Errore in JsonIO::load: un elemento non è un oggetto JSON";
            partial = true;
            continue;   //continua esaminando il prossimo elemento dell'array
        }

        const QJsonObject object = valore.toObject();
        if (!isValidActivityObject(object)) {
            qWarning() << "Errore in JsonIO::load: attività non valida";
            partial = true;
            continue;
        }

        std::unique_ptr<Attivita> att = JsonParser::JsonToAttivita(object);
        if (att) {
            if (!activities.aggiungi(std::move(att))) {
                qWarning() << "Errore in JsonIO::load: ID duplicato";
                partial = true;
            }
        } else {
            qWarning() << "Errore in JsonIO::load: tipo di attività non riconosciuto o parsing fallito";
            partial = true;
        }
    }

    return partial ? LoadResult::Partial : LoadResult::Success;
}
