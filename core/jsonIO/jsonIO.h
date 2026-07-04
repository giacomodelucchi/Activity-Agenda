#ifndef JSONIO_H
#define JSONIO_H

#include "../container/memoria.h"
#include "jsonParser.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "../gerarchia/attivita.h"
class JsonIO {
private:
        QString filePath;
        JsonParser parser;
public:
    //Costruttore
    explicit JsonIO(const QString& filePath = QString());

    //Metodi set
    void setFilePath(const QString& newFilePath);

    //Metodi get
    QString getFilePath() const;
    
    //scrive sul file i dati di tutte le Attivita contenuti nel container
    bool save(const Memoria& activities) const;

    //legge il contenuto del file path, riempendo un container passato per riferimento
    bool load(Memoria& activities) const;
};

#endif //JSONIO_H
