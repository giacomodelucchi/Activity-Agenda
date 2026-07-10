#ifndef VISTAIUTO_H
#define VISTAIUTO_H

#include <QWidget>

class VistaAiuto : public QWidget{
    Q_OBJECT

public:
    explicit VistaAiuto(QWidget* parent = nullptr);

signals:
    void backRequested();
};

#endif // VISTAIUTO_H