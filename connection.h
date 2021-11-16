#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>

class Connection
{
private:
    QSqlDatabase db;

public:
    Connection();
    bool createConnection();
    void closeConnection();
};

#endif // CONNECTION_H
