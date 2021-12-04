#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>
#include <QString>
#include <QSqlQueryModel>
#include <QFileDialog>
#include <QDebug>
#include <QBuffer>
#include <QSqlQuery>
#include <QRegularExpression>
#include <cstdlib>
#include <iostream>
#include <map>
#include <QStringListModel>
#include <QList>
#include <QListView>
//#include "conge.h"
#include <QVector>




class Employe
{
private:

    QString nom;
    QString prenom;
    QString login;
    QString motDePasse;
    QString adresseMail;
    QString adresse;
    QString dateNaissance;
    int cin;
    QString service;
    QString sexe;
    int nss;
public:



    Employe();
    Employe(QString nom, QString prenom, QString login, QString motDePasse ,QString adresseMail, QString adresse, QString dateNaissance, QString service, QString sexe, int nss,  int cin);
    ~Employe();
    bool AjoutEmploye();
    void ModifierEmploye();
    bool SupprimerEmploye();
    bool RechercherInstEmploye(unsigned long long);
    QSqlQueryModel *AfficherEmploye();
    bool RechercherEmployeParNom(QString);
    QVector <QString> AfficheEmployeParNom(QString);
    bool RechercherEmployeParNomPrenom(QString,QString);

    void SetNom(QString nom)
        {
            this->nom = nom;
        }
        QString GetNom()
        {
            return this->nom;
        }
        void SetPrenom(QString prenom)
        {
            this->prenom = prenom;
        }
        QString GetPrenom()
        {
            return this->prenom;
        }

        void SetLogin(QString login)
        {
            this->login = login;
        }
        QString GetLogin()
        {
            return this->login;
        }

        void SetMotDePasse(QString motDePasse)
        {
            this->motDePasse = motDePasse;
        }
        QString GetMotDePasse()
        {
            return this->motDePasse;
        }

        void SetAdresseMail(QString adresseMail)
        {
            this->adresseMail = adresseMail;
        }
        QString GetAdresseMail()
        {
            return this->adresseMail;
        }
        void SetAdresse(QString adresse)
        {
            this->adresse = adresse;
        }
        QString GetAdresse()
        {
            return this->adresse;
        }
        void SetDateNaissance(QString dateNaissance)
        {
            this->dateNaissance = dateNaissance;
        }
        QString GetDateNaissance()
        {
            return this->dateNaissance;
        }

        void SetService(QString service)
        {
            this->service = service;
        }
        QString GetService()
        {
            return this->service;
        }
        void SetSexe(QString sexe)
        {
            this->sexe = sexe;
        }
        QString GetSexe()
        {
            return this->sexe;
        }


        void SetNss(int nss)
            {
               this->nss = nss;
            }
            int GetNss()
            {
                return this->nss;
            }
            void SetCin(int cin)
            {
                this->cin = cin;
            }
            int GetCin()
            {
                return this->cin;
            }



};

#endif // EMPLOYE_H
