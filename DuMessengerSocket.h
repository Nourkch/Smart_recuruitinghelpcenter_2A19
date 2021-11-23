#ifndef DUMESSENGERSOCKET_H
#define DUMESSENGERSOCKET_H

#include <QTcpSocket>
namespace  DuarteCorporation
{
class DuMessengerSocket : public QTcpSocket
{
    Q_OBJECT
public:
    DuMessengerSocket(qintptr handle, QObject *parent = nullptr);
signals :
    void DuReadyRead(DuMessengerSocket*);
    void DuStateChanged(DuMessengerSocket * , int);
};
}//endnamespace  DuarteCorporation
#endif // DUMESSENGERSOCKET_H
