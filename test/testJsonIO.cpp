#include "testJsonIO.h"
#include "../core/jsonIO/jsonParser.h"
#include "../core/gerarchia/evento.h"
#include "../core/gerarchia/eventoRicorrente.h"
#include "../core/gerarchia/lista.h"
#include "../core/gerarchia/voceLista.h"

#include <QDebug>
#include <QDateTime>
#include <QTime>
#include <QVector>

namespace {
class ActivityVerifier : public AttivitaConstVisitor {
public:
    enum class ExpectedType { Evento, EventoRicorrente, Lista };

    ActivityVerifier(ExpectedType expectedType,
                     const QString& expectedTitolo,
                     const QString& expectedLuogo,
                     const QDateTime& expectedOrario,
                     const QString& expectedDescrizione = QString(),
                     Frequenza expectedFrequenza = Frequenza::Nessuna,
                     unsigned int expectedNumOccorrenze = 0,
                     bool expectedIllimitata = false,
                     const QVector<VoceLista>& expectedElementi = {})
        : expectedType(expectedType),
          expectedTitolo(expectedTitolo),
          expectedLuogo(expectedLuogo),
          expectedOrario(expectedOrario),
          expectedDescrizione(expectedDescrizione),
          expectedFrequenza(expectedFrequenza),
          expectedNumOccorrenze(expectedNumOccorrenze),
          expectedIllimitata(expectedIllimitata),
          expectedElementi(expectedElementi) {}

    void visit(const Evento& evento) override {
        matches = expectedType == ExpectedType::Evento
            && evento.getTitolo() == expectedTitolo
            && evento.getLuogo() == expectedLuogo
            && evento.getOrario() == expectedOrario
            && evento.getDescrizione() == expectedDescrizione;
    }

    void visit(const EventoRicorrente& evento) override {
        matches = expectedType == ExpectedType::EventoRicorrente
            && evento.getTitolo() == expectedTitolo
            && evento.getLuogo() == expectedLuogo
            && evento.getOrario() == expectedOrario
            && evento.getDescrizione() == expectedDescrizione
            && evento.getFrequenza() == expectedFrequenza
            && evento.getNumOccorrenze() == expectedNumOccorrenze
            && evento.isIllimitata() == expectedIllimitata;
    }

    void visit(const Lista& lista) override {
        matches = expectedType == ExpectedType::Lista
            && lista.getTitolo() == expectedTitolo
            && lista.getLuogo() == expectedLuogo
            && lista.getOrario() == expectedOrario
            && lista.numeroVoci() == static_cast<unsigned int>(expectedElementi.size());

        for (unsigned int i = 0; matches && i < lista.numeroVoci(); ++i) {
            const VoceLista& expectedVoce = expectedElementi[static_cast<int>(i)];
            const VoceLista& actualVoce = lista.getVoce(i);
            matches = expectedVoce.getTesto() == actualVoce.getTesto()
                && expectedVoce.isCompletata() == actualVoce.isCompletata();
        }
    }

    bool matches = false;

private:
    ExpectedType expectedType;
    QString expectedTitolo;
    QString expectedLuogo;
    QDateTime expectedOrario;
    QString expectedDescrizione;
    Frequenza expectedFrequenza;
    unsigned int expectedNumOccorrenze;
    bool expectedIllimitata;
    QVector<VoceLista> expectedElementi;
};
}

