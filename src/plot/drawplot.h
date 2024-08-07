#ifndef DRAWPLOT_H
#define DRAWPLOT_H

#include <QObject>
#include <QVector>
#include "qcustomplot.h"
#include <QTimer>
#include <QPoint>
#include "mybuoy.h"


class MouseDrag;

class drawPlot: public QCustomPlot
{
    Q_OBJECT
public:
    drawPlot(QWidget *parent = 0);

    void initColor(int i);  //i控制使用几号方案
    QColor getColor(int i); //获取颜色方案中的颜色值
    QString getName(int i);
    double getXIndex();  //获取当前x轴索引值
    double getHeadXIndex(); //获取显示的第一个点的X索引值
    double increaseXIndex(); //增加x轴索引值.并返回增加后的值
    void resetXIndex(); //复位x轴索引值

    void resetXRange();
    void resetYRange();
    void resetXYRange(); //复位视图

    void setAutoXRange(bool enable); //是否使能X轴自动调整
    void autoXRange(void); //自动调整X轴范围
    void setAutoYRange(bool enable); //是否使能Y轴自动调整
    void autoYRange(void); //自动调整Y轴范围
    void setXRange(int lower, int upper); //手动设置X的范围. 触发自动调整会覆盖手动设置的值.

    void setRefreshInterval(int interval_ms); //设置刷新间隔

    void adjustPlotNums(int chs); //调整Y轴数量

    void clearAllPlot(); //清除曲线并复位视图

    void addPoint(QVector<QVector<double>> newdata); //添加数据点

    void setPlotName(QVector<QString> name); //设置曲线名称

    void setBuffSize(int t);//设置数据缓存区时间跨度
    void setWindSize(int t);//设置可视区域时间跨度
    int getBuffSize(){return m_buffSize;} //获取数据缓存区时间跨度
    int getWindSize(){return m_watchSize;} //获取可视区域时间跨度

    void setPlotWidth(int i);//设置曲线宽度

    void showAllPlot();  //显示所有曲线
    void hideAllPlot(); //隐藏所有曲线

    void moursePress(Qt::MouseButton but,QPoint point);
    void mouseDragStart(Qt::MouseButton but,QPoint point);
    void mouseDragMove(Qt::MouseButton but,QPoint point);
    void mouseDragEnd(Qt::MouseButton but,QPoint point);
    void mouseClick(Qt::MouseButton but,QPoint point);
    void mouseDoubleClick(Qt::MouseButton but,QPoint point);

protected:
     void mousePressEvent(QMouseEvent *event) ;
     void mouseMoveEvent(QMouseEvent *event) ;
     void mouseReleaseEvent(QMouseEvent *event) ;
     void mouseDoubleClickEvent(QMouseEvent *event);
     void wheelEvent(QWheelEvent *event);

private slots:

    void selectionChanged();
    void onLegendClick (QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event);
    void onLegendDoubleClick (QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event);

    void onPlottableClick (QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event);
    void onPlottableDoubleClick (QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event);

    void refreshView();

signals:
    //x的可见范围在buffer中的位置出现变化
    void xVisibleRangeChanged(double lower, double upper);
private:
    //x轴索引值记录
    double xIndexCount = 0;
    double xHeadIndexCount = 0;

    bool stopFlag = 0;
    int m_buffSize = 120;  //数据缓存区时间跨度,单位
    int m_watchSize = 30; //可视区域时间跨度，单位

    QVector<QCPGraph *>m_plot;
    QVector<QString> m_name;
    QVector<QColor> m_color;


    bool m_autoMoveX = false; //false ，不能自动动
    bool m_autoMoveY = false; //false 为不允许自动，允许手动

    MouseDrag *mouseDrag;
    bool m_isDrag = false;  //x处于拖拽中
    bool m_isRoom = false;  //是否处于放大缩小状态


    //刷新显示的定时器
    QTimer *refreshTimer;
    double lastXAxisLower = 0;
    double lastXAxisUpper = 0;

    MyBuoy *buoy = nullptr;

};





//识别鼠标拖动事件
class MouseDrag : public QObject
{
    Q_OBJECT
public:
    MouseDrag(QObject *parent = nullptr);
    ~MouseDrag();
    void press(QMouseEvent *event);
    void move(QMouseEvent *event);
    void release(QMouseEvent *event);
    void doubleClick(QMouseEvent *event);

signals:
    void pressed(Qt::MouseButton but, QPoint point);
    void clicked(Qt::MouseButton but, QPoint point);
    void startDrag(Qt::MouseButton but, QPoint point);
    void endDrag(Qt::MouseButton but, QPoint point);
    void drag(Qt::MouseButton but, QPoint point);
    void doubleClicked(Qt::MouseButton but, QPoint point);
private:
    //左键
    bool isPress = false;
    bool isDrag = false;
    QPoint pressPoint;
    QPoint movePoint;
    QPoint releasePoint;

    //右键
    bool isPressR = false;
    bool isDragR = false;
    QPoint pressPointR;
    QPoint movePointR;
    QPoint releasePointR;



    const int checkDragDirectionPix = 5;
};







#endif // DRAWPLOT_H
