#ifndef EXAMEN_H
#define EXAMEN_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class examen
{
public:
    examen();
    examen(int,QString,QString,QString);
    int getide();
    QString getmatiere();
    QString getduree();
    QString getnote();

    void setide(int);
    void setmatiere(QString);
    void setduree(QString);
    void setnote(QString);



    bool ajouter();
    bool modifier(int);
    QSqlQueryModel * afficher();
    bool supprimer(int);

private:
    int ide;
    QString matiere,duree,note;

};

#endif // EXAMEN_H
