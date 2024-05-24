#ifndef MYBUOY_H
#define MYBUOY_H

#include <QWidget>
#include "qcustomplot.h"
#include "verticalline.h"


/**
 * @brief The Buoy class
 * 这个类应该是和RectAxis关联的,因为图元是绘制在这个窗口上面的.
 * 浮标类
 * 1. 添加删除内容,传递颜色和名称
 * 2. 传入xy的位置
 * 2. 输入QVector的数据组,来显示内容
 * 3. 设置显示位置
 * 4. 控制是否显示
 */
class MyBuoy
{
public:
    MyBuoy(QCustomPlot *plot);
    ~MyBuoy();

    void setEnable(QCPGraph *plot,bool en);
    void setAllEnable(bool en);
    bool isEnable(QCPGraph *plot);

    void enableShow(bool en){enshow = en;}
    void setFont(QFont font){label->setFont(font);}
    /**
     * @brief setPixelPos 设置游标的位置
     * @param pixel 屏幕上的像素点
     */
    void setPixelPos(QPointF pixel){pixelPos = pixel;}

    void refresh();
protected:
    void syncGraphNums();

    void clearText(){
        label->clear();
    }
    void appendText(QString text,QColor color){
        QString labelText = label->text();
        labelText += QString("<p style='line-height: 70%; color: %1;'>%2</p>").arg(color.name()).arg(text);
        label->setText(labelText);
    }

private:
    QCustomPlot *qcp;

    int lastAxisrect = 0; //当前所在矩形视窗
    VerticalLine *keyLine;
    QLabel *label;

    bool enshow = true;
    QPointF pixelPos = QPointF(0,0);


    QVector<bool> isShow;
};

#endif // MYBUOY_H
