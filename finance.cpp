
#include "finance.h"
#include<QIntValidator>
#include <QApplication>
#include <QMessageBox>


finance::finance()
{
id=0,salaire=0,telephone=0;
nom="";prenom="", adress="";
}

finance::finance(QString nom,QString prenom,int telephone,int id ,int salaire,QString adress)
{
this->nom=nom;
    this->prenom=prenom;
    this->telephone=telephone;
    this->id=id;
    this->salaire=salaire;
    this->adress=adress;
}

int finance::getid(){return  id;}
int finance::getsalaire(){return salaire;}
int finance::gettelephone(){return telephone;}
QString finance::getnom(){return nom;}
QString finance::getprenom(){return prenom;}
QString finance::getadress(){return adress;}
void finance::setid(int id){this->id=id;}
void finance::setsalaire(int salaire){this->salaire=salaire;}
void finance::settelephone(int telephone){this->telephone=telephone;}
void finance::setnom(QString nom){this->nom=nom;}
void finance::setprenom(QString prenom){this->prenom=prenom;}
void finance::setadrss(QString adress){this->adress=adress;}


bool finance::ajouter()
{
    QSqlQuery query;
    QString id_string=QString::number(id);
    QString salaire_string=QString::number(salaire);
    QString tele_string=QString::number(telephone);

          query.prepare("INSERT INTO finace (nom,prenom,telephone,id,salaire,adress) "
                        "VALUES (:nom, :prenom, :telephone, :id, :salaire, :adress)");
          query.bindValue(":nom", nom);
          query.bindValue(":prenom", prenom);
          query.bindValue(":telephone", tele_string);
          query.bindValue(":id", id_string);
          query.bindValue(":salaire", salaire_string);
          query.bindValue(":adress", adress);
          return query.exec();
}



QSqlQueryModel* finance::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
         model->setQuery("SELECT* FROM finace");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
         model->setHeaderData(1, Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("telephone"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("id"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("salaire"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("adress"));
    return  model ;
}


bool finance::supprimer(int id)
{
    QSqlQuery query;
    query.prepare("delete from finace where id=:id");
    query.bindValue(0,id);
    return query.exec();
}



bool finance::modifier(QString nom,QString prenom,int telephone,int id,int salaire,QString adress)

{

    QSqlQuery query;

    query.prepare("update finace set nom=:nom,prenom=:prenom,telephone=:telephone,id=:id,salaire=:salaire,adress=:adress where id=:id");

    query.bindValue(":nom", nom);
    query.bindValue(":prenom", prenom);
    query.bindValue(":telephone", telephone);
    query.bindValue(":id", id);
    query.bindValue(":salaire", salaire);
    query.bindValue(":adress", adress);



    return query.exec();



}
QSqlQueryModel *finance:: trier(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from finace  order by id ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("telephone"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("id"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("salaire"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("adress"));
return  model ;

}

QSqlQueryModel *finance:: trier1(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from finace  order by nom");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("telephone"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("id"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("salaire"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("adress"));
return  model ;

}

QSqlQueryModel *finance:: trier2(){
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from finace  order by salaire ASC");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("telephone"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("id"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("salaire"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("adress"));
return  model ;

}

QSqlQueryModel *finance::rechercher(QString nom)
{
    QSqlQueryModel *model=new QSqlQueryModel();
    model->setQuery("select * from finace WHERE(nom='"+nom+"')");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("NOM"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("prenom"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("telephone"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("id"));
model->setHeaderData(4, Qt::Horizontal,QObject::tr("salaire"));
model->setHeaderData(5, Qt::Horizontal,QObject::tr("adress"));
return  model ;
}

