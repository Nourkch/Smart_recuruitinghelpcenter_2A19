#include "crudconge.h"
#include "employe.h"

CRUDconge::CRUDconge()
{
    typeConge="";
   loginEmploye="";
    commentaireResponsable="";
    commentaireEmploye="";
    dateDebutConge="";
    dateFinConge="";

}
CRUDconge::CRUDconge(QString loginemploye,QString typeConge,QString commentaireResponsable, QString CommentaireEmploye, QString DateDebutConge,QString DateFinConge)
{
this->typeConge=typeConge;
this->loginEmploye=loginemploye;
this->commentaireResponsable=commentaireResponsable;
this->commentaireEmploye=CommentaireEmploye;
this->dateDebutConge=DateDebutConge;
this->dateFinConge=DateFinConge;
}

bool CRUDconge::AjoutConge(){
QSqlQuery query;
query.prepare("INSERT INTO Conge VALUES (NULL,:loginEmploye,:typeConge,:commentaireResponsable,:commentaireEmploye,:dateDebutConge,:dateFinConge)");
query.bindValue(":loginEmploye",loginEmploye);
query.bindValue(":typeConge",typeConge);
query.bindValue(":commentaireResponsable",commentaireResponsable);
query.bindValue(":commentaireEmploye",commentaireEmploye);
query.bindValue(":dateDebutConge",dateDebutConge);
query.bindValue(":dateFinConge",dateFinConge);
return ((query.exec()));
}

bool CRUDconge::ModifierConge(){
QSqlQuery query;
query.prepare("Update Conge set IdEmploye=:loginEmploye,TypeConge=:typeConge,CommentaireResponsable=:commentaireResponsable,CommentaireEmploye=:commentaireEmploye,DateDebutConge=:dateDebutConge,DateFinConge=:dateFinConge where IdConge=:IdConge");
query.bindValue(":IdConge",idConge);
query.bindValue(":loginEmploye",loginEmploye);
query.bindValue(":typeConge",typeConge);
query.bindValue(":commentaireResponsable",commentaireResponsable);
query.bindValue(":commentaireEmploye",commentaireEmploye);
query.bindValue(":dateDebutConge",dateDebutConge);
query.bindValue(":dateFinConge",dateFinConge);
return ((query.exec()));
}

bool CRUDconge::SupprimerConge(){
QSqlQuery query;
query.prepare("Delete from Conge where IdConge=:IdConge");
query.bindValue(":IdConge",idConge);
return ((query.exec()));
}

bool CRUDconge::RechercherConge(QString IdCongeUtilisateur){
QSqlQuery query;
unsigned long long IdCongeUtilisateur2=IdCongeUtilisateur.toLongLong();

query.prepare("Select * from Conge where IdConge=:IdConge");
query.bindValue(":loginEmploye",IdCongeUtilisateur2);
if (query.exec())
{
    while (query.next()){

        qDebug()<<"find";
        idConge=(query.value(0).toLongLong());
        loginEmploye=(query.value(1).toString());
        typeConge=(query.value(2).toString());
        commentaireResponsable=(query.value(3).toString());
        commentaireEmploye=(query.value(4).toString());
        dateDebutConge=(query.value(5).toString());
        dateFinConge=(query.value(6).toString());

    }
}
return query.exec();
}

QSqlQueryModel *CRUDconge::AfficherConge(){
    QSqlQueryModel * model= new QSqlQueryModel ();
    model->setQuery("select * from Conge");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("IdConge"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("loginEmploye"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("typeConge"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Commentaire Responsable"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Commentaire Employe"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date debut conge"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Fin conge"));
    return model;




}
