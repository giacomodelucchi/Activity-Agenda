#include "jsonIO.h"

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

bool JsonIO::load(Memoria& activities) const {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Impossibile aprire il file per lettura:" << filePath;
        return false;
    }

    const QByteArray fileData = file.readAll();
    file.close();

    QJsonParseError parseError;
    const QJsonDocument documento = QJsonDocument::fromJson(fileData, &parseError);
    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Errore in JsonIO::load:" << parseError.errorString();
        return false;
    }

    if (!documento.isArray()) {
        qWarning() << "Errore in JsonIO::load: manca un array di Attivita nel file JSON";
        return false;
    }

    activities.svuotaMemoria(); // opzionale, se vuoi ricominciare da zero

    const QJsonArray array = documento.array(); //ottiene l'array di Attivita dal documento JSON
    for (const QJsonValue& valore : array) {
        if (!valore.isObject()) {
            qWarning() << "Errore in JsonIO::load: un elemento non è un oggetto JSON";
            continue;   //continua esaminando il prossimo elemento dell'array
        }

        std::unique_ptr<Attivita> att = JsonParser::JsonToAttivita(valore.toObject());  
        if (att) {
            activities.aggiungi(std::move(att));
        } else {
            qWarning() << "Errore in JsonIO::load: tipo di attività non riconosciuto o parsing fallito";
        }
    }

    return true;
}
