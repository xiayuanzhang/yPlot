#include "drawplot.h"

drawplot::drawplot(QObject *parent) : QObject(parent)
{
    chart = new QChart(); //开辟空间
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    //chart->legend()->setAlignment(Qt::AlignRight);

    chart->addAxis(axisX,Qt::AlignBottom);
    chart->addAxis(axisY,Qt::AlignLeft);
    chart->axisX()->setRange(-50,50);
    chart->axisY()->setRange(-50,50);

    chart->layout()->setContentsMargins(0,0,0,0); //设置布局边界为0
    chart->legend()->setAlignment(Qt::AlignRight);


    //设置一点默认数据避免报错
    setChannels(1);
    setWatchSize(1000);
    setBuffSize(5000);
}

void drawplot::setChannels(int nums)
{
    if(channels == nums) return; //如果数量相等不需要处理
    interruptFlag = true;
    if(channels < nums){ //需要增加
        QList<QPointF> buff;  //初始化数据
        for(int i = 1;i<= buffSize;i++){
            buff.append(QPointF(i,0));
        }
        for(int i = 0;i<nums-channels;i++){
           QLineSeries *ser = new QLineSeries; // 需要是不同的LineSeries；
           series.append(ser);
           chart->addSeries(series[series.size()-1]);//添加series到chart
           series[series.size()-1]->attachAxis(axisX); //series绑定坐标轴，需要先将数据添加到chart中，再关联坐标轴
           series[series.size()-1]->attachAxis(axisY); //series绑定坐标轴
           QString name = "ch"+QString::number(series.size());
           series[series.size()-1]->setName(name); //设置series默认名称
           series[series.size()-1]->replace(buff);
        }
    }
    else if(channels > nums){ //需要减少
        for(int i = 0;i<channels-nums;i++){
            chart->removeSeries(series[series.size()-1]);
            series.removeAt(series.size()-1);
        }
    }
    //更新channels的值
    channels = nums;
    interruptFlag = false;

    connectMarkers();//将改变后的通道状况更新给marker

}

void drawplot::setWatchSize(int size)
{
    watchSize = size;
    if(buffSize < watchSize)
        buffSize = watchSize; //数据缓存区肯定不能比视窗区小涩
    //数据缓存区，相当于series的数组长度，视窗区是坐标轴的长度
    chart->axisX()->setRange(buffSize-watchSize+1,buffSize);


}

//点数据集更新还没有写
void drawplot::setBuffSize(int size)
{
    interruptFlag = true;
    buffSize = size;
    if(buffSize < watchSize)
        buffSize = watchSize; //数据缓存区肯定不能比视窗区小涩
    //数据缓存区，相当于series的数组长度，视窗区是坐标轴的长度
    chart->axisX()->setRange(buffSize-watchSize+1,buffSize);

    QList<QPointF> buff;
    for(int i = 1;i<= buffSize;i++){    //初始化数据
        buff.append(QPointF(i,0));
    }
    for(int j = 0;j<channels;j++){
        series[j]->replace(buff);
    }
    interruptFlag = false;

}

void drawplot::setChannelsName(QVector<QString> newName)
{
    for(int i = 0;i<channels;i++)
    {
        series[i]->setName(newName[i]);
    }
}

void drawplot::setPlotColor(int ch,const QColor color)
{
    if(ch < 0) return;
    if(ch > channels-1) return;
    series[ch]->setColor(color);
}


//ch 以0开始
void drawplot::hidePlot(int ch)
{
    if(ch < 0) return;
    if(ch > channels-1) return;
    chart->series().at(ch)->hide();
    updataLegendState(chart->legend()->markers().at(ch));
}

void drawplot::showAllPlot()
{
    for(int i = 0;i<channels;i++){
        chart->series().at(i)->show();
        updataLegendState(chart->legend()->markers().at(i));
    }
}

int drawplot::getWatchSize()
{
    return watchSize;
}

int drawplot::getBuffSize()
{
    return buffSize;
}

int drawplot::getChannels()
{
    return channels;
}

void drawplot::getMinMax_x(double *min, double *max)
{
    *min = axisX->min();
    *max = axisX->max();
}

void drawplot::getMinMax_y(double *min, double *max)
{
    *min = axisY->min();
    *max = axisY->max();
}

QVector<QString> drawplot::getChannelsName()
{
    QVector<QString> name;
    for(int i = 0;i<channels;i++){
        name.append(series[i]->name());
    }
    return name;
}


//数据缓存区为 1~buffsize
//series中点的索引为0~buffsize-1
//void drawplot::addPoint(QVector<QVector<double> > datalist)
//{
//    double axisYRangeMax = -9999999999;
//    double axisYRangeMin = 9999999999;
//    if(channels <= 0) return;
//    if(interruptFlag == true) return;
//    //有多少个通道
//    for(int i = 0;i < channels;i++){
//       QList<QPointF> buff = series[i]->points();

//       for(int j = 0;j < datalist.size();j++){  // 有多少个新的点
//          buff.removeFirst();
//       }
//       for(int j = 0;j < buff.size();j++){
//           buff[j].setX(buff[j].x()-datalist.size());  //X坐标偏移
//           if(buff[j].y() < axisYRangeMin){
//               axisYRangeMin = buff[j].y();
//           }
//           else if(buff[j].y() > axisYRangeMax){
//               axisYRangeMax = buff[j].y();
//           }
//       }
//       for(int j = 0;j < datalist.size();j++){
//         buff.append(QPointF(buffSize-datalist.size()+1,datalist[j][i]));
//       }
//       series[i]->replace(buff);
//    }
//    chart->axisY()->setRange(axisYRangeMin-axisYRangeMin*0.01,axisYRangeMax+axisYRangeMax*0.01);
//}

