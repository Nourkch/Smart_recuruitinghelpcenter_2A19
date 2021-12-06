#include "cours.h"
#include "connection.h"

cours::cours()
{
    idc=0;
    matiere="";
    temps="";
    duree="";

    }



cours::cours (int idc,QString matiere,QString temps,QString duree)
{   this->idc=idc;
    this->matiere=matiere;
    this->temps=temps;
    this->duree=duree;
}
int cours::getidc(){return idc;}
QString cours::getmatiere(){return matiere;}
QString cours::gettemps(){return temps;}
QString cours::getduree(){return duree;}


void cours::setidc(int idc){this->idc=idc;}
void cours::setmatiere(QString matiere){this->matiere=matiere;}
void cours::settemps(QString temps){this->temps=temps;}
void cours::setduree(QString duree){this->duree=duree;}


bool cours::ajouter()
{
    QString idc_string=QString::number(idc);
    QSqlQuery query;

          query.prepare("INSERT INTO cours (idc, matiere, temps,duree) "
                        "VALUES (:idc, :matiere, :temps, :duree)");
          query.bindValue(0,idc_string);
          query.bindValue(1,matiere);
          query.bindValue(2,temps);
          query.bindValue(2,duree);

          return query.exec();

}
bool cours::supprimer(int idc)
{
    QSqlQuery query;

          query.prepare("Delete from cours where idc=:idc");

          query.bindValue(0,idc);

          return query.exec();



}
QSqlQueryModel* cours::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


model->setQuery("SELECT *  FROM cours");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("idc"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("matiere"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("temps"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("duree"));

  return model;
}

int idc();
QString getmatiere();
QString gettemps();
QString getduree();


void setidc(int);
void setmatiere(QString);
void settemps(QString);
void setduree(QString);

bool cours::modifier(int idc )
{
    QSqlQuery query;

     QString res = QString::number(idc);


        query.prepare( "UPDATE cours set matiere=:matiere ,temps=:temps,duree=:duree ;");
        query.bindValue(":idc",res );
        query.bindValue(":matiere", matiere);
        query.bindValue(":temps",temps);
        query.bindValue(":duree",duree);


     return query.exec();
}
