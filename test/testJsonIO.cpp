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
    if (!io.load(caricata)) {
        qWarning() << "runJsonIOTest: caricamento fallito";
        return false;
    }

    if (caricata.size() != 3) {
        qWarning() << "runJsonIOTest: numero attività caricate errato:" << caricata.size();
        return false;
    }

    const Attivita* a1 = caricata.cercaPerId(idEvento);
    const Evento* e1 = dynamic_cast<const Evento*>(a1);
    if (!e1) {
        qWarning() << "runJsonIOTest: evento 1 non trovato o cast fallito";
        return false;
    }
    if (e1->getTitolo() != titoloEvento || e1->getLuogo() != luogoEvento || e1->getOrario() != orarioEvento || e1->getDescrizione() != descrizioneEvento) {
        qWarning() << "runJsonIOTest: evento 1 dati errati";
        qWarning() << "atteso:" << titoloEvento << luogoEvento << orarioEvento.toString(Qt::ISODate) << descrizioneEvento;
        qWarning() << "trovato:" << e1->getTitolo() << e1->getLuogo() << e1->getOrario().toString(Qt::ISODate) << e1->getDescrizione();
        return false;
    }

    const Attivita* a2 = caricata.cercaPerId(idEventoRicorrente);
    const EventoRicorrente* er2 = dynamic_cast<const EventoRicorrente*>(a2);
    if (!er2) {
        qWarning() << "runJsonIOTest: evento ricorrente 2 non trovato o cast fallito";
        return false;
    }
    if (er2->getTitolo() != titoloEventoRicorrente || er2->getLuogo() != luogoEventoRicorrente || er2->getOrario() != orarioEventoRicorrente || er2->getDescrizione() != descrizioneEventoRicorrente
        || er2->getFrequenza() != frequenzaRicorrente || er2->getNumOccorrenze() != numOccorrenzeRicorrente || er2->isIllimitata() != illimitataRicorrente) {
        qWarning() << "runJsonIOTest: evento ricorrente 2 dati errati";
        qWarning() << "atteso:" << titoloEventoRicorrente << luogoEventoRicorrente << orarioEventoRicorrente.toString(Qt::ISODate)
                   << descrizioneEventoRicorrente << frequenzaToString(frequenzaRicorrente) << numOccorrenzeRicorrente << illimitataRicorrente;
        qWarning() << "trovato:" << er2->getTitolo() << er2->getLuogo() << er2->getOrario().toString(Qt::ISODate)
                   << er2->getDescrizione() << frequenzaToString(er2->getFrequenza()) << er2->getNumOccorrenze() << er2->isIllimitata();
        return false;
    }

    const Attivita* a3 = caricata.cercaPerId(idLista);
    const Lista* l3 = dynamic_cast<const Lista*>(a3);
    if (!l3) {
        qWarning() << "runJsonIOTest: lista 3 non trovata o cast fallito";
        return false;
    }
    if (l3->getTitolo() != titoloLista || l3->getLuogo() != luogoLista || l3->getOrario() != orarioLista || l3->numeroVoci() != static_cast<unsigned int>(elementi.size())) {
        qWarning() << "runJsonIOTest: lista 3 dati errati";
        qWarning() << "atteso:" << titoloLista << luogoLista << orarioLista.toString(Qt::ISODate) << elementi.size();
        qWarning() << "trovato:" << l3->getTitolo() << l3->getLuogo() << l3->getOrario().toString(Qt::ISODate) << l3->numeroVoci();
        return false;
    }
    for (unsigned int i = 0; i < elementi.size(); ++i) {
        const VoceLista& expectedVoce = elementi[static_cast<int>(i)];
        const VoceLista& actualVoce = l3->getVoce(i);
        if (expectedVoce.getTesto() != actualVoce.getTesto() || expectedVoce.isCompletata() != actualVoce.isCompletata()) {
            qWarning() << "runJsonIOTest: voce lista" << i << "diversa";
            qWarning() << "atteso:" << expectedVoce.getTesto() << expectedVoce.isCompletata();
            qWarning() << "trovato:" << actualVoce.getTesto() << actualVoce.isCompletata();
            return false;
        }
    }

    qDebug() << "runJsonIOTest: OK";
    return true;
}
