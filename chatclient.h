#ifndef CHATCLIENT_H
#define CHATCLIENT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QtNetwork/QAbstractSocket>
#include <QtNetwork/QSslSocket>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <QByteArray>
#include <QtNetwork>
#include <QSslSocket>

class chatclient : public QObject
{
    Q_OBJECT
public:
   chatclient(const QString &user, const QString &pass,
              const QString &host, quint16 port = 587
                , int timeout = 30000  ) ;
    virtual ~chatclient() ;

void sendMail( const QString &from, const QString &to,
               const QString &subject, const QString &body );

signals:
void status( const QString &);

private slots:
void stateChanged(QAbstractSocket::SocketState socketState);
void errorReceived(QAbstractSocket::SocketError socketError);
void disconnected();
void connected();
void readyRead();

private:
int timeout;
QString message;
QTextStream *t;
QSslSocket *socket;
QString from;
QString rcpt;
QString response;
QString user;
QString pass;
QString host;
quint16 port;
enum states{Tls, HandShake ,Auth,User,Pass,Rcpt,Mail,Data,Init,Body,Quit,Close};
int state;

};
//pour lespace chat
class ChatClient : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ChatClient)
public:
    explicit ChatClient(QObject *parent = nullptr);
public slots:
    void connectToServer(const QHostAddress &address, quint16 port);
    void login(const QString &userName);
    void sendMessage(const QString &text);
    void disconnectFromHost();
private slots:
    void onReadyRead();
signals:
    void connected();
    void readyread();//bech nfasakhha khater cpas sur
    void loggedIn();
    void loginError(const QString &reason);
    void disconnected();
    void messageReceived(const QString &sender, const QString &text);
    void error(QAbstractSocket::SocketError socketError);
    void userJoined(const QString &username);
    void userLeft(const QString &username);
private:
    QTcpSocket *m_clientSocket;
    bool m_loggedIn;
    void jsonReceived(const QJsonObject &doc);
};

#endif // CHATCLIENT_H
