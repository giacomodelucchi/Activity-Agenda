#include "VistaEditorAttivita.h"

VistaEditorAttivita::VistaEditorAttivita(QWidget* parent): QWidget(parent){
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

void VistaEditorAttivita::editActivity(Attivita* a){
    if (!a) return;

    current = a;
    dirty = false;

    // nasconde i campi specifici per di EventoRicorrente e Lista
    formLayout->labelForField(frequenzaCombo)->hide();
    frequenzaCombo->hide();
    formLayout->labelForField(numOccorrenzeSpin)->hide();
    numOccorrenzeSpin->hide();
    illimitataCheck->hide();
    listaEditor->hide();

    // Popola i campi comuni dell'editor con i dati dell'attività corrente
    loadCommonFields(*a);
    formLayout->labelForField(descriptionEdit)->show();
    descriptionEdit->show();
    descriptionEdit->clear();
    saveButton->setEnabled(true);
    cancelButton->setEnabled(true);

    visitorMode = VisitorMode::Loading;
    a->accept(*this);
    dirty = false;
}

void VistaEditorAttivita::onSave(){
    if (!current) return;
    saveCommonFields(*current); //salva i campi comuni dell'attività corrente

    visitorMode = VisitorMode::Saving;
    current->accept(*this);

    dirty = false;
    emit saved(current->getId());
}

void VistaEditorAttivita::onCancel(){
    if (!current) return;
    dirty = false;
    emit cancelled(current->getId());
}

void VistaEditorAttivita::markDirty(){
    if (!current) return;
    dirty = true;
}

bool VistaEditorAttivita::hasUnsavedChanges() const{
    return dirty;
}

void VistaEditorAttivita::visit(Evento& evento){
    if (visitorMode == VisitorMode::Loading) {
        descriptionEdit->setText(evento.getDescrizione());
        return;
    }

    evento.setDescrizione(descriptionEdit->toPlainText());
}

void VistaEditorAttivita::visit(EventoRicorrente& evento){
    if (visitorMode == VisitorMode::Loading) {
        descriptionEdit->setText(evento.getDescrizione());
        frequenzaCombo->setCurrentIndex(static_cast<int>(evento.getFrequenza()));
        numOccorrenzeSpin->setValue(static_cast<int>(evento.getNumOccorrenze()));
        illimitataCheck->setChecked(evento.isIllimitata());

        formLayout->labelForField(frequenzaCombo)->show();
        frequenzaCombo->show();
        formLayout->labelForField(numOccorrenzeSpin)->show();
        numOccorrenzeSpin->show();
        illimitataCheck->show();
        return;
    }

    evento.setDescrizione(descriptionEdit->toPlainText());
    evento.setFrequenza(static_cast<Frequenza>(frequenzaCombo->currentIndex()));
    evento.setNumOccorrenze(static_cast<unsigned int>(numOccorrenzeSpin->value()));
    evento.setIllimitata(illimitataCheck->isChecked());
}

void VistaEditorAttivita::visit(Lista& lista){
    if (visitorMode == VisitorMode::Loading) {
        formLayout->labelForField(descriptionEdit)->hide();
        descriptionEdit->hide();
        listaEditor->setLista(&lista);
        listaEditor->show();
        return;
    }

    listaEditor->applyChanges(lista);
}

//funzioni per evitare la duplicazione del codice per caricare e salvare i campi comuni dell'attività
void VistaEditorAttivita::loadCommonFields(const Attivita& a)
{
    titleEdit->setText(a.getTitolo());
    locationEdit->setText(a.getLuogo());
    dateTimeEdit->setDateTime(a.getOrario());
}

void VistaEditorAttivita::saveCommonFields(Attivita& a)
{
    a.setTitolo(titleEdit->text());
    a.setLuogo(locationEdit->text());
    a.setOrario(dateTimeEdit->dateTime());
}