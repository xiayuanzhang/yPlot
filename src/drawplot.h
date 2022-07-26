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

    void initColor(int i);  //i控制使用几号方案
    QColor getColor(int i);

    void initPlots(int chs);
    void clearAllPlot();
    void plotDataChanged(QVector<double> newdata);
    void setPlotData(QVector<double> newdata);
    void plotNameChanged(QVector<QString> name);
    //是否允许Y轴自动调整
    void enableAutoY(bool flag = false,Qt::Orientations orientations = Qt::Vertical);
    void enableMoveX(bool flag = false ,Qt::Orientations orientations = Qt::Horizontal);
    bool getAutoYState(){return autoY;}

    void setBuffSize(int t);
    void setWindSize(int t);
    void setIntervalSize(int t);
    int getBuffSize(){return _buffSize;}
    int getWindSize(){return _windSize;}
    int getIntervalSize(){return _intervalSize;}



    void setPlotWidth(int i);


     void resetPlotView();
     void showAllPlot();
     void hideAllPlot();
     void setStopShow(bool stop){stopFlag = stop; emit stopStatusChanged(stopFlag);}

protected:
     void mousePressEvent(QMouseEvent *event) ;
     void mouseMoveEvent(QMouseEvent *event) ;
     void mouseReleaseEvent(QMouseEvent *event) ;
     void mouseDoubleClick(QMouseEvent *event) ;


     void setDataLineX(double x = -1);
     void hideDataLinex();

private slots:

    void selectionChanged();
    void onLegendClick (QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event);
    void onLegendDoubleClick (QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event);

    void onPlottableClick (QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event);
    void onPlottableDoubleClick (QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event);

signals:
    void intervaChanged(int interval_size);
    void stopStatusChanged(bool);

private:
    int dataCount = 0;

    bool _intiFlag = 0; //表示未完成初始化，需要等有第一个数据输入，完成了初始化之后才能开始工作
    bool stopFlag = 0;
    int _buffSize = 120;  //数据缓存区时间跨度,单位
    int _windSize = 30; //可视区域时间跨度，单位
    int _intervalSize = 0; //可视区域和最新时间的间隔，控制视窗移动
    QTime *nowTime;

    QVector<QCPGraph *>_plot;
    QVector<QString> _name;
    QVector<QColor> plotColor;


    bool autoY = false; //false 为不允许自动，允许手动
    bool moveX = false; //false ，不能自动动

    //右键拖动相关状态量。
    bool rightPress = 0 ; //true 按下   false 未按下
    double rightPressCount = 0; //初始按下的时间
    double mouseMoveLast = 0; //鼠标按下时上一次的值
    int rightPressX = 0; //用于判断鼠标是否移动

    //左键缩放
    bool leftPress = 0 ; //true 按下   false 未按下
    int leftPressX = 0; //用于判断鼠标是否移动
    bool leftMove = 0; //是否进行了拖拽
    bool isZoom = 0;

    //浮标
    QCPItemStraightLine *dataLine;
    QCPItemText *dataKey;

    QVector<QCPItemText*> dataTexts;
    QVector<QCPItemEllipse*> dataEllipses;
    double dataLineX = 0;

};

#endif // DRAWPLOT_H
