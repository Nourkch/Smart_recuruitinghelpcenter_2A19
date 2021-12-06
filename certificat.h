#ifndef CERTIFICAT_H
#define CERTIFICAT_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class certificat
{
public:
    certificat();
    certificat(int,QString,QString,QString);
    int getidcertif();
    QString getcategorie();
    QString getcible();
    QString gettitre();

    void setidcertif(int);
    void setcategorie(QString);
    void setcible(QString);
    void settitre(QString);

    bool ajouter();
    bool modifier(int);
    QSqlQueryModel * afficher();
    bool supprimer(int);
private:
    int idcertif;
    QString categorie,titre,cible;

};
#endif // CERTIFICAT_H
