#include "connection.h"

Connection::Connection(){}

 bool Connection::createconnection()
 {  bool test=false;
  db = QSqlDatabase::addDatabase("QODBC");
  db.setDatabaseName("GESTION_PARTENARIAT");
  db.setUserName("youssef");
  db.setPassword("esprit18");

  if(db.open()) test=true;

  return test;

 }
