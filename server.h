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
    ~Server();

    void start();
    void stop();

    quint16 getServerPort();

signals:
    void sendMessage(QString);

public slots:
    void newConnection();
    void sendData(qreal);

private:
    QTcpServer* server;
    QList<QTcpSocket*> clients;

};

#endif // SERVER_H
