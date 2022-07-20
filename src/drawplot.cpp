#include "drawPlot.h"

drawPlot::drawPlot(int queuesize,int windsize,QCustomPlot *cp)
{
    //数据相关初始化
    _queueSize = queuesize;
    _windSize = windsize;
    _customPlot = cp;

    //图表初始化
    // 设置坐标轴显示范围，不设置时默认范围为 0~5
    _customPlot->xAxis->setVisible(false);
    _customPlot->xAxis->setRange(_queueSize - _windSize,_queueSize);
    _customPlot->yAxis->setRange(-100, 100);
    _customPlot->yAxis->setRange(-150, 150);
    _customPlot->axisRect()->setupFullAxesBox();//四边安装轴并显示

    //_customPlot->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);
    _customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

    _customPlot->legend->setVisible(true);
    _customPlot->legend->setFont(QFont("Helvetica",9));

}

void drawPlot::resizeMem(int chs)
{
    _dataQueue.clear();
    _plot.clear();
    _customPlot->clearGraphs();
    _dataQueue.resize(chs);  //申请数据通道数量
    for(int i = 0;i<_dataQueue.size();i++){
        _dataQueue[i].resize(_queueSize+_safeLen); //为每个通道申请内存大小
        _plot.append(_customPlot->addGraph());
        _plot[i]->setPen(QPen(QColor((i*30)%255, (i*30)%255, (i*30)%255)));
    }
    //设置游标位置
    _head = -1;
    _windHeadtoHead = 0;
}

void drawPlot::addPoint(QVector<double> newdata)
{
    //软件第一次启动需要进行初始化
    if(!_intiFlag){
        resizeMem(newdata.size());
        //已经完成初始化
        _intiFlag = 1;
    }
    //数据通道出现变化
    if(_dataQueue.size() != newdata.size()){
        resizeMem(newdata.size());
    }

    queueCursorMove(); //移动游标
    for (int i = 0;i<_dataQueue.size();i++) {
         _dataQueue[i][_head] = newdata[i];  //保存数据
    }


//    qDebug()<<_head;
//    qDebug()<<_dataQueue;

    setPlotData(); //绘制数据

}

void drawPlot::setQueueSize(int size)
{
    if(_intiFlag==0) return;
    _queueSize = size;
    resizeMem(_dataQueue.size());
}

void drawPlot::setWindSize(int size)
{
    _windSize = size;
    if(_windSize > _queueSize)
        _windSize = _queueSize;
    _dataWind.clear();
    _dataWind.resize(_dataQueue.size());
    for(int i = 0;i<_dataWind.size();i++){
        _dataWind[i].resize(_windSize); //为每个通道申请内存大小
    }

    _windHeadtoHead = 0; //复位显示窗口
}

int drawPlot::getWindSize()
{
    return _windSize;
}

int drawPlot::getQueueSize()
{
    return _queueSize;
}

void drawPlot::setWindHeadToHead(int distance)
{
    _windHeadtoHead = distance;
    if(_windHeadtoHead + _safeLen + _windSize > _queueSize){
        _windHeadtoHead = _queueSize - _safeLen - _windSize;
    }
}

int drawPlot::getWindHeadToHead()
{
    return _windHeadtoHead;
}

QVector<QVector<double> > & drawPlot::getAllData()
{
    return _dataQueue;
}

int drawPlot::getWindHead()
{

    int windHead = _head - _windHeadtoHead;//windHead要读取的数据的下标
    if(windHead < 0)
        windHead += _queueSize;
    return windHead;
}

void drawPlot::setPlotData()
{
    // 添加一条绘图曲线
//    for(int i = 0;i<_dataQueue.size();i++){
//        _plot.at(i)->mySetData(_dataQueue[i],getWindHead(),_windSize,_queueSize,_windHeadtoHead);

//    }
//    _customPlot->replot();
    static int j = 100;
    for(int i = 0;i<_dataQueue.size();i++){

        j+=1;
        //_customPlot->rescaleAxes();
        //_plot.at(i)->rescaleValueAxis(true);//y的极大值显示出来，此时y的极大值在最大范围处
        _plot.at(i)->addData(j,_dataQueue[i].at(_head));
        //
    }
    //_customPlot->xAxis->setRange(j-10000, j);
    _customPlot->replot(QCustomPlot::rpQueuedReplot);
}


void drawPlot::queueCursorMove()
{
    _head++;
    if(_head >= _queueSize){
        _head = 0;
    }
}




