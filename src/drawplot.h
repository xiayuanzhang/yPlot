#ifndef DRAWPLOT_H
#define DRAWPLOT_H

#include <QObject>
#include <QVector>
#include "qcustomplot.h"

class drawPlot
{
public:
    drawPlot(int queuesize,int windsize,QCustomPlot *cp);

    void resizeMem(int chs);
    void addPoint(QVector<double> newdata);
    void setQueueSize(int size);
    void setWindSize(int size);
    int getWindSize();
    int getQueueSize();

    void setWindHeadToHead(int distance);  //设置窗口头部距离数据头部的距离
    int getWindHeadToHead();
    QVector<QVector<double> > &getAllData();
    int getWindHead();

    void setPlotData();

private:
    void queueCursorMove();  //计算光标的循环位置
    void windCursorMove();  //可视窗口

private:
    bool _intiFlag = 0; //表示未完成初始化，需要等有第一个数据输入，完成了初始化之后才能开始工作

    int _queueSize = 0;  //数据缓存区大小
    int _windSize = 0; //可视区域大小

    QVector<QVector<double>> _dataQueue; //数据缓存二维数组
    QVector<QVector<double>> _dataWind; //要显示的数据二维数组

    QCustomPlot *_customPlot;//绘图窗口
    QVector<QCPGraph *>_plot;

    int _head = -1; //环形缓存队列插入数据的游标,_head 指向最新更新的数据下标
    int _windHeadtoHead = 0;//可视窗口头,距离数据游标的头
    int _safeLen =  5; //可视窗口尾部 _windEnd 和 _Head 间隔的最小距离

};

#endif // DRAWPLOT_H
