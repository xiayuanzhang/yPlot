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


    //曲线可选，图例可选，可多选
    this->setInteractions( QCP::iSelectPlottables| QCP::iSelectLegend| QCP::iMultiSelect|QCP::iSelectItems);
    this->setMultiSelectModifier(Qt::ControlModifier);// 使用ctrl键来多选
    //图例设置
    this->legend->setVisible(true);
    this->legend->setFont(QFont("Helvetica",11,QFont::Bold));
    this->axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignLeft);
    this->legend->setBrush(QColor(255, 255, 255, 150)); //背景透明
    this->legend->setRowSpacing(5);

    this->legend->setSelectableParts(QCPLegend::spItems); //设置legend只能选择图例
    this->legend->setSelectedFont(QFont("Helvetica",11,QFont::Bold)); //设置选中的字体样式
    this->legend->setBorderPen(Qt::NoPen); //不要图例框的边框
    connect(this, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged())); //连接信号

    connect(this,SIGNAL(legendClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)),
            this,SLOT(onLegendClick (QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)));
    connect(this,SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)),
            this,SLOT(onLegendDoubleClick (QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)));


    connect(this,SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)),
            this,SLOT(onPlottableClick (QCPAbstractPlottable*, int, QMouseEvent*)));
    connect(this,SIGNAL(plottableDoubleClick(QCPAbstractPlottable*,int,QMouseEvent*)),
            this,SLOT(onPlottableDoubleClick  (QCPAbstractPlottable*, int, QMouseEvent*)));


    //默认启用自适应Y
    enableAutoY(1);
    //默认启用x轴运动
    enableMoveX(1);

    //初始化颜色
    initColor(1);


}

//颜色获取网站
//  https://mokole.com/palette.html
void drawPlot::initColor(int i)
{
    if(i == 0){
        plotColor.append(0x2f4f4f); //darkslategray
        plotColor.append(0x8b0000); // darkred
        plotColor.append(0x808000); // olive
        plotColor.append(0x3cb371); //mediumseagreen
        plotColor.append(0x00008b); // darkblue
        plotColor.append(0xb03060); //maroon3
        plotColor.append(0xff0000); //red
        plotColor.append(0xff8c00); //darkorange
        plotColor.append(0xffd700); //gold
        plotColor.append(0x00ff7f); //springgreen
        plotColor.append(0x4169e1); //royalblue
        plotColor.append(0x00ffff); //aqua
        plotColor.append(0x00bfff); //deepskyblue
        plotColor.append(0x0000ff); //greenyellow
        plotColor.append(0xadff2f); //blue
        plotColor.append(0xda70d6); //orchid
        plotColor.append(0xd8bfd8); //thistle
        plotColor.append(0xff00ff); //fuchsia
        plotColor.append(0xeee8aa); //palegoldenrod
        plotColor.append(0xffa07a); //lightsalmon
    }
    else if(i == 1){
        plotColor.append(0x000001); //black
        plotColor.append(0x2e8b57); // maroon
        plotColor.append(0x800000); //olive
        plotColor.append(0x808000); // purple2
        plotColor.append(0x7f007f); //maroon3
        plotColor.append(0xff0000); //red
        plotColor.append(0x0000cd); //mediumblue
        plotColor.append(0xffd700); //gold
        plotColor.append(0x00ff00); //lime
        plotColor.append(0x00fa9a); //mediumspringgreen
        plotColor.append(0x4169e1); //royalblue
        plotColor.append(0x00ffff); //aqua
        plotColor.append(0x00bfff); //deepskyblue
        plotColor.append(0xf08080); //lightcoral
        plotColor.append(0xff00ff); //fuchsia
        plotColor.append(0xeee8aa); //palegoldenrod
        plotColor.append(0xffff54); //laserlemon
        plotColor.append(0xdda0dd); //plum
        plotColor.append(0xff1493); //deeppink
        plotColor.append(0x696969); // seagreen
    }
}

QColor drawPlot::getColor(int i)
{
    if(i>=plotColor.size()){
        i = i-plotColor.size();
    }
    return plotColor.at(i);
}

