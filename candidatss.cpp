#include "candidatss.h"
#include <QTableView>
#include <QObject>

Candidatss::Candidatss()
{
    cin = 0;
    nom ="";
    prenom="";

   email="";
    rue = "";
    codepostal=0;

     sexe="" ;
     ville ="";

   // date_naissance=;
}

Candidatss :: Candidatss (int cin,QString nom,QString prenom ,QString email,QString sexe,QString rue,int codepostal,QDate date_naissance,QString ville)
{

    this->cin= cin ;
    this->nom = nom;
    this->prenom= prenom;
    this->email= email;
    this->sexe=sexe;
    this->rue= rue;
    this->codepostal= codepostal;
    this->date_naissance=date_naissance;
    this->ville=ville;

}

Candidatss :: Candidatss (int id_candidat, int cin,QString nom,QString prenom ,QString email,QString sexe,QString rue,int codepostal,QDate date_naissance,QString ville)
{

    this->id_candidat=id_candidat;

    this->cin= cin ;
    this->nom = nom;
    this->prenom= prenom;
    this->email= email;
    this->sexe=sexe;
    this->rue= rue;
    this->codepostal= codepostal;
    this->date_naissance=date_naissance;
    this->ville=ville;

}
int Candidatss:: getCIN(){return cin;}
QString Candidatss:: getnom() {return nom;}
    QString Candidatss:: getprenom(){return prenom;}
    QString Candidatss::getadressemail(){return email;}
    QString Candidatss::getrue(){return rue;}
    int Candidatss::getcodepostal(){return codepostal;}
    QString Candidatss::getsexe(){ return sexe;}
    QString Candidatss:: getville(){return ville;}
int Candidatss:: getID_candidat(){return id_candidat;}
    QDate Candidatss :: getDatenaissance(){return date_naissance;}


bool Candidatss::ajouter_candidat()
{
    QSqlQuery query;
    QString i;

     query.exec("select id_candidat from CANDIDAT where id_candidat = ( select max(id_candidat) from CANDIDAT);");

      if (query.next()) {
            i = query.value(0).toString();

            qDebug() << i <<endl; // yaffichi les id fel consol (test)
        }


QString CIN_string= QString::number(cin);
QString codepostal_string= QString::number(codepostal);

query.prepare("INSERT INTO CANDIDAT(ID_CANDIDAT,CIN,NOM,PRENOM,email,SEXE,RUE,CODE_POSTAL,DATE_NAISSANCE,VILLE)"  // selon base
              "VALUES(:id_candidat,:cin,:nom,:prenom,:email,:sexe,:rue,:codepostal,:date_naissance,:ville)");

 query.bindValue(":id_candidat",(i.toInt()+1)); // inc + conv to int

query.bindValue(":nom",nom);
query.bindValue(":prenom",prenom);
query.bindValue(":email",email);
query.bindValue(":sexe",sexe);
query.bindValue(":rue",rue);

query.bindValue(":ville",ville);

//

query.bindValue(":cin",CIN_string);
query.bindValue(":codepostal",codepostal_string);
query.bindValue(":date_naissance",date_naissance);

    return query.exec();

}

QSqlQueryModel *Candidatss:: afficher()
{
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from CANDIDAT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODE_POSTAL"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("DATE_NAISSANCE"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("SEXE"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("VILLE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("RUE"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("CIN"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("PRENOM"));

    return model;
}

bool Candidatss:: supprimer_candidat(int id)
{
    QSqlQuery query;
    query.prepare("Delete from CANDIDAT where id_candidat=:id_candidat");
    query.bindValue(":id_candidat",id);
    return query.exec();
}

bool Candidatss::modifier_candidat()
{
    QSqlQuery query;
    QString res0 =QString::number(id_candidat);
    QString res1 =QString::number(codepostal);
    QString res2 = QString::number(cin);


    query.prepare(" UPDATE CANDIDAT SET CIN=:cin, NOM=:nom, PRENOM=:prenom, email=:email, SEXE=:sexe, RUE=:rue ,CODE_POSTAL=:code_postal ,DATE_NAISSANCE=:date_naissance, VILLE=:ville WHERE id_candidat=:id_candidat ");

    query.bindValue(":id_candidat",res0);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":email",email);
    query.bindValue(":sexe",sexe);
    query.bindValue(":cin",res2);
    query.bindValue(":date_naissance",date_naissance);
    query.bindValue(":rue",rue);
    query.bindValue(":code_postal",res1);
    query.bindValue(":ville",ville);


    return query.exec();
}
