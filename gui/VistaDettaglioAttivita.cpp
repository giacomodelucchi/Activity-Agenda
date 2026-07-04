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

    auto placeholder = [this](const QString& value){
        return value.trimmed().isEmpty() ? tr("Non specificato") : value;
    };

    titleLabel->setText(placeholder(a->getTitolo()));
    editButton->setEnabled(true);
    deleteButton->setEnabled(true);

    QString details;
    if (const EventoRicorrente* er = dynamic_cast<const EventoRicorrente*>(a)) {
        details += tr("Tipo: Ricorrenza\n");
        details += tr("Luogo: %1\n").arg(placeholder(er->getLuogo()));
        details += tr("Orario: %1\n").arg(er->getOrario().isValid()
            ? QLocale::system().toString(er->getOrario(), QLocale::ShortFormat)
            : tr("Non specificato"));
        details += tr("Descrizione: %1\n").arg(placeholder(er->getDescrizione()));
        details += tr("Frequenza: %1\n").arg(JsonParser::frequenzaToString(er->getFrequenza()));
        details += tr("Occorrenze: %1\n").arg(er->getNumOccorrenze());
        details += tr("Illimitata: %1").arg(er->isIllimitata() ? tr("Sì") : tr("No"));
    } else if (const Evento* ev = dynamic_cast<const Evento*>(a)) {
        details += tr("Tipo: Evento\n");
        details += tr("Luogo: %1\n").arg(placeholder(ev->getLuogo()));
        details += tr("Orario: %1\n").arg(ev->getOrario().isValid()
            ? QLocale::system().toString(ev->getOrario(), QLocale::ShortFormat)
            : tr("Non specificato"));
        details += tr("Descrizione: %1").arg(placeholder(ev->getDescrizione()));
    } else if (const Lista* lista = dynamic_cast<const Lista*>(a)) {
        details += tr("Tipo: Lista\n");
        details += tr("Luogo: %1\n").arg(placeholder(lista->getLuogo()));
        details += tr("Orario: %1\n").arg(lista->getOrario().isValid()
            ? QLocale::system().toString(lista->getOrario(), QLocale::ShortFormat)
            : tr("Non specificato"));
        details += tr("Voci (%1):\n").arg(lista->numeroVoci());
        for (unsigned int i = 0; i < lista->numeroVoci(); ++i) {
            const VoceLista& voce = lista->getVoce(i);
            details += QString("  %1 %2\n").arg(voce.isCompletata() ? QChar(0x2714) : QChar(0x2610)).arg(voce.getTesto().isEmpty() ? tr("Non specificato") : voce.getTesto());
        }
    } else {
        details += tr("Tipo: Attività generica\n");
    }

    detailsLabel->setText(details);
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
