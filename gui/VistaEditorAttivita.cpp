#include "VistaEditorAttivita.h"

VistaEditorAttivita::VistaEditorAttivita(QWidget* parent)
    : QWidget(parent)
{
    auto* mainLayout = new QVBoxLayout(this);
    formLayout = new QFormLayout();

    titleEdit = new QLineEdit(this);
    titleEdit->setPlaceholderText(tr("Titolo"));

    descriptionEdit = new QTextEdit(this);
    descriptionEdit->setPlaceholderText(tr("Descrizione"));
    descriptionEdit->setAcceptRichText(false);

    locationEdit = new QLineEdit(this);
    locationEdit->setPlaceholderText(tr("Luogo"));

    dateTimeEdit = new QDateTimeEdit(this);
    dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
    dateTimeEdit->setCalendarPopup(true);

    listaEditor = new VistaEditorLista(this);
    listaEditor->hide();

    frequenzaCombo = new QComboBox(this);
    frequenzaCombo->addItem("Nessuna");
    frequenzaCombo->addItem("Giornaliera");
    frequenzaCombo->addItem("Settimanale");
    frequenzaCombo->addItem("Mensile");
    frequenzaCombo->addItem("Annuale");
    numOccorrenzeSpin = new QSpinBox(this);
    numOccorrenzeSpin->setMinimum(1);
    numOccorrenzeSpin->setMaximum(1000);
    illimitataCheck = new QCheckBox(tr("Ricorrenza illimitata"), this);

    saveButton = new QPushButton(tr("Salva"), this);
    cancelButton = new QPushButton(tr("Annulla"), this);

    QLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(saveButton);
    buttonLayout->addWidget(cancelButton);

    formLayout->addRow(tr("Titolo:"), titleEdit);
    formLayout->addRow(tr("Descrizione:"), descriptionEdit);
    formLayout->addRow(tr("Luogo:"), locationEdit);
    formLayout->addRow(tr("Orario:"), dateTimeEdit);
    
    formLayout->addRow(tr("Frequenza:"), frequenzaCombo);
    formLayout->addRow(tr("Numero occorrenze:"), numOccorrenzeSpin);
    formLayout->addRow("", illimitataCheck);
    formLayout->labelForField(frequenzaCombo)->setVisible(false);
    formLayout->labelForField(numOccorrenzeSpin)->setVisible(false);

    frequenzaCombo->hide();
    numOccorrenzeSpin->hide();
    illimitataCheck->hide();

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(listaEditor);
    mainLayout->addLayout(buttonLayout);

    connect(saveButton, &QPushButton::clicked, this, &VistaEditorAttivita::onSave);
    connect(cancelButton, &QPushButton::clicked, this, &VistaEditorAttivita::onCancel);
    connect(titleEdit, &QLineEdit::textChanged, this, &VistaEditorAttivita::markDirty);
    connect(descriptionEdit, &QTextEdit::textChanged, this, &VistaEditorAttivita::markDirty);
    connect(locationEdit, &QLineEdit::textChanged, this, &VistaEditorAttivita::markDirty);
    connect(dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &VistaEditorAttivita::markDirty);
    connect(listaEditor, &VistaEditorLista::modified, this, &VistaEditorAttivita::markDirty);
    connect(illimitataCheck, &QCheckBox::toggled, numOccorrenzeSpin, &QSpinBox::setDisabled);
}

void VistaEditorAttivita::editActivity(Attivita* a)
{
    current = a;
    dirty = false;

    // nasconde i campi specifici per di EventoRicorrente e Lista
    formLayout->labelForField(frequenzaCombo)->hide();
    frequenzaCombo->hide();
    formLayout->labelForField(numOccorrenzeSpin)->hide();
    numOccorrenzeSpin->hide();
    illimitataCheck->hide();
    listaEditor->hide();

    // Popola i campi dell'editor con i dati dell'attività corrente
    titleEdit->setText(a->getTitolo());
    formLayout->labelForField(descriptionEdit)->show();
    descriptionEdit->show();
    descriptionEdit->clear();
    locationEdit->clear();
    dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    saveButton->setEnabled(true);
    cancelButton->setEnabled(true);

    if (const EventoRicorrente* er = dynamic_cast<const EventoRicorrente*>(a)) {
        descriptionEdit->setText(er->getDescrizione());
        locationEdit->setText(er->getLuogo());
        dateTimeEdit->setDateTime(er->getOrario());
        frequenzaCombo->setCurrentIndex(static_cast<int>(er->getFrequenza()));
        numOccorrenzeSpin->setValue(er->getNumOccorrenze());
        illimitataCheck->setChecked(er->isIllimitata());
        
        formLayout->labelForField(frequenzaCombo)->show();
        frequenzaCombo->show();
        formLayout->labelForField(numOccorrenzeSpin)->show();
        numOccorrenzeSpin->show();
        illimitataCheck->show();

    } else if (const Evento* ev = dynamic_cast<const Evento*>(a)) {
        descriptionEdit->setText(ev->getDescrizione());
        locationEdit->setText(ev->getLuogo());
        dateTimeEdit->setDateTime(ev->getOrario());

    } else if (Lista* lista = dynamic_cast<Lista*>(a)) {
        formLayout->labelForField(descriptionEdit)->hide();
        descriptionEdit->hide();
        listaEditor->setLista(lista);
        listaEditor->show();
    } else {
        descriptionEdit->setVisible(true);
    }
}

void VistaEditorAttivita::onSave()
{
    if (!current) return;
    current->setTitolo(titleEdit->text());

    if (auto* er = dynamic_cast<EventoRicorrente*>(current)) {
        er->setDescrizione(descriptionEdit->toPlainText());
        er->setLuogo(locationEdit->text());
        er->setOrario(dateTimeEdit->dateTime());
        er->setFrequenza(static_cast<Frequenza>(frequenzaCombo->currentIndex()));
        er->setNumOccorrenze(numOccorrenzeSpin->value());
        er->setIllimitata(illimitataCheck->isChecked());
    }
    else if (auto* ev = dynamic_cast<Evento*>(current)) {
        ev->setDescrizione(descriptionEdit->toPlainText());
        ev->setLuogo(locationEdit->text());
        ev->setOrario(dateTimeEdit->dateTime());
    }
    if (auto* lista = dynamic_cast<Lista*>(current)) {
        lista->setLuogo(locationEdit->text());
        lista->setOrario(dateTimeEdit->dateTime());
    }

    dirty = false;
    emit saved(current->getId());
}

void VistaEditorAttivita::onCancel()
{
    if (!current) return;
    dirty = false;
    emit cancelled(current->getId());
}

void VistaEditorAttivita::markDirty()
{
    if (!current) return;
    dirty = true;
}

bool VistaEditorAttivita::hasUnsavedChanges() const
{
    return dirty;
}
