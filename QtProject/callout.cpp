/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the Qt Charts module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 or (at your option) any later version
** approved by the KDE Free Qt Foundation. The licenses are as published by
** the Free Software Foundation and appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "callout.h"
#include <QtGui/QPainter>
#include <QtGui/QFontMetrics>
#include <QtWidgets/QGraphicsSceneMouseEvent>
#include <QtGui/QMouseEvent>
#include <QtCharts/QChart>

Callout::Callout(QChart *chart):
    m_chart(chart)
{
    line = new QGraphicsLineItem(m_chart);
}


void Callout::showChartPos(QPointF pos,QVector<QLineSeries*> series,QVector<double> rect)
{
    int series_size = series.size();
    int coordY_size = m_coordY.size();
    int circle_size = m_circle.size();

    //1、保证显示的图元数量和通道数量相等
    if(coordY_size < series_size){
       for(int i = 0;i< series_size - coordY_size;i++){
           QGraphicsSimpleTextItem *item = new QGraphicsSimpleTextItem(m_chart);
           m_coordY.append(item);

       }
    }
    else if (coordY_size>series_size) {
        for(int i = 0;i< coordY_size - series_size;i++){
            delete m_coordY.last();
            m_coordY.removeLast();
        }
    }

    if(circle_size < series_size){
       for(int i = 0;i< series_size - circle_size;i++){
           QGraphicsEllipseItem *item = new QGraphicsEllipseItem(m_chart);
           m_circle.append(item);
       }
    }
    else if (circle_size>series_size) {
        for(int i = 0;i< circle_size - series_size;i++){
            delete m_circle.last();
            m_circle.removeLast();
        }
    }

    //2、进行坐标变换，输入的是chartview上的坐标
    auto axis_pos = m_chart->mapToValue(pos);//将chartview的pos转换到对应x坐标轴的值
    QVector<qreal>  show_value;//将对应坐标轴的点的值取出来>
    QVector<QColor> show_color;
    QVector<QPointF> show_pos; //用来显示的位置
    for(int i=0;i<series.size();i++){
        show_value.append(series.at(i)->at(static_cast<int>(axis_pos.x())).y());
        show_color.append(series.at(i)->color());
        QPointF position_y = m_chart->mapToPosition(QPointF(0,show_value.at(i)));
        show_pos.append(QPointF(pos.x(),position_y.y())); //显示在鼠标的X，通道的数值y处
    }


    //3、设置显示的图元
    for(int i = 0;i<m_coordY.size();i++){
        QPen pen;
        pen.setColor(show_color.at(i));
        m_coordY[i]->setPos(show_pos.at(i));
        m_coordY[i]->setText(QString("%2 ").arg(show_value.at(i)));
        m_coordY[i]->setPen(pen);

        if(!series.at(i)->isVisible()){  //如果线条不可见就隐藏
            m_coordY[i]->hide();
        }
        else if(axis_pos.x() < rect.at(0) || axis_pos.x() > rect.at(1)){
           m_coordY[i]->hide();
        }
        else
            m_coordY[i]->show();
    }

    //避免重叠，如果出现了重叠就往下偏移
//    int font_size = m_coordY[0]->font().pointSize(); //字体大小是9
//    for(int i = 0;i<m_coordY.size();i++){
//        //和自己之前的比较
//        for(int j = 0;j<i;j++){
//            auto va = m_coordY[i]->pos().y() - m_coordY[j]->pos().y();
//            if(abs(va) < font_size) //出现了重叠
//            {

//            }
//        }
//        //和自己之后的比较
//        for(int j = i+1;j<m_coordY.size();j++){

//        }


//        qDebug()<<m_coordY[i]->font().pixelSize();
//        qDebug()<<m_coordY[i]->font().pointSize(); //字体大小是9
//        qDebug()<<m_coordY[i]->boundingRect();
//    }

    for(int i = 0;i<m_circle.size();i++){
        QPen pen;
        pen.setColor(show_color.at(i));
        pen.setWidth(3);
        m_circle[i]->setPen(pen);

        QBrush brush;
        brush.setColor(show_color.at(i));
        m_circle[i]->setBrush(brush);

        m_circle[i]->setPos(show_pos.at(i));
        m_circle[i]->setRect( QRect(-3,-3,6,6));

        if(!series.at(i)->isVisible()){  //如果线条不可见就隐藏
            m_circle[i]->hide();
        }
        else if(axis_pos.x() < rect.at(0) || axis_pos.x() > rect.at(1))
            m_circle[i]->hide();
        else
            m_circle[i]->show();
    }




    //4.显示鼠标x的虚线
    //rect中数据顺序：xmin,xmax,ymin,ymax
    QPen linepen;
    linepen.setStyle(Qt::DotLine);
    linepen.setWidth(1);
    line->setPen(linepen);
    line->setLine(pos.x(),m_chart->mapToPosition(QPointF(0,rect.at(2))).y(),
                  pos.x(),m_chart->mapToPosition(QPointF(0,rect.at(3))).y());
    if(axis_pos.x() < rect.at(0) || axis_pos.x() > rect.at(1))
        line->hide();
    else
        line->show();
}

void Callout::hideChartPos()
{
    for(int i = 0;i<m_coordY.size();i++){
        m_coordY[i]->hide();
    }
    for(int i = 0;i<m_circle.size();i++){
        m_circle[i]->hide();
    }
    line->hide();
}
