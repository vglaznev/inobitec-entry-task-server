#include "mysignal.h"

#include<QTimer>

MySignal::MySignal(QObject *parent) :
    QObject(parent),
    timer(new QTimer),
    function(nullptr),
    currentX(0),
    xStep(0.01)
{
    timer->setInterval(20);
    //Генерируем сигнал каждые 20 миллисекунд
    connect(timer, &QTimer::timeout, [this](){calculateNewValue();});
}

MySignal::~MySignal(){

}

void MySignal::setFunction(std::function<double (double)> _function){
    function = _function;
}

void MySignal::setTimeInterval(int _interval){
    timer->setInterval(_interval);
}

void MySignal::setXInitial(double xInitial){
    currentX = xInitial;
}

void MySignal::setXStep(double _xStep){
    xStep = _xStep;
}

bool MySignal::start(){
    if(function == nullptr){
        return false;
    }
    timer->start();
    return true;
}

void MySignal::stop(){
    timer->stop();
}

void MySignal::calculateNewValue(){
    emit newValue(function.operator()(currentX));
    currentX += xStep;
}
