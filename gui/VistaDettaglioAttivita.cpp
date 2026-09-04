#include "VistaDettaglioAttivita.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QStyle>

#include "../core/jsonIO/jsonParser.h"
#include "../core/gerarchia/evento.h"
#include "../core/gerarchia/eventoRicorrente.h"
#include "../core/gerarchia/lista.h"

VistaDettaglioAttivita::VistaDettaglioAttivita(QWidget* parent)
    : QWidget(parent)
{
    auto* mainLayout = new QVBoxLayout(this);
    auto* buttonLayout = new QHBoxLayout();
    mainLayout->setContentsMargins(12, 12, 12, 12);
    mainLayout->setSpacing(14);

    titleLabel = new QLabel(tr("Seleziona un'attività"), this);
    titleLabel->setWordWrap(true);
    titleLabel->setStyleSheet("font-weight: bold; font-size: 20px; color: #333;");

    detailsLabel = new QLabel(tr("Usa l'elenco per selezionare un'attività."), this);
    detailsLabel->setWordWrap(true);
    detailsLabel->setStyleSheet("font-size: 14px; color: #444; background: #f8f8ff; border: 1px solid #d6d9e0; border-radius: 8px; padding: 12px;");
    detailsLabel->setTextInteractionFlags(Qt::TextSelectableByMouse);

    editButton = new QPushButton(tr("Modifica"), this);
    deleteButton = new QPushButton(style()->standardIcon(QStyle::SP_TrashIcon), tr("Elimina"), this);
    backButton = new QPushButton(style()->standardIcon(QStyle::SP_ArrowBack), tr("Indietro"), this);

    buttonLayout->addWidget(backButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(detailsLabel);

    connect(editButton, &QPushButton::clicked, this, &VistaDettaglioAttivita::onEdit);
    connect(deleteButton, &QPushButton::clicked, this, &VistaDettaglioAttivita::onDelete);
    connect(backButton, &QPushButton::clicked, this, &VistaDettaglioAttivita::onBack);
}

//se il campo è vuoto, mostra un testo di default
QString VistaDettaglioAttivita::placeholder(const QString& value) const
{
    return value.trimmed().isEmpty()? tr("Non specificato"): value;
}

QString VistaDettaglioAttivita::formatCommonDetails(const Attivita& attivita, const QString& tipo) const
{
    QString testo;
    testo += tr("<b>Tipo:</b> %1<br>").arg(tipo);
    testo += tr("<b>Titolo:</b> %1<br>").arg(placeholder(attivita.getTitolo()));
    testo += tr("<b>Luogo:</b> %1<br>").arg(placeholder(attivita.getLuogo()));

    const QDateTime orario = attivita.getOrario();
    testo += tr("<b>Orario:</b> %1<br>").arg(
        orario.isValid()
            ? QLocale::system().toString(orario, QLocale::ShortFormat)
            : tr("Non specificato"));
    return testo;
}

void VistaDettaglioAttivita::setActivity(const Attivita* a)
{
    current = a;
    if (!a) {
        titleLabel->setText(tr("Nessuna attività selezionata"));
        detailsLabel->setText(tr("Seleziona un elemento dall'elenco a sinistra o torna all'elenco."));
        editButton->setEnabled(false);
        deleteButton->setEnabled(false);
        return;
    }
    titleLabel->setText(a->getTitolo());
    editButton->setEnabled(true);
    deleteButton->setEnabled(true);
    current->accept(*this);
}

void VistaDettaglioAttivita::onEdit()
{
    if (!current) return;
    emit editRequested(current->getId());
}

void VistaDettaglioAttivita::onDelete()
{
    if (!current) return;
    emit deleteRequested(current->getId());
}

void VistaDettaglioAttivita::onBack()
{
    emit backRequested();
}

/*
==============================================================================================
Implementazione dei metodi del Visitor per la visualizzazione dei dettagli delle attività
==============================================================================================
*/

void VistaDettaglioAttivita::visit(const Evento& evento){
    QString testo = formatCommonDetails(evento, tr("Evento"));
    testo += tr("<b>Descrizione:</b> %1").arg(placeholder(evento.getDescrizione()));

    detailsLabel->setText(testo);
}

void VistaDettaglioAttivita::visit(const EventoRicorrente& evento){
    QString testo = formatCommonDetails(evento, tr("Ricorrenza"));
    testo += tr("<b>Descrizione:</b> %1<br>").arg(placeholder(evento.getDescrizione()));
    testo += tr("<b>Frequenza:</b> %1<br>").arg(frequenzaToString(evento.getFrequenza()));

    if (evento.isIllimitata()) {
        testo += tr("<b>Occorrenze:</b> Illimitate");
    } else {
        testo += tr("<b>Occorrenze:</b> %1").arg(evento.getNumOccorrenze());
    }

    detailsLabel->setText(testo);
}

void VistaDettaglioAttivita::visit(const Lista& lista){
    QString testo = formatCommonDetails(lista, tr("Lista"));
    testo += tr("<b>Elementi:</b><br>");

    for (unsigned int i = 0; i < lista.numeroVoci(); ++i) {
        const VoceLista& voce = lista.getVoce(i);

        testo += QString("%1. %2%3<br>")
                     .arg(i + 1)
                     .arg(voce.getTesto())
                     .arg(voce.isCompletata() ? tr(" ✓") : "");
    }

    detailsLabel->setText(testo);
}

