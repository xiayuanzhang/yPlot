#ifndef DRAWPLOT_H
#define DRAWPLOT_H

#include <QObject>
#include <QVector>
#include "qcustomplot.h"

class drawPlot
{
public:
    drawPlot(int bufftime ,int windtime ,QCustomPlot *cp);

    void resetPlot(int chs);
    void addPoint(QVector<double> newdata);
    void setPlotData(QVector<double> newdata);
    //是否允许Y轴自动调整
    void enableAutoY(bool flag = false);
    void enableMoveX(bool flag = false);

    void setBuffTime(int t);
    void setWindTime(int t);
    void setIntervalTime(int t);

private:


private:
    bool _intiFlag = 0; //表示未完成初始化，需要等有第一个数据输入，完成了初始化之后才能开始工作

    int _buffTime = 120;  //数据缓存区时间跨度,单位s
    int _windTime = 60; //可视区域时间跨度，单位s
    int _intervalTime = 0; //可视区域和最新时间的间隔，控制视窗移动
    QTime *nowTime;

    QCustomPlot *_customPlot;//绘图窗口
    QVector<QCPGraph *>_plot;


    bool autoY = false; //false 为不允许
    bool moveX = false;


};

#endif // DRAWPLOT_H
