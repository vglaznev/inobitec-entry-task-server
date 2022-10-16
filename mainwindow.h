#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Server;
class MySignal;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_serverStartButton_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    Server* server;
    MySignal* signal;
};

#endif // MAINWINDOW_H
