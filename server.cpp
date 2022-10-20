#include "server.h"

#include <QTimer>
#include <QDataStream>
#include <QTcpServer>
#include <QTcpSocket>

Server::Server(QObject *parent) :
    QObject(parent),
    server(new QTcpServer(this)),
    clients()
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
    for (const auto socket : clients) {
        socket->disconnectFromHost();
    }

    server->close();
    emit sendMessage("Cервер остановлен");
}

quint16 Server::getServerPort(){
    return server->serverPort();
}

void Server::newConnection() {
    while(server->hasPendingConnections()){
        QTcpSocket* socket = server->nextPendingConnection();
        emit sendMessage("Клиент присоединен");

        clients << socket;

        connect(socket, &QTcpSocket::disconnected, [this, socket](){
            emit sendMessage("Клиент отсоединен");
            clients.removeAll(socket);
            socket->deleteLater();
        });
    }
}

void Server::sendData(qreal value){
    for (const auto socket : clients) {
        QDataStream data(socket);
        data << value;
        socket->flush();
    }
}