void drawPlot::selectionChanged()
{
  // 将图形的选择与相应图例项的选择同步
  //
  for (int i=0; i<this->graphCount(); ++i)
  {
    QCPGraph *graph = this->graph(i);
    QCPPlottableLegendItem *item = this->legend->itemWithPlottable(graph);

    if(dataEllipses.at(i)->selected() || dataTexts.at(i)->selected() || graph -> selected()){
        dataEllipses.at(i)->setSelected(false); //变为不选中
        dataTexts.at(i)->setSelected(false);

        QPen pen = graph->pen();
        pen.setWidthF(pen.widthF()+1.5);
        graph ->  selectionDecorator() -> setPen(pen);
        graph -> setSelection(QCPDataSelection(graph -> data() -> dataRange()));

        item->setSelectedTextColor(pen.color()); //选中的颜色也和线条一样，相当于不变化
        item->setSelected(true);
    }
    else if(!(graph -> selected())){
      item->setSelected(false);
    }


  }

}

void drawPlot::onLegendClick(QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event)
{
    Q_UNUSED(event)
    Q_UNUSED(legend)
    for (int i = 0;i<this->graphCount();i++) {
        QCPGraph *graph = this->graph(i);
        QCPPlottableLegendItem *mitem = this->legend->itemWithPlottable(graph);
        if(mitem == item){
            item->setSelected(false);  //复位选中，不将选中表现出来
            if(graph->visible() == true){
                graph->setVisible(false);//设置为不可见
                item->setTextColor(QColor(0xDDDDDD)); //图例文字颜色变灰，表示隐藏了
            }
            else {
                graph->setVisible(true);//设置为可见
                item->setTextColor(graph->pen().color()); //恢复颜色
            }
            break;
        }
    }

}


void drawPlot::onLegendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item, QMouseEvent *event)
{
    Q_UNUSED(event)
    Q_UNUSED(legend)
    item->setSelected(false);  //复位选中，不将选中表现出来
}

//
void drawPlot::onPlottableClick(QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event)
{
    qDebug()<<"adadad";
    Q_UNUSED(event)
    Q_UNUSED(plottable)
    Q_UNUSED(dataIndex)
}

void drawPlot::onPlottableDoubleClick(QCPAbstractPlottable *plottable, int dataIndex, QMouseEvent *event)
{
    Q_UNUSED(event)
    Q_UNUSED(plottable)
    Q_UNUSED(dataIndex)
}


void drawPlot::initPlots(int chs)
{
    QCPPlottableLegendItem *item;
    _plot.clear();         //清除句柄保存
    dataTexts.clear();    //清空句柄
    dataEllipses.clear(); //清空句柄
    this->clearGraphs();   //清空视图
    this->clearItems(); //清空图元

    //浮标
    dataLine = new QCPItemStraightLine(this);
    QPen pen1 = dataLine->pen();
    pen1.setColor(Qt::black);
    pen1.setStyle(Qt::DotLine);
    //pen1.setWidth(1);
    dataLine->setPen(pen1);
    dataLine->setSelectable(false); //禁用选中
    //显示X值的图元
    dataKey = new QCPItemText(this);
    dataKey->setFont(QFont("Helvetica",7));
    dataKey->setColor(Qt::black);
    dataKey->position->setAxes(this->xAxis,this->yAxis);
    dataKey->setSelectable(false);
    //创建数据通道
    for(int i = 0;i<chs;i++){
        _plot.append(this->addGraph()); //初始化空间
        _name.append("ch"+QString::number(i)); //初始化空间

        _plot.at(i)->setPen(QPen(getColor(i)));
        _plot.at(i)->pen().setWidth(i);

        QCPItemText* itext = new  QCPItemText(this);
        QCPItemEllipse* iellipes = new  QCPItemEllipse(this);
        //初始化图元并添加，后面就只需要设置位置即可
        itext->setFont(QFont("Helvetica",8));
        itext->setColor(Qt::black);
        itext->position->setAxes(this->xAxis,this->yAxis);
        itext->setPositionAlignment(Qt::AlignVCenter);
        itext->setSelectable(false);

        iellipes->topLeft->setAxes(this->xAxis,this->yAxis);
        iellipes->bottomRight->setAxes(this->xAxis,this->yAxis);
        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(getColor(i));
        QPen pen;
        pen.setColor(getColor(i));
        iellipes->setPen(pen);
        iellipes->setBrush(brush);
        iellipes->setSelectable(false);

//        //保存句柄
        dataTexts.append(itext);
        dataEllipses.append(iellipes);

    }

    //名称和数据长度同步
    while(_name.size() > _plot.size()){
        _name.removeLast();
    }
    while(_name.size() < _plot.size()){
        _name.append("chx");
    }

    //添加名称
    for(int i = 0;i<chs;i++){
        _plot.at(i)->setName(_name.at(i));
        item = this->legend->itemWithPlottable(_plot.at(i));
        item->setTextColor(_plot.at(i)->pen().color());
    }
    setPlotWidth(1);
}

