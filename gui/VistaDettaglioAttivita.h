#ifndef VISTADETTAGLIOATTIVITA_H
#define VISTADETTAGLIOATTIVITA_H

#include <QWidget>

class QLabel;
class QPushButton;

#include "../core/gerarchia/attivita.h"
#include "../core/gerarchia/attivitaConstVisitor.h"

class VistaDettaglioAttivita : public QWidget, public AttivitaConstVisitor {
    Q_OBJECT
public:
    explicit VistaDettaglioAttivita(QWidget* parent = nullptr);
    void setActivity(const Attivita* a);

    //Visitor
    void visit(const Evento&) override;
    void visit(const EventoRicorrente&) override;
    void visit(const Lista&) override;

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

    QString placeholder(const QString&) const;  //per mostrare un testo di default quando un campo è vuoto
};

#endif // VISTADETTAGLIOATTIVITA_H
