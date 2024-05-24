#ifndef MYTIMER_H
#define MYTIMER_H

#include <QObject>
#include <QTimer>
#include <QThread>
#include <QDebug>

class TimerThread : public QThread {
    Q_OBJECT

public:
    TimerThread() {
        moveToThread(this);
        start();
    }

    static TimerThread& instance() {
        static TimerThread instance;
        return instance;
    }

protected:
    void run() override {
        exec();
    }
};


class MyTimer : public QObject
{
    Q_OBJECT
public:
    explicit MyTimer(QObject *parent = nullptr)
        : QObject(parent),
    isStart(false){
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MyTimer::update);
        timer->moveToThread(&TimerThread::instance());
    }

    ~MyTimer(){
        timer->deleteLater();
    }

    void start(int interval){
        QMetaObject::invokeMethod(timer, "start", Qt::QueuedConnection, Q_ARG(int, interval));
        isStart = true;
    }

    void stop(){
        QMetaObject::invokeMethod(timer, "stop", Qt::QueuedConnection);
        isStart = false;
    }

    bool isActive(){
        return isStart;
    }




private slots:
    //定时器在子线程中触发timeout之后, 会在主线程调用update,然后再发出mytimer的timeout信号, 所以没有意义
    void update(){
        qDebug() << "QTimer::update()" << QThread::currentThread();
        emit timeout();
    }

signals:
    void timeout();



private:
    QTimer *timer;
    bool isStart;
};

#endif // MYTIMER_H
