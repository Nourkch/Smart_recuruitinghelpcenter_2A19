#include "employe.h"

Employe::Employe()
{
    nom="";
    prenom="";
    login="";
    motDePasse="";
    adresseMail="";
    adresse="";
    dateNaissance="";
    service="";
    sexe="";
    nss=0;
    cin=0;


}
Employe::Employe(QString nom, QString prenom, QString login, QString motDePasse ,QString adresseMail, QString adresse, QString dateNaissance, QString service, QString sexe, int nss,  int cin)
{
    this->nom=nom;
    this->prenom=prenom;
    this->login=login;
    this->motDePasse=motDePasse;
    this->adresseMail=adresseMail;
    this->adresse=adresse;
    this->dateNaissance=dateNaissance;
    this->service=service;
    this->sexe=sexe;
    this->nss=nss;
    this->cin=cin;
}

Employe::~Employe()
{

}

bool Employe::AjoutEmploye()
{
    QSqlQuery query;
    QString nss1=QString::number(nss);
    QString cin1=QString::number(cin);


    query.prepare("INSERT INTO Employe VALUES (:nom,:prenom,:login,:motDepasse,:adresseMail,:adresse,:tel,:dateNaissance,:profession,:typeContrat,:dateEmbouche,:service,:nss1,:numpas,:cin1,:sexe,:nationnalite,:adresseTravail,:etatCivil,:image)");


    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":login",login);
    query.bindValue(":motDePasse",motDePasse);

    query.bindValue(":adresseMail",adresseMail);
    query.bindValue(":adresse",adresse);
    query.bindValue(":dateNaissance",dateNaissance);

    query.bindValue(":service",service);

    query.bindValue(":nss1",nss1);
    query.bindValue(":cin1",cin1);
    query.bindValue(":sexe",sexe);



return (query.exec());

}

void Employe::ModifierEmploye(){

        QSqlQuery query;
        query.prepare("Update Employe set nom=:nom,prenom=:prenom,motdepasse=:motdepasse,adressemail=:adressemail,adresse=:adresse,telephonetravail=:telephonetravail,datenaissance=:datenaissance,profession=:profession,typecontrat=:typecontrat,dateembouche=:dateembouche,service=:service,nss=:nss,numpassport=:numpassport,cin=:cin,sexe=:sexe,nationnalite=:nationnalite,adressetravail=:adressetravail,etatcivil=:etatcivil,image=:image  where login=:login");

        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":login",login);
        query.bindValue(":motdepasse",motDePasse);
        query.bindValue(":adressemail",adresseMail);
        query.bindValue(":adresse",adresse);
        query.bindValue(":datenaissance",dateNaissance);

        query.bindValue(":service",service);

        query.bindValue(":nss",nss);
        query.bindValue(":cin",cin);
        query.bindValue(":sexe",sexe);



        query.exec();
        qDebug()<<"L'employe a etait modifie avec succees !";
      }

bool Employe::RechercherInstEmploye(unsigned long long LoginUtilisateur)
{


    QSqlQuery query;
    if (LoginUtilisateur!=0)
    {
    query.prepare("Select * from Employe where login=:login");
    query.bindValue(":login", LoginUtilisateur);
    if (query.exec())
    {
    while(query.next())
    {

        nom=(query.value(0).toString());
        prenom=(query.value(1).toString());
        login=(query.value(2).toString());
        qDebug()<<"dsqd" <<login;
        motDePasse=(query.value(3).toString());
        adresseMail=(query.value(4).toString());
        adresse=(query.value(5).toString());
        dateNaissance=(query.value(7).toString());

        service=(query.value(11).toString());
        nss=(query.value(12).toInt());
        cin=(query.value(14).toInt());
        sexe=(query.value(15).toString());



    }
    }
    return true;
    }

    else
        return false;
}

bool Employe::SupprimerEmploye()
{
    QSqlQuery query;

        qDebug()<<"L'employe a ete supprimer avec succes !";
        query.prepare("Delete from  Employe where (nom=:nom and prenom=:prenom) and login=:login");
        query.bindValue(":nom",nom);
        query.bindValue(":prenom",prenom);
        query.bindValue(":login",login);
return   query.exec();

}

bool Employe::RechercherEmployeParNomPrenom(QString nomUtilisateur,QString prenomUtilisateur)
{

    QSqlQuery query;
  //  QByteArray array;
    if (nomUtilisateur!="")
    {
    query.prepare("Select * from Employe where  nom=:nom and prenom=:prenom");
    query.bindValue(":nom", nomUtilisateur);
    query.bindValue(":prenom", prenomUtilisateur);
    query.exec();
    while(query.next())
    {

        nom=(query.value(0).toString());
        prenom=(query.value(1).toString());
        login=(query.value(2).toString());
       motDePasse=(query.value(3).toString());
        adresseMail=(query.value(4).toString());
        adresse=(query.value(5).toString());
        dateNaissance=(query.value(7).toString());

        service=(query.value(11).toString());
        nss=(query.value(12).toInt());
        cin=(query.value(14).toInt());
        sexe=(query.value(15).toString());




}
    }
    return true;
}

bool Employe::RechercherEmployeParNom(QString nomUtilisateur)
{

    QSqlQuery query;
    if (nomUtilisateur!="")
    {
    query.prepare("Select * from Employe where nom=:nom");
    query.bindValue(":nom", nomUtilisateur);
    query.exec();
    while(query.next())
    {
        qDebug()<<"ENTER ENTER";
        nom=(query.value(0).toString());
        prenom=(query.value(1).toString());
        login=(query.value(2).toString());
        motDePasse=(query.value(3).toString());
        adresseMail=(query.value(4).toString());
        adresse=(query.value(5).toString());
        dateNaissance=(query.value(7).toString());

        service=(query.value(11).toString());
        nss=(query.value(12).toInt());
        cin=(query.value(14).toInt());
        sexe=(query.value(15).toString());



    }
        return true;
    }

    else
        return false;

}

QSqlQueryModel *Employe::AfficherEmploye()
{
    QSqlQueryModel * model= new QSqlQueryModel ();
    model->setQuery("select * from Employe");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Prenom"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Login"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Mot de passe"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Adresse Mail"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Adresse d'habitation"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Telephone"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Date de Naissance"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Service"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Numero de securite social"));
    model->setHeaderData(14, Qt::Horizontal, QObject::tr("Carte d'identite nationnale"));
    model->setHeaderData(15, Qt::Horizontal, QObject::tr("Sexe"));
    model->setHeaderData(17, Qt::Horizontal, QObject::tr("Adresse de travail"));


    return model;




}

QVector<QString> Employe::AfficheEmployeParNom(QString nomUtilisateur)
{


    QVector <QString>vectEmploye;
    QSqlQuery query;
    query.prepare("Select * from Employe where nom=:nom");
    query.bindValue(":nom",nomUtilisateur);
    if (query.exec())
    {
        while (query.next())
        {
            vectEmploye.push_back(query.value(0).toString()+" "+query.value(1).toString());
        }
    }



return vectEmploye;
}























