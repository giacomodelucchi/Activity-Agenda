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
    
    bool save(const QVector<Attivita*>& activities) const;
    bool load(QVector<Attivita*>& outActivities) const;

};