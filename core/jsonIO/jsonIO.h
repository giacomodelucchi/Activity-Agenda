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
    enum class LoadResult {
        Success,
        Partial,    //il file è stato caricato, ma alcune attività non erano valide e sono state ignorate
        Failed
    };

    //Costruttore
    explicit JsonIO(const QString& filePath = QString());

    //Metodi set
    void setFilePath(const QString& newFilePath);

    //Metodi get
    QString getFilePath() const;
    
    //scrive sul file i dati di tutte le Attivita contenuti nel container
    bool save(const Memoria& activities) const;

    //legge il contenuto del file path, riempendo un container passato per riferimento
    LoadResult load(Memoria& activities) const; //ritorna Success se tutte le attività sono state caricate correttamente, Partial se alcune attività non erano valide e sono state ignorate, Failed se il caricamento è fallito
};

#endif //JSONIO_H
