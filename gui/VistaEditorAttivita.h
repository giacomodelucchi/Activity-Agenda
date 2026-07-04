#ifndef VISTAEDITORATTIVITA_H
#define VISTAEDITORATTIVITA_H

#include <QWidget>

class QLineEdit;
class QTextEdit;
class QPushButton;
class QLabel;
class QTreeWidget;
class QDateTimeEdit;

#include "../core/gerarchia/attivita.h"

class VistaEditorAttivita : public QWidget {
    Q_OBJECT
public:
    explicit VistaEditorAttivita(QWidget* parent = nullptr);
    void editActivity(Attivita* a);
    bool hasUnsavedChanges() const;

signals:
    void saved(unsigned int id);
    void cancelled(unsigned int id);

private slots:
    void onSave();
    void onCancel();
    void markDirty();

private:
    Attivita* current = nullptr;
    QLineEdit* titleEdit = nullptr;
    QTextEdit* descriptionEdit = nullptr;
    QLineEdit* locationEdit = nullptr;
    QDateTimeEdit* dateTimeEdit = nullptr;
    QLabel* itemsLabel = nullptr;
    QTreeWidget* itemList = nullptr;
    QPushButton* saveButton = nullptr;
    QPushButton* cancelButton = nullptr;
    bool dirty = false;
};

#endif // VISTAEDITORATTIVITA_H
