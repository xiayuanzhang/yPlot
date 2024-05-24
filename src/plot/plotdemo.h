#ifndef PLOTDEMO_H
#define PLOTDEMO_H
#include <QObject>
#include <QTimer>
class PlotDemo: public QObject
{
    Q_OBJECT
public:
    PlotDemo(QObject *parent = nullptr);
    void start(int interval_ms = 3);
    void stop();
    bool isStart() { return timer->isActive(); }

private slots:
    void update();
signals:
    void readyRead(QByteArray data);
private:
    QTimer *timer;

    float m_ch[6];
    double m_count = 0;
};

#endif // PLOTDEMO_H

