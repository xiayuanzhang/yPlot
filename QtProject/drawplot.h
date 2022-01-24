#ifndef DRAWPLOT_H
#define DRAWPLOT_H

#include <QObject>
#include <QVector>
#include <QtCharts>
#include "mychartview.h"
using namespace QtCharts;

class drawplot : public QObject
{
    Q_OBJECT
public:
    //图标
    QChart* chart;
    //抽象数据集
    QVector<QLineSeries*> series;

    explicit drawplot(QObject *parent = nullptr);
    //设置通道数
    void setChannels(int nums);
    //设置视窗宽度
    void setWatchSize(int size);
    //设置数据缓存去宽度
    void setBuffSize(int size);
    //设置数据名
    void setChannelsName(QVector<QString> newName);
    //改变线条颜色
    void setPlotColor(int ch,const QColor color);
    //改变线条粗细
    //void setPlotPenSize();
    //设置视窗背后的格子大小
    //void setGridSize();
    //隐藏数据
    void hidePlot(int ch);
    //显示全部通道
    void showAllPlot();

    //获取视窗大小
    int getWatchSize(void);
    //获取缓冲区大小
    int getBuffSize(void);
    //获取通道数
    int getChannels(void);
    //获取Y最大最小值
    void getMinMax_x(double *min, double *max);
    void getMinMax_y(double *min, double *max);
    //获取X最大最小值
    //获取数据名
    QVector<QString> getChannelsName(void);
    //增加点数
    void addPoint(QVector<QVector<double>> datalist);
    //清除线条
    void clearPlot();

    //鼠标右键移动视窗
    void moveX(qreal size);
    void moveY(qreal size);
    //鼠标左键放大选中区域
    void zoomRectangle(QPointF value1,QPointF value2); //value1是指对应chart值的点，而不是坐标
    //复位视窗
    void viewZoomReset();






private:
    //更新坐标

    bool interruptFlag = false;
    int channels = 0;
    int buffSize = 0;
    int watchSize = 0;
    //Y轴范围自动更新的最大最小值
    double axisYRangeMax = -9999999999;
    double axisYRangeMin = 9999999999;

    QVector<QString> channelsName;

    //坐标轴相关成员
    QValueAxis *axisX;
    QValueAxis *axisY;



    //********************图例************************//
    void connectMarkers();
    void handleMarkerClicked();
    void updataLegendState(QLegendMarker* marker);

signals:

public slots:



};

#endif // DRAWPLOT_H
