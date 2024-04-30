#include "serialinfo.h"


SerialInfo::SerialInfo(QObject *parent)
    : QObject(parent)
{
    findPortTimer = new QTimer(this);
    findPortTimer->setInterval(500);
    connect(findPortTimer, &QTimer::timeout, this, &SerialInfo::findPort);
    findPortTimer->start();
}

SerialInfo::~SerialInfo()
{

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
    if(list.length() != portlist.length()){
        portlist = list;
        emit portListChanged(portlist);
        return;
    }

    int count = 0;
    for(int i = 0;i< list.length();++i)
    {
        for(int j = 0;j< portlist.length();++j)
        {
            if(list[i].portName() == portlist[j].portName())
            {
                count ++;
                break;
            }
        }
    }

    //出现改变
    if(count != list.length())
    {
        portlist = list;
        emit portListChanged(portlist);
    }
}
