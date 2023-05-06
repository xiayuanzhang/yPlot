#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include "mavlink_cpp/yplot/mavlink.h"


//数据名帧头：AABBCC
//数据名：数据名1,数据名2,数据名3,  （根据通道数量检查逗号，8通道应该右7个逗号）
//数据名帧尾 CCBBAA

//数据帧头：DDEEFF
//数据：类型*通道
//数据帧尾 FFEEDD

#define PLOT_NUM_MAX 12
#define PLOT_NAME_MAXLEN 15

class dataAnalysis : public QObject
{
    Q_OBJECT
public:
    dataAnalysis();
    ~dataAnalysis();

    //获取数据通道数量
    int getChannelNum();
    //输入数据流
    void inputDataStream(QByteArray stream);
    void clearAnalysisBuff();
private:

signals:
    void haveNewData(QVector<double> newdata);
    void haveNewName(QVector<QString> name);

private:
    int channels;

    mavlink_message_t msg;
    mavlink_status_t status;
};

#endif // DATAANALYSIS_H
