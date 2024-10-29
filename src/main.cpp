#include "mainwindow.h"

#include <QApplication>

#include "preferences.h"

Preferences *Preferences ::instance = new Preferences();

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
