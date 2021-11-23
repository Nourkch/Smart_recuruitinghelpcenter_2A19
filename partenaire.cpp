#include "partenaire.h"
#include<QSqlQuery>
#include<QtDebug>
#include <QObject>
#include <QString>
#include <QSqlQueryModel>

partenaire::partenaire()
{
id=0;numero=0 ;nom="";adresse="";mail="";
}
partenaire::partenaire(int id,QString nom,QString adresse ,QString mail,int numero)//
{
  this->id=id;
  this->nom=nom;
  this->adresse=adresse;
  this->mail=mail;
  this->numero=numero;
}

QString partenaire::getnom(){return nom ;}
QString partenaire::getadresse(){return adresse ;}
QString  partenaire::getmail(){return mail ;}
int partenaire::getid(){return id ;}
int partenaire::getnumero(){return numero ;}

void partenaire:: setnom(QString nom ){this->nom=nom;}
void partenaire::setadresse(QString adresse ){this->adresse=adresse;}
void partenaire::setmail(QString mail ){this->mail=mail;}
void partenaire::setid(int id){this->id=id;}
void partenaire::setnumero(int numero){this->numero=numero;}

bool partenaire::ajouter()
{ bool test=false;
    QSqlQuery query;
    QString numero_string= QString::number(numero);
    QString id_string= QString::number(id);
          query.prepare("INSERT INTO PARTENAIRE (id, nom, adresse,mail,numero) "
                        "VALUES (:id, :nom, :adresse, :mail, :numero)");
          query.bindValue(":id", id_string);//ou 0
          query.bindValue(":nom", nom);
          query.bindValue(":adresse", adresse);
          query.bindValue(":mail", mail);
          query.bindValue(":numero", numero_string);

        return query.exec();

    return test;
}
QSqlQueryModel* partenaire::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM PARTENAIRE");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
         //new instance pour la securiter
         model->setHeaderData(3, Qt::Horizontal, QObject::tr("mail"));
         model->setHeaderData(4, Qt::Horizontal, QObject::tr("numero"));

  return model;
}
bool  partenaire::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("delete from PARTENAIRE where id=:id");
  query.bindValue(0, id);
return query.exec();

}
bool partenaire::update(int id, QString nom, QString adresse, QString mail, int numero)

              {

                  QSqlQuery query;



                  query.prepare("UPDATE PARTENAIRE SET id= :id,nom= :nom, adresse= :adresse, mail= :mail,numero= :numero WHERE id =:id");
                                                                                                  //c un modele preparer pour lexecution
                  query.bindValue(":id", id);                                                           //taatiti valeur binaire variable

                  query.bindValue(":nom", nom);

                  query.bindValue(":adresse", adresse);

                  query.bindValue(":mail", mail);

                  query.bindValue(":numero", numero);


                          return    query.exec();



              }
QSqlQueryModel* partenaire::rechercher (const QString &aux)

{
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("select * from PARTENAIRE where ((id||nom||adresse||mail||numero) LIKE '%"+aux+"%')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));

    model->setHeaderData(2, Qt::Horizontal, QObject::tr("adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("mail"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("numero"));

    return model;

}

