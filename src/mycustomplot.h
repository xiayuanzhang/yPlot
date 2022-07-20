#ifndef MYCUSTOMPLOT_H
#define MYCUSTOMPLOT_H
#include "qcustomplot.h"

class MyCustomPlot: public QCustomPlot
{
    Q_OBJECT
public:
    MyCustomPlot();

    void mousePressEvent(QMouseEvent * event);
};

#endif // MYCUSTOMPLOT_H
