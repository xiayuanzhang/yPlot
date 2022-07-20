#include "drawPlot.h"

drawPlot::drawPlot(QWidget *parent) :
    QCustomPlot(parent)
{
    //数据相关初始化


    nowTime = new QTime();

    //图表初始化
    //坐标轴初始化

    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
    timeTicker->setTimeFormat("%h:%m:%s");

    this->xAxis->setTicker(timeTicker);

    this->xAxis->setTickLabelFont(QFont("Helvetica",9));

    int nowtime = nowTime->currentTime().msecsSinceStartOfDay();
    this->xAxis->setRange(nowtime*0.001-_windTime,nowtime*0.001);
    this->xAxis->ticker()->setTickCount(6);//主刻度
    this->xAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);//可读性优于设置



    this->yAxis->setPadding(10);
    this->yAxis->setTickLabelFont(QFont("Helvetica",9));
    this->yAxis->setRange(-150, 150);
    this->yAxis->ticker()->setTickCount(8);//主刻度
    this->yAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);//可读性优于设置


    //框选放大设置
    this->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    this->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    this->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);


    this->setInteractions( QCP::iSelectPlottables| QCP::iSelectLegend);
    //图例设置
    this->legend->setVisible(true);
    this->legend->setFont(QFont("Helvetica",9));
    this->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    this->legend->setBrush(QColor(255, 255, 255, 150)); //背景透明

    //设置legend只能选择图例
    this->legend->setSelectableParts(QCPLegend::spItems);
    connect(this, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));




    //默认启用自适应Y
    enableAutoY(1);
    //默认启用x轴运动
    enableMoveX(1);

}

