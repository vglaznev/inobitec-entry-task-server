#include "server.h"

#include <QTimer>
#include <QDataStream>
#include <QTcpServer>
#include <QTcpSocket>

Server::Server(QObject *parent) :
    QObject(parent),
    server(new QTcpServer(this)),
    receiver(nullptr)
{
    connect(server, &QTcpServer::newConnection, this, &Server::newConnection);
}

Server::~Server(){
}

void Server::start(){
    if(!server->listen(QHostAddress::Any, 1043)){
        server->listen();
    }
    emit sendMessage("Сервер запущен");
}

void Server::stop(){
    server->close();
    emit sendMessage("Cервер остановлен");
}

quint16 Server::getServerPort(){
    return server->serverPort();
}

void Server::newConnection() {
    receiver = server->nextPendingConnection();
    emit sendMessage("Клиент присоединен");

    connect(receiver, &QTcpSocket::disconnected, [this](){
        emit sendMessage("Клиент отсоединен");
        //receiver->deleteLater();
    });
}

void Server::sendData(double value){
    if(receiver != nullptr){
        QDataStream data(receiver);
        data << value;
        receiver->flush();
    }
}


