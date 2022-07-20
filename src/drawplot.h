#ifndef DRAWPLOT_H
#define DRAWPLOT_H

#include <QObject>
#include <QVector>
#include "qcustomplot.h"

class drawPlot: public QCustomPlot
{
    Q_OBJECT
public:
    drawPlot(QWidget *parent = 0);

    void resetPlot(int chs);
    void addPoint(QVector<double> newdata);
    void setPlotData(QVector<double> newdata);
    //是否允许Y轴自动调整
    void enableAutoY(bool flag = false,Qt::Orientations orientations = Qt::Vertical);
    void enableMoveX(bool flag = false ,Qt::Orientations orientations = Qt::Horizontal);

    void setBuffTime(double t);
    void setWindTime(double t);
    void setIntervalTime(double t);

protected:
     void mousePressEvent(QMouseEvent *event) ;
     void mouseMoveEvent(QMouseEvent *event) ;
     void mouseReleaseEvent(QMouseEvent *event) ;

private slots:
    void OnResetAction();
    void OnShowAllAction();
    void OnAutoYAction();

    void selectionChanged();

private:
    bool _intiFlag = 0; //表示未完成初始化，需要等有第一个数据输入，完成了初始化之后才能开始工作

    double _buffTime = 240;  //数据缓存区时间跨度,单位s
    double _windTime = 60; //可视区域时间跨度，单位s
    double _intervalTime = 0; //可视区域和最新时间的间隔，控制视窗移动
    QTime *nowTime;

    QVector<QCPGraph *>_plot;


    bool autoY = false; //false 为不允许自动，允许手动
    bool moveX = false; //false ，不能自动动

    //右键拖动相关状态量。
    bool rightPress = 0 ; //true 按下   false 未按下
    double rightPressTime = 0; //初始按下的时间
    double mouseMoveLast = 0; //鼠标按下时上一次的值
    int rightPressX = 0; //用于判断鼠标是否移动

    //左键缩放
    bool leftPress = 0 ; //true 按下   false 未按下
    int leftPressX = 0; //用于判断鼠标是否移动
    bool leftMove = 0; //是否进行了拖拽
    bool isZoom = 0;


};

#endif // DRAWPLOT_H