void drawPlot::selectionChanged()
{
  // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (this->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || this->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      this->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || this->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    this->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    this->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }
  // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
  if (this->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || this->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
      this->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || this->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
  {
    this->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    this->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
  }

  // 将图形的选择与相应图例项的选择同步
  for (int i=0; i<this->graphCount(); ++i)
  {
    QCPGraph *graph = this->graph(i);
    QCPPlottableLegendItem *item = this->legend->itemWithPlottable(graph);
    if (item->selected() || graph->selected())
    {
      item->setSelected(true);
      //注意：这句需要Qcustomplot2.0系列版本
      graph->setSelection(QCPDataSelection(graph->data()->dataRange()));
      if(graph->visible() == true){
          graph->setVisible(false);
      }
      else {
          graph->setVisible(true);
      }
      //这句1.0系列版本即可
      //graph->setSelected(true);
    }
  }
}


void drawPlot::resetPlot(int chs)
{
    _plot.clear();
    this->clearGraphs();
    for(int i = 0;i<chs;i++){
        _plot.append(this->addGraph());
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
    QVector<QCPGraph *> visiblePlot;

    //加载数据
    for(int i = 0;i<_plot.size();i++){
        _plot.at(i)->addData(key,newdata[i]);
        _plot.at(i)->data()->removeBefore(key-_buffTime);

        //将可见波形拿出来
        if(_plot.at(i)->visible())
            visiblePlot.append(_plot.at(i));
    }
    //自动调节Y轴
    for(int i = 0;i<visiblePlot.size();i++){
        if(autoY){
            if(i == 0)
                visiblePlot.at(i)->rescaleValueAxis(false,true); //不带true，y缩放到适应范围
            else
                visiblePlot.at(i)->rescaleValueAxis(true,true);//带true，只放大，不缩小
        }
    }

    if(moveX){
        this->xAxis->setRange(key-_windTime-_intervalTime,key-_intervalTime);
    }
    this->replot(QCustomPlot::rpQueuedReplot);
}

void drawPlot::enableAutoY(bool flag,Qt::Orientations orientations)
{
    autoY = flag ;
    if(autoY == false){//false 开启手动功能 //滚轮垂直方向缩放
        this->setInteractions(this->interactions() | QCP::iRangeZoom);
    }else {
        this->setInteractions(this->interactions() & (~QCP::iRangeZoom));
    }
    this->axisRect()->setRangeZoom(orientations);
}

void drawPlot::enableMoveX(bool flag ,Qt::Orientations orientations)
{
    moveX = flag;
    if(moveX == false){ //false 开启手动功能
        this->setInteractions(this->interactions() | QCP::iRangeDrag);
    }else {
       this->setInteractions(this->interactions() & (~QCP::iRangeDrag));
    }
    this->axisRect()->setRangeDrag(orientations);
}

void drawPlot::setBuffTime(double t)
{
    if(t<=0) t = 120; //120s
    _buffTime = t;
}

void drawPlot::setWindTime(double t)
{
    if(t<=0) t = 60; //60s
    _windTime = t;
    if(_windTime > _buffTime)
        _windTime = _buffTime;
}

void drawPlot::setIntervalTime(double t)
{
    if(t<0) t = 0;

    _intervalTime = t;
    if(_intervalTime + _windTime > _buffTime)
        _intervalTime = _buffTime - _windTime;
}

void drawPlot::mousePressEvent(QMouseEvent *event)
{
    //右键按下，菜单，或者拖动
    if(event ->button() & Qt::RightButton){
        this->setInteractions(this->interactions() | QCP::iRangeDrag); //此时只启动拖动功能，不禁用移动
        rightPress = 1;
        rightPressX = event->x();
    }

    //左键按下，框选放大，进入研究状态，此时暂停波形的自动调整行为，并且开启xy方向的拖拽行为
    if(event->button() & Qt::LeftButton){
        leftPress = 1;
        leftPressX = event->x();
    }
     QCustomPlot::mousePressEvent(event);
}

void drawPlot::mouseMoveEvent(QMouseEvent *event)
{
    bool hamper = 0;
    if(rightPress && abs(event->pos().x() - rightPressX) > 50){  //出现了个像素点的偏移，证明是拖动事件
        if(moveX) enableMoveX(0); //开始拖拽了，禁止自动移动
        //记录按下时的时间,作为窗口头
        if(rightPressTime <1) {
            rightPressTime = nowTime->currentTime().msecsSinceStartOfDay()*0.001;
            mouseMoveLast =  this->xAxis->pixelToCoord(event->x());
        }
        // 限定坐标轴
        double nowMouse = this->xAxis->pixelToCoord(event->x()); //获取鼠标当前位置
        double len =-(nowMouse - mouseMoveLast); //方向变一下
        qDebug()<<len;
        //出现了超过20ms的误差才处理一次
        if(this->xAxis->range().upper+len >= rightPressTime){
            hamper = 1;
            qDebug()<<"mouseMove:"<<this->xAxis->range().upper<<" ";
        }
        else if(this->xAxis->range().lower+len <= rightPressTime - _buffTime){
            hamper = 1;
            qDebug()<<"mouseMove:"<<this->xAxis->range().lower+len<<" "<< rightPressTime - _buffTime;
        }
        //其他时候就传递信号过去，自己就动了
        mouseMoveLast = nowMouse;//更新信号值
    }

    //----------------------------------------------------------------------
    if(leftPress == 1 && abs(event->pos().x() - leftPressX) > 50){//出现了15个像素点的偏移，证明是拖动事件
        //停止坐标轴运动，并且设置拖拽和放大为全方向
        enableMoveX(0,Qt::Horizontal|Qt::Vertical);
        enableAutoY(0,Qt::Horizontal|Qt::Vertical);
        leftMove = 1;
    }
    else if(leftPress == 1 && abs(event->pos().x() - leftPressX) < 10){//出现了15个像素点的偏移，证明是拖动事件
       hamper = 1;
    }


    if(hamper) return;
    QCustomPlot::mouseMoveEvent(event);
}

void drawPlot::mouseReleaseEvent(QMouseEvent *event)
{
    if((event ->button() & Qt::RightButton) && rightPressTime>1){ //表示是进过了拖拽状态的
        double wind = this->xAxis->range().upper;
        if(isZoom == 0){//未在缩放状态下，进行拖拽后允许运动
            setIntervalTime(rightPressTime-wind); //始终是正的
            enableMoveX(1);
        }
        //复位各个控制量
        rightPress = 0 ; //true 按下   false 未按下
        rightPressTime = 0; //初始按下的时间
        mouseMoveLast = 0; //鼠标按下时上一次的值
        rightPressX = 0; //用于判断鼠标是否移动
    }
    else if(event ->button() & Qt::RightButton){ //单纯的鼠标右键点击事件，创建次啊单
        //复位各个控制量
        rightPress = 0 ; //true 按下   false 未按下
        rightPressTime = 0; //初始按下的时间
        mouseMoveLast = 0; //鼠标按下时上一次的值
        rightPressX = 0; //用于判断鼠标是否移动

        QMenu *pMenu = new QMenu(this);

        QAction *actReset = new QAction(tr("复位"), this);
        QAction *actShowAll = new QAction(tr("显示全部"), this);
        QAction *actAutoY = new QAction(tr("自适应Y"), this);
        //把QAction对象添加到菜单上
        pMenu->addAction(actReset);
        pMenu->addAction(actShowAll);
        pMenu->addAction(actAutoY);
                //连接鼠标右键点击信号
        connect(actReset, SIGNAL(triggered()), this, SLOT(OnResetAction()));
        connect(actShowAll, SIGNAL(triggered()), this, SLOT(OnShowAllAction()));
        connect(actAutoY, SIGNAL(triggered()), this, SLOT(OnAutoYAction()));


        //在鼠标右键点击的地方显示菜单
        pMenu->exec(cursor().pos());

        //释放内存
        QList<QAction*> list = pMenu->actions();
        foreach (QAction* pAction, list) delete pAction;
        delete pMenu;
    }
    if((event->button() & Qt::LeftButton) && leftMove == 1){
        isZoom = 1;  //进入缩放状态
    }
    if(event->button() & Qt::LeftButton){
        leftMove = 0;
        leftPress = 0;
        rightPressX = 0;
    }

    QCustomPlot::mouseReleaseEvent(event);
}



void drawPlot::OnResetAction()
{
    isZoom = 0;
    enableAutoY(1);
    setIntervalTime(0);
    enableMoveX(1);
}

void drawPlot::OnShowAllAction()
{

}

void drawPlot::OnAutoYAction()
{
    if(autoY == 0){
        enableAutoY(1);

    }
    else{
        enableAutoY(0);
    }
}





