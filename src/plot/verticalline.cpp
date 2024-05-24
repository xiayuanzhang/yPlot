// verticalline.cpp
#include "verticalline.h"
#include <QPainter>

VerticalLine::VerticalLine(QWidget* parent) : QWidget(parent) {
    length = 100;
    width = 1;
    color = Qt::black;
    style = Qt::SolidLine;
    visible = true;
}

void VerticalLine::setLength(int newLength) {
    length = newLength;
    setFixedSize(width, length);
    update();
}

void VerticalLine::setWidth(int newWidth) {
    width = newWidth;
    setFixedSize(width, length);
    update();
}

void VerticalLine::setColor(QColor newColor) {
    color = newColor;
    update();
}

void VerticalLine::setLineStyle(Qt::PenStyle newStyle) {
    style = newStyle;
    update();
}

void VerticalLine::setPosition(int x, int y) {
    move(x, y);
}

void VerticalLine::paintEvent(QPaintEvent* event) {
    Q_UNUSED(event);
    if (visible) {
        QPainter painter(this);
        QPen pen;
        pen.setColor(color);
        pen.setWidth(width);
        pen.setStyle(style);
        painter.setPen(pen);
        painter.drawLine(QPoint(0, 0), QPoint(0, length));
    }
}
