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

signals:
    void sendMessage(QString);
    void started(qint16);
    void stopped();

public slots:
    void newConnection();
    void sendData(qreal);

private:
    QTcpServer *server;
    QList<QTcpSocket *> clients;
};

#endif // SERVER_H