void drawPlot::clearAllPlot()
{
    this->clearGraphs();   //清空曲线
    this->clearItems(); //清空图元
}

void drawPlot::addPoint(QVector<double> newdata)
{
    //软件第一次启动需要进行初始化
    if(!_intiFlag){
        initPlots(newdata.size());
        //已经完成初始化
        _intiFlag = 1;
    }
    //数据通道出现变化
    if(_plot.size() != newdata.size()){
        initPlots(newdata.size());
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
        setDataLineX();
    }
    this->replot(QCustomPlot::rpQueuedReplot);
}

void drawPlot::setPlotName(QVector<QString> name)
{
    QCPPlottableLegendItem *item;
    _name = name; //将名字保存起来
    if(_plot.size() >= 1){  //如果没有数据就不更新，有数据就直接更新
        while(_name.size() > _plot.size()){
            _name.removeLast();
        }
        while(_name.size() < _plot.size()){
            _name.append("chx");
        }

        for(int i = 0;i<_name.size();i++){
            _plot.at(i)->setName(_name.at(i));
            item = this->legend->itemWithPlottable(_plot.at(i));
            item->setTextColor(_plot.at(i)->pen().color());
        }
    }
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

void drawPlot::setPlotWidth(int i)
{
    for(int j = 0;j<_plot.size();j++){
        QPen pen= _plot.at(j)->pen();
        pen.setWidth(i);
        _plot.at(j)->setPen(pen);
    }
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
        //qDebug()<<len;
        //出现了超过20ms的误差才处理一次
        if(this->xAxis->range().upper+len >= rightPressTime){
            hamper = 1;
            //qDebug()<<"mouseMove:"<<this->xAxis->range().upper<<" ";
        }
        else if(this->xAxis->range().lower+len <= rightPressTime - _buffTime){
            hamper = 1;
            //qDebug()<<"mouseMove:"<<this->xAxis->range().lower+len<<" "<< rightPressTime - _buffTime;
        }
        //其他时候就传递信号过去，自己就动了
        mouseMoveLast = nowMouse;//更新信号值
    }

    //----------------------------------------------------------------------
    if(leftPress == 1 && abs(event->pos().x() - leftPressX) > 20){//出现了15个像素点的偏移，证明是拖动事件
        //停止坐标轴运动，并且设置拖拽和放大为全方向
        enableMoveX(0,Qt::Horizontal|Qt::Vertical);
        enableAutoY(0,Qt::Horizontal|Qt::Vertical);
        leftMove = 1;
    }
    else if(leftPress == 1){
       hamper = 1;
    }
//------------------------------------浮标
    //获取坐标,窗体鼠标的位置，不是曲线x轴的值
    setDataLineX(event->x());

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

void drawPlot::mouseDoubleClick(QMouseEvent *event)
{
    Q_UNUSED(event)
    //拦截掉双击信号
}

void drawPlot::setDataLineX(double x)
{
    QVector<double> visibleValue;
    QVector<double> visibleYPixel;
    if(this->graphCount()<1 || _intiFlag == false) return; //没有数据不能执行

    if(x  > 1)  //如果输入了X就覆盖原来的值，如果没有输入X的值就不改变
        dataLineX = x;

    //重新划线
    dataLine->point1->setPixelPosition(QPointF(dataLineX,1));
    dataLine->point2->setPixelPosition(QPointF(dataLineX,2));



    //获取数据点的索引,所有线条的数据点数一样多，所以可以只用一条线来找
    double sortkey = this->xAxis->pixelToCoord(dataLineX);

    //更新X,时间的显示
    QString time = QTime::fromMSecsSinceStartOfDay(int(sortkey*1000)).toString("hh:mm:ss-zzz");
    dataKey->setText(time);//time.toString("hh:mm:ss-zzz")
    double y = this->yAxis->coordToPixel(this->yAxis->range().lower);
    dataKey->position->setPixelPosition(QPointF(dataLineX,y-8));

    //更新点和数据
    int index = this->graph(0)->findEnd(sortkey); //获取索引
    int penWidth= this->graph(0)->pen().width()/2+3;  //小圆圈始终比线宽大4个像素点
    for(int i = 0;i<this->graphCount();i++){
        if(this->graph(i)->visible() == false) {
            dataEllipses.at(i)->setVisible(false); //不显示
        }else {
            double value = this->graph(i)->data()->at(index)->value;
            double yPixel = this->yAxis->coordToPixel(value); //y轴刻度会变化，所以转变为像素点更方便控制原型的大小
            //记录y ，value,为显示文本做准备
            visibleValue.append(value);
            visibleYPixel.append(yPixel);
            //更新小圆圈的显示
            dataEllipses.at(i)->topLeft->setPixelPosition(
                        QPointF(dataLineX-penWidth,yPixel-penWidth));
            dataEllipses.at(i)->bottomRight->setPixelPosition(
                        QPointF(dataLineX+penWidth,yPixel+penWidth));
            dataEllipses.at(i)->setVisible(true);//显示
        }
    }
    // 冒泡排序
    for (int i = 0; i < visibleValue.size(); ++i)
    {
        for (int j = 0; j < visibleValue.size() - 1 - i; ++j)
        {
            if (visibleValue[j] < visibleValue[j + 1])  // 从大排到小
            {
                double temp1 = visibleValue[j];
                double temp2 = visibleYPixel[j];
                visibleValue[j] = visibleValue[j + 1];
                visibleValue[j + 1] = temp1;
                visibleYPixel[j] = visibleYPixel[j + 1];
                visibleYPixel[j + 1] = temp2;
            }
        }
    }
//    qDebug()<<visibleValue;
//    qDebug()<<visibleYPixel;
    //显示文本
    double itemHeight = dataTexts.at(0)->bottomLeft->pixelPosition().y()
                -dataTexts.at(0)->topLeft->pixelPosition().y();
    for(int i = 0;i<this->dataTexts.size();i++){
        if(i < visibleValue.size()){  //显示图例
            dataTexts.at(i)->setVisible(true);
            dataTexts.at(i)->setText(QString::number(visibleValue[i]));
            dataTexts.at(i)->position->setPixelPosition(
                        QPointF(dataLineX+penWidth+2,visibleYPixel[i]));//向右偏移
            if(i>=1){
                if(dataTexts.at(i-1)->bottomLeft->pixelPosition().y()
                        > dataTexts.at(i)->topLeft->pixelPosition().y()){ //出现重合现象
                    dataTexts.at(i)->position->setPixelPosition(  //设置当前点紧贴上一个点
                                QPointF(dataLineX+penWidth+2
                                        ,dataTexts.at(i-1)->left->pixelPosition().y()+itemHeight));
                }
            }
        }
        else {  //不显示
            dataTexts.at(i)->setVisible(false);
        }



    }

    this->replot(QCustomPlot::rpQueuedReplot);

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
    for(int i = 0;i<this->graphCount();i++){
        this->graph(i)->setVisible(true);
        QCPPlottableLegendItem *mitem = this->legend->itemWithPlottable(this->graph(i));
        mitem->setSelected(false);
        mitem->setTextColor(this->graph(i)->pen().color()); //恢复颜色
    }
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





