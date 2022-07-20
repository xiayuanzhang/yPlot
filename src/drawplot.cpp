#include "drawPlot.h"

drawPlot::drawPlot(int bufftime ,int windtime,QCustomPlot *cp)
{
    //数据相关初始化
    setBuffTime(bufftime);
    setWindTime(windtime);

    _customPlot = cp;

    nowTime = new QTime();

    //图表初始化
    //坐标轴初始化

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    _customPlot->xAxis->setTicker(timeTicker);

    _customPlot->xAxis->setTickLabelFont(QFont("Helvetica",9));

    int nowtime = nowTime->currentTime().msecsSinceStartOfDay();
    _customPlot->xAxis->setRange(nowtime*0.001-_windTime,nowtime*0.001);
    _customPlot->xAxis->ticker()->setTickCount(6);//主刻度
    _customPlot->xAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);//可读性优于设置



    _customPlot->yAxis->setPadding(10);
    _customPlot->yAxis->setTickLabelFont(QFont("Helvetica",9));
    _customPlot->yAxis->setRange(-150, 150);
    _customPlot->yAxis->ticker()->setTickCount(8);//主刻度
    _customPlot->yAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);//可读性优于设置


    _customPlot->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    _customPlot->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    _customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);


    //_customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
    //_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    //_customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    //_customPlot->axisRect()->setRangeDrag(Qt::Horizontal);


    _customPlot->legend->setVisible(true);
    _customPlot->legend->setFont(QFont("Helvetica",9));


    //默认启用自适应Y
    enableAutoY();
    //默认启用x轴运动
   enableMoveX();

}

void drawPlot::resetPlot(int chs)
{
    _plot.clear();
    _customPlot->clearGraphs();
    for(int i = 0;i<chs;i++){
        _plot.append(_customPlot->addGraph());
        _plot[i]->setPen(QPen(QColor((i*30)%255, (i*30)%255, (i*30)%255)));
    }
}

void drawPlot::addPoint(QVector<double> newdata)
{
    //软件第一次启动需要进行初始化
    if(!_intiFlag){
        resetPlot(newdata.size());
        //已经完成初始化
        _intiFlag = 1;
    }
    //数据通道出现变化
    if(_plot.size() != newdata.size()){
        resetPlot(newdata.size());
    }

    setPlotData(newdata); //绘制数据

}



void drawPlot::setPlotData(QVector<double> newdata)
{
    int nowtime = nowTime->currentTime().msecsSinceStartOfDay();
    double key = nowtime*0.001;
    for(int i = 0;i<_plot.size();i++){
        if(autoY){
            if(i == 0)
                _plot.at(i)->rescaleValueAxis(false,true); //不带true，y缩放到适应范围
            else
                _plot.at(i)->rescaleValueAxis(true,true);//带true，只放大，不缩小
        }
        _plot.at(i)->addData(key,newdata[i]);
        _plot.at(i)->data()->removeBefore(key-_buffTime);
    }
    if(moveX){
        _customPlot->xAxis->setRange(key-_windTime-_intervalTime,key-_intervalTime);
    }
    _customPlot->replot(QCustomPlot::rpQueuedReplot);
}

void drawPlot::enableAutoY(bool flag)
{
    autoY = flag ;
    if(!autoY){
         //滚轮垂直方向缩放
        _customPlot->setInteractions(_customPlot->interactions() | QCP::iRangeZoom);
        _customPlot->axisRect()->setRangeZoom(Qt::Vertical);
    }else {
        _customPlot->setInteractions(_customPlot->interactions() & (!QCP::iRangeZoom));
    }
}

void drawPlot::enableMoveX(bool flag)
{
    moveX = flag;
    if(!moveX){
        _customPlot->setInteractions(_customPlot->interactions() | QCP::iRangeDrag);
        _customPlot->axisRect()->setRangeDrag(Qt::Horizontal);
    }else {
        _customPlot->setInteractions(_customPlot->interactions() & (!QCP::iRangeDrag));
    }
}

void drawPlot::setBuffTime(int t)
{
    if(t<=0) t = 120; //120s
    _buffTime = t;
}

void drawPlot::setWindTime(int t)
{
    if(t<=0) t = 60; //60s
    _windTime = t;
    if(_windTime > _buffTime)
        _windTime = _buffTime;
}

void drawPlot::setIntervalTime(int t)
{
    if(t<0) t = 0;

    _intervalTime = t;
    if(_intervalTime + _windTime > _buffTime)
        _intervalTime = _buffTime - _windTime;
}





