#ifndef SERVER_H
#define SERVER_H

#include <QObject>

class QTcpServer;
class QTcpSocket;

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:

public slots:
    void newConnection();
    void sendData();

private:
    QTcpServer* server;
    QTcpSocket* receiver;
};

#endif // SERVER_H
