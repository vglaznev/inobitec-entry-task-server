#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include "mysignal.h"

#include <QTimer>
#include <QTime>
#include <QThread>
#include <math.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      server(new Server()),
      signal(new MySignal()),
      signalThread(new QThread(this)),
      serverThread(new QThread(this))
{
    ui->setupUi(this);

    signal->setFunction([](double x) -> double { return 3 * sin(x); });

    signal->setXInitial(0);

    // При появлении нового значения сигнала отправляем его на сервер
    connect(signal, &MySignal::newValue, server, &Server::sendData);

    connect(ui->serverStartButton, &QPushButton::clicked, signal, [this](bool checked) { checked ? signal->start() : signal->stop(); });
    connect(ui->serverStartButton, &QPushButton::clicked, server, [this](bool checked) {checked ? server->start() : server->stop(); });
    connect(ui->serverStartButton, &QPushButton::clicked, this, [this](bool checked) { ui->serverStartButton->setText(checked ? "Остановить сервер" : "Запустить сервер"); });
    connect(server, &Server::started, this, [this](qint16 portNumber) {ui->portNumber->setNum(portNumber); });
    connect(server, &Server::stopped, this, [this]() {ui->portNumber->setText(""); });

    // Отображение информации о старте/остановки сервера, подключениях и отключениях
    connect(server, &Server::sendMessage, this, [this](const QString &message) {
        ui->notificationBox->append("[" + QTime::currentTime().toString() + "]" + "\t" + message);
    });

    signal->moveToThread(signalThread);
    signalThread->start();

    server->moveToThread(serverThread);
    serverThread->start();
}

MainWindow::~MainWindow()
{
    serverThread->quit();
    signalThread->quit();
    delete ui;
}
