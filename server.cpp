#include "server.h"
#include <QTimer>
#include <QDataStream>
#include <QTcpServer>
#include <QTcpSocket>

Server::Server(QObject *parent) :
    QObject(parent),
    server(nullptr),
    receiver(nullptr)
{
    server = new QTcpServer(this);

    connect(server, &QTcpServer::newConnection, this, &Server::newConnection);

    QTimer* timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &Server::sendData);
    timer->start(20);

    if(!server->listen(QHostAddress::Any, 1234)){
        qDebug() << "Server couldn't start";
    } else {
        qDebug() << "Server started";
    }
}

void Server::newConnection() {
    receiver = server->nextPendingConnection();
    qDebug() << "New connection";

    connect(receiver, &QTcpSocket::disconnected, [this](){
        receiver->deleteLater();
        qDebug() << "Disconected";
    });
}

void Server::sendData(){
    if(receiver != nullptr){
        QTextStream data(receiver);
        data << "Test tcp text stream";
        receiver->flush();
    }
}


