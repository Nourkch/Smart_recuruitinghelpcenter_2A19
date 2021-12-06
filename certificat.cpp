#include "certificat.h"
#include "connection.h"


certificat::certificat()
{
    idcertif=0;
    categorie="";
    cible="";
    titre="";

    }

certificat::certificat (int idcertif,QString categorie,QString cible,QString titre)
{   this->idcertif=idcertif;
    this->categorie=categorie;
    this->cible=cible;
    this->titre=titre;
}
int certificat::getidcertif(){return idcertif;}
QString certificat::getcategorie(){return categorie;}
QString certificat::getcible(){return cible;}
QString certificat::gettitre(){return titre;}


void certificat::setidcertif(int idcertif){this->idcertif=idcertif;}
void certificat::setcategorie(QString categorie){this->categorie=categorie;}
void certificat::setcible(QString cible){this->cible=cible;}
void certificat::settitre(QString titre){this->titre=titre;}


bool certificat::ajouter()
{
    QString idcertif_string=QString::number(idcertif);
    QSqlQuery query;

          query.prepare("INSERT INTO certificat (idcertif, categorie, cible,titre) "
                        "VALUES (:idc, :categorie, :cible, :titre)");
          query.bindValue(0,idcertif_string);
          query.bindValue(1,categorie);
          query.bindValue(2,cible);
          query.bindValue(2,titre);

          return query.exec();

}
bool certificat::supprimer(int idcertif)
{
    QSqlQuery query;

          query.prepare("Delete from certificat where idcertif=:idcertif");

          query.bindValue(0,idcertif);

          return query.exec();



}
QSqlQueryModel* certificat::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


model->setQuery("SELECT *  FROM certificat");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("idcertif"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("categorie"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("cible"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("titre"));

  return model;
}

int idcertif();
QString getcategorie();
QString getcible();
QString gettitre();


void setidcertif(int);
void setcategorie(QString);
void setcible(QString);
void settitre(QString);

bool certificat::modifier(int idcertif )
{
    QSqlQuery query;

     QString res = QString::number(idcertif);


        query.prepare( "UPDATE certificat set categorie=:categorie ,cible=:cible,titre=:titre ;");
        query.bindValue(":idcertif",res );
        query.bindValue(":categorie", categorie);
        query.bindValue(":cible",cible);
        query.bindValue(":titre",titre);


     return query.exec();
}
