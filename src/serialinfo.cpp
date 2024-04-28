#include "serialinfo.h"


SerialInfo::SerialInfo(QObject *parent)
    : QObject(parent)
{
    findPortTimer = new QTimer(this);
    findPortTimer->setInterval(1000);
    connect(findPortTimer, &QTimer::timeout, this, &SerialInfo::findPort);
    findPortTimer->start();
}

void SerialInfo::stopFindPort()
{
    findPortTimer->stop();
}

void SerialInfo::startFindPort()
{
    findPortTimer->start();
}

void SerialInfo::findPort()
{
    QList<QSerialPortInfo> list = QSerialPortInfo::availablePorts();
    if(list != portlist)
    {
        portlist = list;
        emit portListChanged(portlist);
    }
}
