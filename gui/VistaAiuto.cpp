#include "VistaAiuto.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStyle>

VistaAiuto::VistaAiuto(QWidget* parent) : QWidget(parent){
    auto* layout = new QVBoxLayout(this);

    QLabel* testo = new QLabel(
        tr(
            "<b>CREARE/CARICARE LE ATTIVITÀ:</b><br>"
            "Fai clic su Aggiungi o Carica JSON per aggiungere Attività<br><br>"
            "<b>UNA VOLTA CARICATE DELLE ATTIVITÀ:</b><br>"
            "• Clic su un'attività per visualizzarne i dettagli.<br>"
            "• Clic sull'intestazione di una colonna per ordinare le attività.<br>"
            "• Usa la barra di ricerca per filtrare.<br>"
            "• Il pulsante Elimina rimuove le attività selezionate.<br>"
            "• Puoi salvare le attività in un file JSON con Salva JSON<br><br>"
            "<b>LEGENDA COLORI:</b><br>"
            "• Il colore delle righe dipende dal tipo di attività.<br>"
            "• Le attività evidenziate in giallo sono le prossime in programma.<br>"
            "• Le attività con testo grigio sono già passate.<br>"
        ),
        this
    );

    testo->setWordWrap(true);

    QPushButton* backButton = new QPushButton(style()->standardIcon(QStyle::SP_ArrowBack), tr("Indietro"), this);

    layout->addWidget(testo);
    layout->addStretch();
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &VistaAiuto::backRequested);
}
