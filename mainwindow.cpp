#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "server.h"
#include "mysignal.h"

#include <QTimer>
#include <QTime>
#include <QThread>
#include <math.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    server(new Server(this)),
    signal(new MySignal(this))
{
    ui->setupUi(this);

    signal->setFunction([](double x) -> double {
        return 3 * sin(x);
    });

    signal->setXInitial(0);

    connect(signal, &MySignal::newValue, server, &Server::sendData);

    connect(server, &Server::sendMessage, [this](const QString& message) {
        ui->notificationBox->append("[" + QTime::currentTime().toString() + "]" + "\t " + message);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_serverStartButton_clicked(bool checked)
{
    if(checked){
        server->start();
        signal->start();

        ui->serverStartButton->setText("Остановить сервер");
        ui->portNumber->setNum(server->getServerPort());
    } else {
        signal->stop();
        server->stop();

        ui->serverStartButton->setText("Запустить сервер");
        ui->portNumber->setText(" ");
    }
}
