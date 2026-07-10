#include "VistaEditorLista.h"




VistaEditorLista::VistaEditorLista(QWidget* parent) 
    : QWidget(parent){

    auto* layout = new QGridLayout(this);
    voceList = new QListWidget(this);

    // permette modifica con doppio click
    voceList->setEditTriggers(
        QAbstractItemView::DoubleClicked
    );

    auto* editorListaLabel = new QLabel("Voci della lista:", this);

    addButton = new QPushButton(tr("Aggiungi voce"), this);
    removeButton = new QPushButton(tr("Elimina voce"), this);
    removeButton->setEnabled(false);
    
    auto* buttons = new QVBoxLayout();
    buttons->addWidget(addButton);
    buttons->addWidget(removeButton);

    layout->addWidget(editorListaLabel, 0, 0);
    layout->addWidget(voceList, 1, 0);
    layout->addLayout(buttons, 1, 1);

    connect(addButton, &QPushButton::clicked, this, &VistaEditorLista::aggiungiVoce);
    connect(removeButton, &QPushButton::clicked, this, &VistaEditorLista::eliminaVoce);
    connect(voceList, &QListWidget::itemChanged, this, &VistaEditorLista::aggiornaVoce);
    connect(voceList, &QListWidget::itemSelectionChanged, this, &VistaEditorLista::aggiornaPulsanteElimina);
}

void VistaEditorLista::setLista(Lista* lista){

    currentLista = lista;
    aggiornaVista();
}

void VistaEditorLista::aggiornaVista(){

    voceList->clear();

    if (!currentLista){
        removeButton->setEnabled(false);
        return;
    }

    unsigned int numVoci = currentLista->numeroVoci();
    for(unsigned int i = 0; i < numVoci; ++i){
        const VoceLista& voce = currentLista->getVoce(i);
        auto* item = new QListWidgetItem(voce.getTesto());

        item->setFlags(item->flags() | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
        item->setCheckState(voce.isCompletata()? Qt::Checked : Qt::Unchecked);
        voceList->addItem(item);
    }

    voceList->clearSelection();
    aggiornaPulsanteElimina();
}

void VistaEditorLista::aggiungiVoce(){

    if(!currentLista)
        return;

    currentLista->aggiungiVoce(VoceLista(""));  //aggiunta di una voce vuota

    aggiornaVista();

    voceList->setCurrentRow(voceList->count()-1);   
    voceList->editItem(voceList->currentItem());

    emit modified();
}

void VistaEditorLista::eliminaVoce(){

    if(!currentLista)
        return;


    int indice = voceList->currentRow();
   
    if(indice < 0)
        return;

    currentLista->rimuoviVoce(indice);
    aggiornaVista();
    voceList->clearSelection(); 
    emit modified();
}

void VistaEditorLista::aggiornaVoce(QListWidgetItem* item){

    if(!currentLista)
        return;

    int indice = voceList->row(item);
    QVector<VoceLista> voci;    

    for(unsigned int i=0; i < currentLista->numeroVoci(); ++i){
        voci.append(currentLista->getVoce(i));
    }

    voci[indice].setTesto(item->text());

    voci[indice].setCompletata(item->checkState() == Qt::Checked);
    
    currentLista->setElementi(voci);

    emit modified(); 
}

/*  se c'è una voce della lista viene selezionata viene abilitato il pulsante "Elimina voce", 
quando non c'è nessuna voce selezionata il pulsante viene disabilitato */
void VistaEditorLista::aggiornaPulsanteElimina(){
    removeButton->setEnabled( voceList->currentItem() != nullptr);
}
