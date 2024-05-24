#ifndef VERTICALLINE_H
#define VERTICALLINE_H

#include <QWidget>

// verticalline.h
#include <QWidget>
#include <QColor>

class VerticalLine : public QWidget {
    Q_OBJECT

public:
    VerticalLine(QWidget* parent = nullptr);
    void setLength(int length);
    void setWidth(int width);
    void setColor(QColor color);
    void setLineStyle(Qt::PenStyle style);

    void setPosition(int x, int y);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    int length;
    int width;
    QColor color;
    Qt::PenStyle style;
    bool visible;
};




#endif // VERTICALLINE_H
