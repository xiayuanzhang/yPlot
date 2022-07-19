
#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H
#include <QObject>
#include <QList>


//创建此类自动打开文件对话框,选择保存路径，设置文件名，按照文件名创建文件夹，数据就保存在文件夹中
//如果没有输入文件名，就自动按时间确定，或者是违规操作

//文件夹中按每一个线条创建文件保存，文件名称为通道名称
//文件内容为 X值 ， Y值

class outputData : public QObject
{
public:
    outputData(QVector<int*> ser);
    void setFolderPath();

    void outputCsv(QString fileName,QList<QPointF> data);

private:

};

#endif // OUTPUTDATA_H
