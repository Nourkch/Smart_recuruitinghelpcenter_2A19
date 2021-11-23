#ifndef PARTENAIRE_H
#define PARTENAIRE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>



class partenaire
{

public:
    partenaire();
    partenaire(int,QString,QString,QString,int);
       //Getters

    int getid();

       QString getnom();
       QString getadresse();
       QString getmail();
       int getnumero();
       //setters
       void setid(int);
        void setnom(QString);
        void setadresse(QString);
        void setmail(QString);
        void setnumero(int);
        //fonctionnalites de base relatives a lentite etudiant
       bool ajouter();
       QSqlQueryModel * afficher();
       QSqlQueryModel* rechercher(const QString &aux);
       bool supprimer (int);
       bool update(int , QString ,QString ,QString,int );
private :
       QString nom,adresse,mail;
           int id,numero;

    };
    #endif // PARTENAIRE_H
