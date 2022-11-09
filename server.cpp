#include "server.h"

#include <QTimer>
#include <QDataStream>
#include <QTcpServer>
#include <QTcpSocket>

Server::Server(QObject *parent) : QObject(parent), server(new QTcpServer(this))
{
    connect(server, &QTcpServer::newConnection, this, &Server::newConnection, Qt::QueuedConnection);
}

Server::~Server()
{
    stop();
}

void Server::start()
{
    if (!server->listen(QHostAddress::Any, 1043)) {
        server->listen();
    }
    emit started(server->serverPort());
    emit sendMessage("Сервер запущен");
}

void Server::stop()
{
    for (const auto socket : clients) {
        socket->disconnectFromHost();
    }

    server->close();

    emit stopped();
    emit sendMessage("Cервер остановлен");
}

void Server::newConnection()
{
    while (server->hasPendingConnections()) {
        QTcpSocket *socket = server->nextPendingConnection();
        QString socketDescriptor = QString::number(socket->socketDescriptor());
        emit sendMessage("Клиент [" + socketDescriptor + "] присоединен");

        clients << socket;

        connect(
                socket, &QTcpSocket::disconnected, this,
                [this, socket, socketDescriptor]() {
                    emit sendMessage("Клиент [" + socketDescriptor + "] отсоединен");
                    clients.removeAll(socket);
                    socket->deleteLater();
                },
                Qt::QueuedConnection);
    }
}

void Server::sendData(qreal value)
{
    for (const auto socket : clients) {
        QDataStream data(socket);
        data << value;
        socket->flush();
    }
}
