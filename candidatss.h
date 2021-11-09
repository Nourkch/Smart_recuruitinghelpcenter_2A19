#ifndef CANDIDATSS_H
#define CANDIDATSS_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>
#include <QSqlQuery>   // moyen pour manipuler l base
#include <QDebug>

class Candidatss
{
public:

    Candidatss();
    Candidatss(int cin,QString nom,QString prenom ,QString adressemail,QString sexe,QString rue,int codepostal,QDate date_naissance,QString ville);
    Candidatss(int id_candidat,int cin,QString nom,QString prenom ,QString adressemail,QString sexe,QString rue,int codepostal,QDate date_naissance,QString ville);


    // getters

    int getCIN();
       QString getnom();
        QString getprenom();
         QString getadressemail();
         QString getrue();
         int getcodepostal();
         QString getsexe();
         QString getville();
  int getID_candidat();
         QDate getDatenaissance();

         // setters

         void setCIN(int);
              void setnom(QString);
               void setprenom(QString);
               void setadressemail(QString);

               void setrue(QString);
               void setcodepostal(int);

               void setsexe(QString);
                void setDatenaissance(QDate);


                 void setville(QString);

// Cruds


                 bool ajouter_candidat();
                 QSqlQueryModel * afficher();
                 bool supprimer_candidat(int  id_candidat);
                 bool modifier_candidat();

private :

    QDate date_naissance;
    QString nom , prenom , email, sexe, rue,ville;
    int codepostal,cin,id_candidat;


};

#endif // CANDIDATSS_H
