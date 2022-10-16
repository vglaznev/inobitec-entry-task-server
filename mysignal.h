#ifndef MYSIGNAL_H
#define MYSIGNAL_H

#include <QObject>
#include <functional>

class QTimer;

class MySignal : public QObject
{
    Q_OBJECT
public:
    explicit MySignal(QObject *parent = nullptr);
    virtual ~MySignal();

    void setTimeInterval(int);
    void setFunction(std::function<double(double)>);
    void setXInitial(double);
    void setXStep(double);

    bool start();
    void stop();

signals:
    void newValue(double);

private:
    QTimer* timer;
    std::function<double(double)> function;
    double currentX;
    double xStep;

    void calculateNewValue();
};

#endif // MYSIGNAL_H
