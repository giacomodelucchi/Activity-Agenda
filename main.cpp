#include <QApplication>
#include "gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // per testare la funzionalità della gerarchia di classi e della serializzazione JSON, decommentare le righe seguenti
    /*
    runJsonIOTest("test_activities.json");
    return 0;
    */

    MainWindow w;
    w.show();

    return a.exec();
}
