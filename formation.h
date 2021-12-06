#ifndef FORMATOION_H
#define FORMATOION_H


#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QTimer>
#include <QComboBox>
#include "cours.h"

class formation
{
public:
    formation();
    formation(int,QString,QString);
    int getidf();
    QString gettype();
    QString getperiode();

    void setidf(int);
    void settype(QString);
    void setperiode(QString);

    bool ajouter();
    bool modifier(int);
    QSqlQueryModel * afficher();
    bool supprimer(int);
    QSqlQueryModel * sort_formation();
    QSqlQueryModel * rechercher(int iden);

private:
    int idf;
    QString type,periode;


};

#endif // FORMATION_H
