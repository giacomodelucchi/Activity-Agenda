#ifndef VISTAELENCOATTIVITA_H
#define VISTAELENCOATTIVITA_H

#include <QWidget>
#include <QVector>

class QLineEdit;        // per la barra di ricerca
class QTreeWidget;      // per la tabella delle attività
class QTreeWidgetItem;  // per gli elementi della tabella
class QLabel;
class QPushButton;
class QToolButton;

#include "../core/container/memoria.h"

class VistaElencoAttivita : public QWidget {
    Q_OBJECT

private:
    Memoria* memoria = nullptr;
    QLineEdit* search = nullptr;
    QTreeWidget* list = nullptr;
    QLabel* emptyStateLabel = nullptr;
    QPushButton* deleteButton = nullptr;
    QToolButton* addButton = nullptr;

public:
    enum ActivityType { // serve per distinguere i tipi di attività quando si aggiunge una nuova attività
        TipoEvento = 0,
        TipoEventoRicorrente = 1,
        TipoLista = 2
    };

    explicit VistaElencoAttivita(QWidget* parent = nullptr);
    void setMemoria(Memoria* m);
    void refreshList();
    QVector<unsigned int> selectedActivityIds() const;
    void clearSelection();

signals:
    void activitySelected(unsigned int id);
    void deleteSelectedRequested(const QVector<unsigned int>& ids);
    void addRequested(int type);

private slots:
    void onItemClicked(QTreeWidgetItem* item, int column);      // slot per gestire la selezione di un'attività dalla tabella
    void onSearchTextChanged(const QString& text);  // slot per filtrare la lista in base al testo di ricerca
    void onDeleteSelected();
    void onAddRequested(int type);
};

#endif // VISTAELENCOATTIVITA_H
