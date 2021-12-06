#ifndef COURS_H
#define COURS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class cours
{
public:
    cours();
    cours(int,QString,QString,QString);
    int getidc();
    QString getmatiere();
    QString gettemps();
    QString getduree();

    void setidc(int);
    void setmatiere(QString);
    void settemps(QString);
    void setduree(QString);



    bool ajouter();
    bool modifier(int);
    QSqlQueryModel * afficher();
    bool supprimer(int);

private:
    int idc;
    QString matiere,temps,duree;


};
#endif // COURS_H

