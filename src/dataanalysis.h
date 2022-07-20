#ifndef DATAANALYSIS_H
#define DATAANALYSIS_H

#include <QObject>
#include <QVector>
#include <QDebug>


//数据名帧头：AABBCC
//数据名：数据名1,数据名2,数据名3,  （根据通道数量检查逗号，8通道应该右7个逗号）
//数据名帧尾 CCBBAA

//数据帧头：DDEEFF
//数据：类型*通道
//数据帧尾 FFEEDD

class dataAnalysis : public QObject
{
    Q_OBJECT
public:
    dataAnalysis();


    //获取数据通道数量
    int getChannelNum();
    //输入数据流
    void inputDataStream(QByteArray stream);
    void clearAnalysisBuff();
private:
    //解析数据名
    void analysisDataName(QByteArray stream);
     //解析数据帧
    void analysisData(QByteArray stream);

//    QString dataType;
//    int dataTypeSize();
//    double dataChange(char *p);

signals:
    void haveNewData(QVector<double> newdata);
    void haveNewName(QVector<QString> name);

private:

    const QByteArray frameNameHead = "AABBCC";
    const QByteArray frameNameEnd = "CCBBAA";
    const QByteArray frameDataHead = "DDEEFF";
    const QByteArray frameDataEnd = "FFEEDD";
    const int inputDataBuffSize = 1024*10; //最大10k缓存


    int channels;
    QVector<QString> lastName;
    QByteArray inputDataBuff;
};

#endif // DATAANALYSIS_H
