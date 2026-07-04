#ifndef VISTADETTAGLIOATTIVITA_H
#define VISTADETTAGLIOATTIVITA_H

#include <QWidget>

class QLabel;
class QPushButton;

#include "../core/gerarchia/attivita.h"

class VistaDettaglioAttivita : public QWidget {
    Q_OBJECT
public:
    explicit VistaDettaglioAttivita(QWidget* parent = nullptr);
    void setActivity(const Attivita* a);

signals:
    void editRequested(unsigned int id);
    void deleteRequested(unsigned int id);
    void backRequested();

private slots:
    void onEdit();
    void onDelete();
    void onBack();

private:
    const Attivita* current = nullptr;
    QLabel* titleLabel = nullptr;
    QLabel* detailsLabel = nullptr;
    QPushButton* editButton = nullptr;
    QPushButton* deleteButton = nullptr;
    QPushButton* backButton = nullptr;
};

#endif // VISTADETTAGLIOATTIVITA_H
