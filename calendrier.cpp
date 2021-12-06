#include "calendrier.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlQueryModel>

calendrier::calendrier()
{
    ide=0;
    date_exam=date_exam.currentDate();
    temps="";
}
calendrier::calendrier(int ide,QDate date_exam, QString temps)
{
    this->ide=ide; this->date_exam=date_exam; this->temps=temps;
}
int calendrier::getide() {return ide;}
QDate calendrier::getdate_exam(){return date_exam;}
QString calendrier::gettemps(){return temps;}


void calendrier::setide(int ide){this->ide=ide;}
void calendrier::setdate_exam(QDate date_exam){this->date_exam=date_exam;}
void calendrier::settemps(QString temps){this->temps=temps;}

bool calendrier::ajouter()
{ bool test=false;
    QSqlQuery query;
    QString ide_string= QString::number(ide);
          query.prepare("INSERT INTO calendrier (ide, date_exam, temps) "
                        "VALUES (:ide, :date_exam, :temps)");

          query.bindValue(0, ide_string);
          query.bindValue(1, date_exam);
          query.bindValue(2, temps);
        return query.exec();



    return test;

}
bool  calendrier::supprimer(int ide)
{  QSqlQuery query;
    query.prepare("delete from calendrier where ide=:ide");
  query.bindValue(0, ide);
return query.exec();
}


QSqlQueryModel* calendrier::afficher()
{
   QSqlQueryModel* model=new QSqlQueryModel();

         model->setQuery("SELECT* FROM calendrier");
         model->setHeaderData(0, Qt::Horizontal, QObject::tr("ide"));
         model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date_exam"));
         model->setHeaderData(2, Qt::Horizontal, QObject::tr("temps"));


  return model;
}


bool calendrier::update(int ide, QDate date_exam,QString temps)
{
    QSqlQuery query;
    query.prepare("UPDATE calendrier SET ide= :ide,date_exam= :date_exam,temps=:temps WHERE ide = :ide");
    query.bindValue(":ide", ide);
    query.bindValue(":date_exam",date_exam );
    query.bindValue(":temps", temps);



    return    query.exec();
}
