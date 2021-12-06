#include "examen.h"
#include "connection.h"

examen::examen()
{
    ide=0;
    matiere="";
    duree="";
    note="";

    }



examen::examen (int ide,QString matiere,QString duree,QString note)
{   this->ide=ide;
    this->matiere=matiere;
    this->duree=duree;
    this->note=note;
}
int examen::getide(){return ide;}
QString examen::getmatiere(){return matiere;}
QString examen::getduree(){return duree;}
QString examen::getnote(){return note;}


void examen::setide(int ide){this->ide=ide;}
void examen::setmatiere(QString matiere){this->matiere=matiere;}
void examen::setduree(QString duree){this->duree=duree;}
void examen::setnote(QString note){this->note=note;}


bool examen::ajouter()
{
    QString ide_string=QString::number(ide);
    QSqlQuery query;

          query.prepare("INSERT INTO examen (ide, matiere, duree,note) "
                        "VALUES (:ide, :matiere, :duree, :note)");
          query.bindValue(0,ide_string);
          query.bindValue(1,matiere);
          query.bindValue(2,duree);
          query.bindValue(2,note);

          return query.exec();

}
bool examen::supprimer(int ide)
{
    QSqlQuery query;

          query.prepare("Delete from examen where ide=:ide");

          query.bindValue(0,ide);

          return query.exec();



}
QSqlQueryModel* examen::afficher()
{
  QSqlQueryModel* model=new QSqlQueryModel();


model->setQuery("SELECT *  FROM examen");
model->setHeaderData(0, Qt::Horizontal,QObject::tr("ide"));
model->setHeaderData(1, Qt::Horizontal,QObject::tr("matiere"));
model->setHeaderData(2, Qt::Horizontal,QObject::tr("duree"));
model->setHeaderData(3, Qt::Horizontal,QObject::tr("note"));

  return model;
}

int ide();
QString getmatiere();
QString getduree();
QString getduree();


void setide(int);
void setmatiere(QString);
void setduree(QString);
void setnote(QString);

bool examen::modifier(int ide )
{
    QSqlQuery query;

     QString res = QString::number(ide);


        query.prepare( "UPDATE examen set matiere=:matiere ,duree=:duree,note=:note ;");
        query.bindValue(":idc",res );
        query.bindValue(":matiere", matiere);
        query.bindValue(":duree",duree);
        query.bindValue(":note",note);


     return query.exec();
}