//addPoint函数优化
void drawplot::addPoint(QVector<QVector<double> > datalist)
{
    if(channels <= 0) return;
    if(interruptFlag == true) return;
    //有多少个通道
    int moveSize = datalist.size();
    for(int i = 0;i < channels;i++){
       QList<QPointF> buff = series[i]->points();
       for(int j = 0;j < buff.size()-moveSize;j++){
           buff[j].setY(buff[j+moveSize].y());

           if(buff[j].y() < axisYRangeMin){
               axisYRangeMin = buff[j].y();
           }
           else if(buff[j].y() > axisYRangeMax){
               axisYRangeMax = buff[j].y();
           }
       }
       for(int j = buff.size()-moveSize;j<buff.size();j++){
           buff[j].setY(datalist[j-(buff.size()-moveSize)][i]);
           if(buff[j].y() < axisYRangeMin){
               axisYRangeMin = buff[j].y();
           }
           else if(buff[j].y() > axisYRangeMax){
               axisYRangeMax = buff[j].y();
           }
       }
       series[i]->replace(buff);
    }

    if(chart->isZoomed() == false){  //未在放大状态下才自动Y轴
        if(axisYRangeMax < axisYRangeMin)
             chart->axisY()->setRange(-1,1);
        else
            chart->axisY()->setRange(axisYRangeMin-axisYRangeMin*0.01,axisYRangeMax+axisYRangeMax*0.01);
    }
}

void drawplot::clearPlot()
{
    interruptFlag = true;
    QList<QPointF> buff;
    for(int i = 1;i<= buffSize;i++){    //初始化数据
        buff.append(QPointF(i,0));
    }
    for(int j = 0;j<channels;j++){
        series[j]->replace(buff);
    }
    axisYRangeMax = -9999999999;
    axisYRangeMin = 9999999999;

    interruptFlag = false;
}

void drawplot::moveX(qreal size)
{
    qreal xmin = axisX->min();
    qreal xmax = axisX->max();
    qreal range = xmax-xmin;
    if(xmin+size <= 1){
        chart->axisX()->setRange(1,1+range);
    }
    else if (xmax+size > buffSize) {
        chart->axisX()->setRange(buffSize-range,buffSize);
    }
    else {
        chart->axisX()->setRange(xmin+size,xmax+size);
    }

}

void drawplot::moveY(qreal size)
{
    qreal ymin = axisY->min();
    qreal ymax = axisY->max();
    qreal leval = fabs(ymax-ymin)*0.1;

    chart->axisY()->setRange(ymin+size*leval,ymax+size*leval);
}

void drawplot::zoomRectangle(QPointF value1, QPointF value2)
{
    qreal buff;
    if(fabs(value1.x() - value2.x())<0.00001 || fabs(value1.y() - value2.y())<0.00001)
        return;
    if(value1.x() > value2.x()){
        buff = value1.x();
        value1.setX(value2.x());
        value2.setX(buff);
    }
    if(value1.y() > value2.y()){
        buff = value1.y();
        value1.setY(value2.y());
        value2.setY(buff);
    }
    chart->axisX()->setRange(value1.x(),value2.x());
    chart->axisY()->setRange(value1.y(),value2.y());
}

void drawplot::viewZoomReset()
{
    chart->zoomReset();
    axisX->setRange(buffSize-watchSize+1,buffSize);
    if(axisYRangeMax < axisYRangeMin)
         axisY->setRange(-1,1);
    else
        axisY->setRange(axisYRangeMin-axisYRangeMin*0.01,axisYRangeMax+axisYRangeMax*0.01);
}


void drawplot::connectMarkers()
{
//![1]
    // Connect all markers to handler
    const auto markers = chart->legend()->markers();
    for (QLegendMarker *marker : markers) {
        // Disconnect possible existing connection to avoid multiple connections
        QObject::disconnect(marker, &QLegendMarker::clicked,
                            this, &drawplot::handleMarkerClicked);
        QObject::connect(marker, &QLegendMarker::clicked, this, &drawplot::handleMarkerClicked);
    }
//![1]
}

void drawplot::handleMarkerClicked()
{
//![3]
    QLegendMarker* marker = qobject_cast<QLegendMarker*> (sender());
    Q_ASSERT(marker);
//![3]

//![4]
    switch (marker->type())
//![4]
    {
        case QLegendMarker::LegendMarkerTypeXY:
        {
//![5]
        // Toggle visibility of series
        marker->series()->setVisible(!marker->series()->isVisible());

        // Turn legend marker back to visible, since hiding series also hides the marker
        // and we don't want it to happen now.
        marker->setVisible(true);
//![5]

//![6]
        // Dim the marker, if series is not visible
        updataLegendState(marker);
//![6]
        break;
        }
    default:
        {
        qDebug() << "Unknown marker type";
        break;
        }
    }
}

void drawplot::updataLegendState(QLegendMarker* marker)
{
    qreal alpha = 1.0;

    if(marker->series()->isVisible()){
        alpha = 1.0;
    }
    else{
        alpha = 0.1;
    }
    QColor color;
    QBrush brush = marker->labelBrush();
    color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    marker->setLabelBrush(brush);

    brush = marker->brush();
    color = brush.color();
    color.setAlphaF(alpha);
    brush.setColor(color);
    marker->setBrush(brush);

    QPen pen = marker->pen();
    color = pen.color();
    color.setAlphaF(alpha);
    pen.setColor(color);
    marker->setPen(pen);
}
