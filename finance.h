#ifndef FINANCE_H
#define FINANCE_H

#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>


class finance
{
public:

    finance();
    finance(QString,QString,int,int,int,QString);

    int getid();
    int getsalaire();
    int gettelephone();
    QString getnom();
    QString getprenom();
    QString getadress();
    void setid(int);
    void setsalaire(int);
    void settelephone(int);
    void setnom(QString);
    void setprenom(QString);
    void setadrss(QString);
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    bool modifier(QString,QString,int,int,int,QString);
      QSqlQueryModel * trier();
      QSqlQueryModel * trier1();
      QSqlQueryModel * trier2();
      QSqlQueryModel* rechercher(QString nom);




private :
    int id,salaire,telephone;
    QString nom , prenom,adress;

};

#endif // FINANCE_H
