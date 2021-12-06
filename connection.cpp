#include "connection.h"
//test tutoriel
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet2A19");//inserer le nom de la source de données ODBC
db.setUserName("dhia");//inserer nom de l'utilisateur
db.setPassword("dhia");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
