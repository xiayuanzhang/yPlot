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

      //设置数据格式
    void setDataType(QString type);
    //设置数据通道数量
    void setChannelNum(int num);
    //输入数据流
    void inputDataStream(QByteArray stream);

    void clearAnalysisBuff();

private:
    int dataTypeSize();
    //解析数据名
    void analysisDataName();
     //解析数据帧
    void analysisData();
    double dataChange(char *p);

signals:
    void haveNewData(QVector<QVector<double>> newdata);
    void haveNewName(QVector<QString> name);

private:
    int channels;
    QString dataType;
    QVector<QVector<double>> newDataList;
    QVector<QString> newName;

    const QByteArray frameNameHead = "AABBCC";
    const QByteArray frameNameEnd = "CCBBAA";
    const QByteArray frameDataHead = "DDEEFF";
    const QByteArray frameDataEnd = "FFEEDD";
    QByteArray inputDataBuff;
    QVector<QByteArray> dataNameBuff;
    QVector<QByteArray> dataBuff;
};

#endif // DATAANALYSIS_H
