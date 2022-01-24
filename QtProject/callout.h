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

#ifndef CALLOUT_H
#define CALLOUT_H

#include <QtCharts/QChartGlobal>
#include <QtWidgets/QGraphicsItem>
#include <QtGui/QFont>
#include <QtCharts>
QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
QT_END_NAMESPACE

QT_CHARTS_BEGIN_NAMESPACE
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE



//一个在chartview根据鼠标显示 覆盖图层的类。
//输入：series集合、鼠标当前点（在chartview上的位置）
//输出：在chartview上显示鼠标的十字架点，在每条线对应的鼠标X位置显示小圆和数值

//特殊要求：显示的数值不能从重合，数字和点的颜色和线条一样。鼠标指示位置用虚线

class Callout
{
public:
    Callout(QChart *parent);
    //通道数量变化时，不用改变
    void showChartPos(QPointF pos,QVector<QLineSeries*> series,QVector<double> rect);
    void hideChartPos();


//    void setText(const QString &text);
//    void setAnchor(QPointF point);
//    void updateGeometry();

//    QRectF boundingRect() const;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,QWidget *widget);

protected:
//    void mousePressEvent(QGraphicsSceneMouseEvent *event);
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

private:

    QChart *m_chart;
    QVector<QGraphicsSimpleTextItem *>m_coordY;
    QVector<QGraphicsEllipseItem*>m_circle;
    QGraphicsLineItem *line;
};

#endif // CALLOUT_H