bool runJsonIOTest(const QString& jsonFilePath) {
    const unsigned int idEvento = 1;
    const unsigned int idEventoRicorrente = 2;
    const unsigned int idLista = 3;

    const QString titoloEvento = QStringLiteral("Riunione progetto");
    const QString luogoEvento = QStringLiteral("Sala A");
    const QDateTime orarioEvento = QDateTime(QDate(2026, 12, 25), QTime(15, 30, 0));
    const QString descrizioneEvento = QStringLiteral("Allineare il lancio del progetto e confermare le risorse.");

    const QString titoloEventoRicorrente = QStringLiteral("Allenamento");
    const QString luogoEventoRicorrente = QStringLiteral("Palestra");
    const QDateTime orarioEventoRicorrente = QDateTime(QDate(2026, 11, 2), QTime(8, 35, 0));
    const QString descrizioneEventoRicorrente = QStringLiteral("Sessione settimanale per migliorare la resistenza.");
    const Frequenza frequenzaRicorrente = Frequenza::Settimanale;
    const unsigned int numOccorrenzeRicorrente = 8;
    const bool illimitataRicorrente = false;

    const QString titoloLista = QStringLiteral("Lista spesa");
    const QString luogoLista = QStringLiteral("Negozio");
    const QDateTime orarioLista = QDateTime(QDate(2026, 9, 30), QTime(18, 0, 0));

    Memoria memoria;
    memoria.aggiungi(std::make_unique<Evento>(
        idEvento,
        titoloEvento,
        luogoEvento,
        orarioEvento,
        descrizioneEvento));

    memoria.aggiungi(std::make_unique<EventoRicorrente>(
        idEventoRicorrente,
        titoloEventoRicorrente,
        luogoEventoRicorrente,
        orarioEventoRicorrente,
        descrizioneEventoRicorrente,
        frequenzaRicorrente,
        numOccorrenzeRicorrente,
        illimitataRicorrente
    ));

    QVector<VoceLista> elementi;
    elementi.append(VoceLista(QStringLiteral("Comprare latte"), false));
    elementi.append(VoceLista(QStringLiteral("Chiamare Marco"), true));

    memoria.aggiungi(std::make_unique<Lista>(
        idLista,
        titoloLista,
        luogoLista,
        orarioLista,
        elementi
    ));

    JsonIO io(jsonFilePath);
    if (!io.save(memoria)) {
        qWarning() << "runJsonIOTest: salvataggio fallito";
        return false;
    }

    Memoria caricata;
    if (io.load(caricata) == JsonIO::LoadResult::Failed) {
        qWarning() << "runJsonIOTest: caricamento fallito";
        return false;
    }

    if (caricata.size() != 3) {
        qWarning() << "runJsonIOTest: numero attività caricate errato:" << caricata.size();
        return false;
    }

    const Attivita* a1 = caricata.cercaPerId(idEvento);
    ActivityVerifier eventoVerifier(
        ActivityVerifier::ExpectedType::Evento,
        titoloEvento, luogoEvento, orarioEvento, descrizioneEvento);
    if (!a1) {
        qWarning() << "runJsonIOTest: evento 1 non trovato";
        return false;
    }
    a1->accept(eventoVerifier);
    if (!eventoVerifier.matches) {
        qWarning() << "runJsonIOTest: evento 1 dati errati";
        return false;
    }

    const Attivita* a2 = caricata.cercaPerId(idEventoRicorrente);
    ActivityVerifier ricorrenteVerifier(
        ActivityVerifier::ExpectedType::EventoRicorrente,
        titoloEventoRicorrente, luogoEventoRicorrente, orarioEventoRicorrente,
        descrizioneEventoRicorrente, frequenzaRicorrente,
        numOccorrenzeRicorrente, illimitataRicorrente);
    if (!a2) {
        qWarning() << "runJsonIOTest: evento ricorrente 2 non trovato";
        return false;
    }
    a2->accept(ricorrenteVerifier);
    if (!ricorrenteVerifier.matches) {
        qWarning() << "runJsonIOTest: evento ricorrente 2 dati errati";
        return false;
    }

    const Attivita* a3 = caricata.cercaPerId(idLista);
    ActivityVerifier listaVerifier(
        ActivityVerifier::ExpectedType::Lista,
        titoloLista, luogoLista, orarioLista, QString(), Frequenza::Nessuna,
        0, false, elementi);
    if (!a3) {
        qWarning() << "runJsonIOTest: lista 3 non trovata";
        return false;
    }
    a3->accept(listaVerifier);
    if (!listaVerifier.matches) {
        qWarning() << "runJsonIOTest: lista 3 dati errati";
        return false;
    }

    qDebug() << "runJsonIOTest: OK";
    return true;
}
