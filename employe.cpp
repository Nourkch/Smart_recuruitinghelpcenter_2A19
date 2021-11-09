#include "employe.h"
#include <QDate>
employe::employe()
{
    ID=0;
    CIN=0;
    lastname="";
    firstname="";
    TEL=0;
    BDate=QDate::currentDate();
    sexe="";
    department="";

}

employe::employe(int id ,int Cin,QString lname,QString fname,int tel,QDate birthdate,QString Sexe,QString departement)
{
  this-> ID=id;
  this->lastname=lname;
  this-> firstname=fname;
    this->CIN=Cin;
    this->TEL=tel;
    //BDate = birthdate;

    this->BDate = birthdate;
    this->sexe=Sexe;
    this->department=departement;

}
bool employe::ajouter()
{
QSqlQuery query;
query.prepare("INSERT INTO emplye (cin,nom,prenom,id,date_naissance,sexe,departement) "
                    "VALUES (:cin,:nom, :prenom,:id,:date_naissance,:sexe,:departement)");

query.bindValue(":cin", CIN);
query.bindValue(":nom", lastname);
query.bindValue(":prenom", firstname);
query.bindValue(":id", ID);
query.bindValue(":date_naissance", BDate);
query.bindValue(":sexe", sexe);
query.bindValue(":departement", department);
return    query.exec();
}


QSqlQueryModel * employe::afficher()
{QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from employe");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("id"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("nom"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("prenom"));
return model;
}
bool employe::supprimer(int id)
{
QSqlQuery query;
QString res= QString::number(id);
query.prepare("Delete from employe where id = :id ");
query.bindValue(":id", res);
return    query.exec();
}
bool employe::modifier(int)
{   QSqlQuery query;
    query.prepare( "UPDATE employe SET  nom=:nom,prenom=:prenom,date_naissance=:date_naissance,departement= :departement WHERE id=:id");
    query.bindValue(":cin", CIN);
    query.bindValue(":nom", lastname);
    query.bindValue(":prenom", firstname);
    query.bindValue(":id", ID);
    query.bindValue(":date_naissance", BDate);
    query.bindValue(":sexe", sexe);
    query.bindValue(":departement", department);

 return query.exec();
}
