#include "mysignal.h"

#include <QTimer>
#include <QThread>
#include <QDebug>

MySignal::MySignal(QObject *parent)
    : QObject(parent), timer(new QTimer(this)), function(nullptr), currentX(0), xStep(0.01)
{
    timer->setInterval(20);
    // Генерируем сигнал каждые 20 миллисекунд
    connect(timer, &QTimer::timeout, this, [this]() { calculateNewValue(); });
    
    connect(this, &MySignal::started, this, [this]() {timer->start(); });
}

MySignal::~MySignal() { }

void MySignal::setFunction(std::function<double(double)> _function)
{
    function = _function;
}

void MySignal::setXInitial(double xInitial)
{
    currentX = xInitial;
}

bool MySignal::start()
{
    if (function == nullptr) {
        return false;
    }
    emit started();
    return true;
}

void MySignal::stop()
{
    timer->stop();
}

void MySignal::calculateNewValue()
{
    emit newValue(function.operator()(currentX));
    currentX += xStep;
}
