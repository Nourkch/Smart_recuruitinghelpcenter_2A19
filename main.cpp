#include "mainwindow.h"
#include "gestion_annonces.h"
#include "connection.h"
#include <QApplication>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connection c;

    bool testConnection = c.createConnection();

    gestion_annonces w;

    if(testConnection){
        w.show();
    }
    else{
        QMessageBox::critical(nullptr,
                              QObject::tr("Failed to connect to Database"),
                              QObject::tr("Click OK to Exit"),
                              QMessageBox::Ok);

    }

    return a.exec();
}


// Khedma_aman_2021
