#include "mainwindow.h"
#include <QApplication>
#include "basicComponents.h"
#include "objLoader.h"
#include "optionwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow three2two;

    optionWindow w;
    w.show();

    return a.exec();
}
