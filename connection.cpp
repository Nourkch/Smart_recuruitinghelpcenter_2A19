#include "connection.h"

Connection::Connection()
{

}

bool Connection::createConnection(){

    db=QSqlDatabase::addDatabase("QODBC");

    db.setDatabaseName("project2A19");
    db.setUserName("system");
    db.setPassword("Maxfayer2001");

    if(db.open())
        return true;

    return false;
}

void Connection::closeConnection(){db.close();}
