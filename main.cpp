#include "mainwindow.h"
#include "gestion_annonces.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    gestion_annonces b;
    b.show();


    return a.exec();
}
