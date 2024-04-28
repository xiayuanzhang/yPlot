#ifndef SERIALINFO_H
#define SERIALINFO_H
#include <QObject>
#include <QtSerialPort>
#include <QSerialPortInfo>

class SerialInfo : public QObject
{
     Q_OBJECT

public:
    SerialInfo(QObject *parent = nullptr);
    ~SerialInfo();

    void stopFindPort();
    void startFindPort();

    const QList<QSerialPortInfo> &getPortList() const { return portlist; }

private slots:
    void findPort();

signals:
    void portListChanged(const QList<QSerialPortInfo> &portlist);
private:
    QList<QSerialPortInfo> portlist;

    QTimer *findPortTimer; // 定时器，用于定时搜索串口
};

#endif // SERIALINFO_H
