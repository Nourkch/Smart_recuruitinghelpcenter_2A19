#include "formation.h"
#include "connection.h"



#include "mainwindow.h"
#include "cours.h"
#include <QMessageBox>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QFileDialog>
#include <QTextDocument>
#include <QComboBox>

formation::formation()
{
idf=0 ; type=" "  ; periode=" " ;
}

formation::formation (int idf,QString type,QString periode)
{   this->idf=idf;
    this->type=type;
    this->periode=periode;
}
int formation::getidf(){return idf;}
QString formation::gettype(){return type;}
QString formation::getperiode(){return periode;}


void formation::setidf(int idf){this->idf=idf;}
void formation::settype(QString type){this->type=type;}
void formation::setperiode(QString periode){this->periode=periode;}


bool formation::ajouter()
{
    QString idf_string=QString::number(idf);
    QSqlQuery query;

          query.prepare("INSERT INTO FORMATION (idf, type, periode) "
                        "VALUES (:idf, :type, :periode)");
          query.bindValue(0,idf_string);
          query.bindValue(1,type);
          query.bindValue(2,periode);

          return query.exec();

}
bool formation::supprimer(int idf)
{
    QSqlQuery query;

          query.prepare("Delete from FORMATION where idf=:idf");

          query.bindValue(0,idf);

          return query.exec();



}
QSqlQueryModel* formation::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


model->setQuery("SELECT *  FROM formation");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("Idf"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("periode"));

  return model;
}

int idf();
QString gettype();
QString getperiode();


void setidf(int);
void settype(QString);
void setperiode(QString);

bool formation::modifier(int idf )
{
    QSqlQuery query;

     QString res = QString::number(idf);


        query.prepare( "UPDATE FORMATION set type=:type ,periode=:periode ;");
        query.bindValue(":idf",res );
        query.bindValue(":type", type);
        query.bindValue(":periode",periode);


     return query.exec();
}
QSqlQueryModel *formation::sort_formation()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("select * from  FORMATION ORDER BY idf");

    model->setHeaderData(0, Qt::Horizontal,QObject::tr("idf"));
    model->setHeaderData(1, Qt::Horizontal,QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("periode"));



    return model;
}
QSqlQueryModel * formation::rechercher(int iden)
{
QSqlQueryModel * model= new QSqlQueryModel();
QSqlQuery query;
QString res=QString::number(iden);  //SQLQUERY ONLY TAKES STRING ENTRIES.
query.prepare("SELECT * from FORMATION where idf= :idf");
query.bindValue(":idf",res);

    query.exec();
model->setQuery(query);
model->setHeaderData(0, Qt::Horizontal,QObject::tr("idf"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("type"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("periode"));

return model ;
}
