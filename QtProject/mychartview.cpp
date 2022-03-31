#include "mychartview.h"
#include <QDebug>

myChartView::myChartView(QWidget *parent) :
    QChartView(parent)
{
    setRubberBand(QChartView::RectangleRubberBand);
}

myChartView::myChartView(QChart *chart, QWidget *parent) :
    QChartView(chart, parent)
{
    setRubberBand(QChartView::RectangleRubberBand); // 这个好像是橡皮筋功能（左键框选放大）
}


//左右键单击信号，附带点击坐标
//左右键双击信号，附带点击坐标
//左右键拖动信号，附带起始坐标和终止坐标
//数据类型  QPointtF
//鼠标滚轮信号，

//全都直接返回在chartView中的坐标值，不经过变换

void myChartView::mousePressEvent(QMouseEvent *event)  //鼠标点击事件
{
    if(event->button() == Qt::LeftButton){
        pressFlag_left = true;
        pressPoint_left = event->pos(); //在chartView中的坐标值
        emit mousePressd(LEFT,pressPoint_left);
    }
    if(event->button() == Qt::RightButton){
        pressFlag_right = true;
        pressPoint_right = event->pos();
        emit mousePressd(RIGHT,pressPoint_right);
    }
    QChartView::mousePressEvent(event);
}

void myChartView::mouseMoveEvent(QMouseEvent *event)
{
    static QPointF lastPoint(0,0);
    if(pressFlag_left == true){
        emit mouseMove(LEFT,event->pos());
        emit mouseMoveSize(LEFT,event->x()-pressPoint_left.x(),event->y()-pressPoint_left.y());
    }
    else if(pressFlag_right == true){
        emit mouseMove(RIGHT,event->pos());
        emit mouseMoveSize(RIGHT,event->x()-pressPoint_right.x(),event->y()-pressPoint_right.y());
    }
    else {
        emit mouseMove(NOONE,event->pos());
        emit mouseMoveSize(NOONE,event->x()-lastPoint.x(),event->y()-lastPoint.y());
    }
    lastPoint = event->pos();
    QChartView::mouseMoveEvent(event);
}

void myChartView::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        pressFlag_left = false;
        releasePoint_left = event->pos();
        emit mouseRelease(LEFT,releasePoint_left);
        if(releasePoint_left == pressPoint_left){ //鼠标单击事件
            emit mouseClicked(LEFT,releasePoint_left);
        }
        else{ //按下移动，返回距离事件
            emit mousePressdToRelease(LEFT,releasePoint_left.x()-pressPoint_left.x(),
                                      releasePoint_left.y()-pressPoint_left.y());
        }

    }

    if(event->button() == Qt::RightButton){
        pressFlag_right = false;
        releasePoint_right = event->pos();
        emit mouseRelease(RIGHT,releasePoint_right);
        if(fabs(releasePoint_right.x() - pressPoint_right.x()) < 1
                && fabs(releasePoint_right.y() - pressPoint_right.y()) < 1){ //鼠标单击事件
            emit mouseClicked(RIGHT,releasePoint_right);

        }
        else{ //按下移动，返回距离事件
            emit mousePressdToRelease(RIGHT,releasePoint_right.x()-pressPoint_right.x(),
                                      releasePoint_right.y()-pressPoint_right.y());
        }
        return; //如果是右键，就不执行QChartView::mouseReleaseEvent(event); 避免原来的chartview响应右键释放事件
                //导致出现缩放。
    }
    QChartView::mouseReleaseEvent(event);
}


void myChartView::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        emit mouseDoubleClicked(LEFT,event->pos());
    }
    if(event->button() == Qt::RightButton){
        emit mouseDoubleClicked(RIGHT,event->pos());
    }

    QChartView::mouseDoubleClickEvent(event);
}

void myChartView::wheelEvent(QWheelEvent *event)
{
    wheelValue = event->delta(); //每次一个固定的值一样
    emit mouseWheel(wheelValue);

    QChartView::wheelEvent(event);
}
