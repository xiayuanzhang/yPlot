#ifndef MYCHARTVIEW_H
#define MYCHARTVIEW_H
#include <QtCharts/QChartView>
#include <QtWidgets/QRubberBand>

QT_CHARTS_USE_NAMESPACE

#define NOONE 0
#define LEFT 1
#define RIGHT 2


class myChartView: public QChartView
{
    Q_OBJECT
public:
    explicit myChartView(QWidget *parent = Q_NULLPTR);
    explicit myChartView(QChart *chart, QWidget *parent = Q_NULLPTR);
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
private:
    //左右键单击信号，附带点击坐标
    //左右键双击信号，附带点击坐标
    //左右键拖动信号，附带起始坐标和终止坐标
    //数据类型  QPointtF
    //鼠标滚轮信号，
    QPointF pressPoint_left, pressPoint_right;
    QPointF releasePoint_left, releasePoint_right;
    QPointF doubleClickPoint_left,doubleClickPoint_right;
    bool pressFlag_left,pressFlag_right;
    int wheelValue;


signals:
    void mouseMove(int key,QPointF nowPos);  //0 无按键，1左键，2右键
    void mouseMoveSize(int key,qreal dx,qreal dy);  //0 无按键，1左键，2右键
    void mouseDoubleClicked(int key,QPointF clickPos); //0 无按键，1左键，2右键
    void mouseClicked(int key,QPointF clickPos);//0 无按键，1左键，2右键
    void mousePressd(int key,QPointF pressPos);//0 无按键，1左键，2右键
    void mouseRelease(int key,QPointF releasekPos);//0 无按键，1左键，2右键
    //返回按下到释放的距离
    void mousePressdToRelease(int key,double xsize,double ysize);//0 无按键，1左键，2右键
    void mouseWheel(int value);
};

#endif // MYCHARTVIEW_H
