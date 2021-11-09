#include "connexion.h"


connexion::connexion()
{}

bool connexion::createconnexion()
{
db=QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("PROJET2A19");
db.setUserName("system");
db.setPassword("didiayouta");
if(db.open()) test=true;
return test;
}
void connexion::closeconnexion(){db.close();}
