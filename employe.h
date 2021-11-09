#ifndef EMPLOYE_H
#define EMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>
class employe
{
private:
    QString lastname,firstname,sexe,department;
    QDate BDate;
    int ID,CIN,TEL;
public:
 //contructor
    employe();
    employe(int id ,QString lname,QString fname);
    employe (int id ,int Cin,QString lname,QString fname,int tel,QDate birthdate,QString Sexe,QString departement);
 //method
    int getId() const{return ID;}
      void setId(int value) {ID=value;}
      QString getFirstname() const {return firstname;  }
      void setFirstname(const QString &value) { firstname = value; }
      QString getLastname() const {return lastname;}
      void setLastname(const QString &value){ lastname = value;}
      int getCIN() const {return CIN;};
      void setCIN(int value) {CIN=value;}
      int getTEL() const {return TEL;};
      void setTEL(int value) {TEL=value;}
     // QString getBdate() const{return BDate ;};
    //  void setBdate(const QString &value){BDate=value;};
      QString getsexe() const {return sexe;};
      void setsexe(const QString &value) {sexe=value;}
      QString getDepartment() const {return department;};
      void setDepartment(const QString &value){department=value;};
//functions
bool ajouter();
QSqlQueryModel * afficher();
bool supprimer(int);
bool modifier(int);
};

#endif // EMPLOYE_H
