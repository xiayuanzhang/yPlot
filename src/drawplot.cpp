#include "drawPlot.h"

drawPlot::drawPlot(QWidget *parent) :
    QCustomPlot(parent)
{
    //数据相关初始化


    nowTime = new QTime();

    //图表初始化
    //坐标轴初始化
    //this->xAxis->setTickLabelFont(QFont("Helvetica",9));
    this->xAxis->setRange(_buffSize-_windSize,_buffSize);
    this->xAxis->ticker()->setTickCount(15);//主刻度
    this->xAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);//可读性优于设置
    this->xAxis->setTickLabels(false);



    this->yAxis->setPadding(10);
    this->yAxis->setTickLabelFont(QFont("Helvetica",9));
    this->yAxis->setRange(-10, 10);
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
  for (int i=0; i<_plot.size(); ++i)
  {
    QCPGraph *graph = _plot.at(i);
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
    for (int i = 0;i<_plot.size();i++) {
        QCPGraph *graph = _plot.at(i);
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
    m_xStart = 0;        //控制X轴运动的变量
    this->clearGraphs();   //清空视图
    this->clearItems(); //清空图元

    //浮动竖线
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
    //创建数据通道，和对应的，图元
    for(int i = 0;i<chs;i++){
        _plot.append(this->addGraph()); //初始化空间
        _plot.at(i)->setPen(QPen(getColor(i)));

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

        //初始化线条显示名称的文本颜色
        item = this->legend->itemWithPlottable(_plot.at(i));
        item->setTextColor(_plot.at(i)->pen().color());
    }
    //设置线条粗细
    setPlotWidth(1);
}

void drawPlot::clearAllPlot()
{
    QVector<QString> namebuff;
    for(int i = 0;i<_plot.size();i++){
        namebuff.append(_plot.at(i)->name());
    }
    initPlots(_plot.size());
    for(int i = 0;i<_plot.size();i++){
        _plot.at(i)->setName(namebuff.at(i));
    }
}

#include <QDebug>
#include <windows.h>

//QVector<QVector<double>> newdata
//通道<数据帧<double>> newdata
void drawPlot::plotDataChanged(QVector<QVector<double>> newdata)
{
#if 1
    LARGE_INTEGER litmp;
    LONGLONG Qpart1,Qpart2,Useingtime;
    double dfMinus,dfFreq,dfTime;


    //获得CPU计时器的时钟频率
    QueryPerformanceFrequency(&litmp);//取得高精度运行计数器的频率f,单位是每秒多少次（n/s），
    dfFreq = (double)litmp.QuadPart;

    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
    Qpart1 = litmp.QuadPart; //开始计时
   #endif


   //数据通道出现变化，就先重置线条，然后再添加数据，否则就直接添加
    if(_plot.size() != newdata.size()){
        initPlots(newdata.size());
    }

    m_plotNum = newdata.size();  //获取数据通道数量

    QVector<QCPGraph *> visiblePlot;

    QVector<double> xNow;  
    //有几帧数据,就生成几个x值
    for(int i = 0;i<newdata[0].size();i++){
        m_xStart++;
        if(m_xStart >= (1.79769e+308-1)){
            m_xStart = 0;
            initPlots(_plot.size());
        }
        xNow.append(m_xStart+_buffSize);
        
    }
    //qDebug()<<"xNow:"<<xNow;
    for(int i = 0;i<_plot.size();i++){
        _plot.at(i)->addData(xNow,newdata[i]);
        _plot.at(i)->data()->removeBefore(m_xStart);

        //将可见波形拿出来
        if(_plot.at(i)->visible())
            visiblePlot.append(_plot.at(i));
    }
    //自动调节Y轴
    if(autoY){
//        this->yAxis->setRange(-10,10);
//        this->rescaleAxes();  //如果频繁调用将会严重影响绘图效率
//        this->yAxis->rescale(true); //如果频繁调用将会严重影响绘图效率

    }

    if(moveX && stopFlag==false){
        this->xAxis->setRange(m_xStart+_buffSize-_windSize-_intervalSize
                              ,m_xStart+_buffSize-_intervalSize);
        setDataLineX();
    }
    this->replot(QCustomPlot::rpQueuedReplot);


#if 1
    QueryPerformanceCounter(&litmp);//取得高精度运行计数器的数值
    Qpart2 = litmp.QuadPart; //终止计时

    dfMinus = (double)(Qpart2 - Qpart1);//计算计数器值
    dfTime = dfMinus / dfFreq;//获得对应时间，单位为秒,可以乘1000000精确到微秒级（us）
    Useingtime = dfTime*1000000;

    qDebug()<<dfTime<<"s";
#endif

}

void drawPlot::plotNameChanged(QVector<QString> name)
{
    //数据通道出现变化，就先重置线条，然后再设置名字，否则就直接设置
    if(_plot.size() != name.size()){
        initPlots(name.size());
    }

    QCPPlottableLegendItem *item;
    for(int i = 0;i<_plot.size();i++){
        _plot.at(i)->setName(name.at(i));
        item = this->legend->itemWithPlottable(_plot.at(i));
        if(_plot.at(i)->visible()){
            item->setTextColor(_plot.at(i)->pen().color());
        }
        else{
            item->setTextColor(QColor(0xDDDDDD)); //图例文字颜色变灰，表示隐藏了
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

void drawPlot::setBuffSize(int t)
{
    if(t<=0) t = 30; //120
    _buffSize = t;
}

void drawPlot::setWindSize(int t)
{
    if(t<=0) t = 1; //60s
    _windSize = t;
    if(_windSize > _buffSize)
        _windSize = _buffSize;
}

void drawPlot::setIntervalSize(int t)
{
    if(t<0) t = 0;

    _intervalSize = t;
    if(_intervalSize + _windSize > _buffSize)
        _intervalSize = _buffSize - _windSize;

    intervaChanged(_intervalSize); //发送变化信号
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
        if(rightPressCount <1) {
            rightPressCount = m_xStart+_buffSize;
            mouseMoveLast =  this->xAxis->pixelToCoord(event->x());
        }
        // 限定坐标轴
        double nowMouse = this->xAxis->pixelToCoord(event->x()); //获取鼠标当前位置
        double len =-(nowMouse - mouseMoveLast); //方向变一下
        if(this->xAxis->range().upper+len >= rightPressCount){
            hamper = 1;
            //qDebug()<<"mouseMove:"<<this->xAxis->range().upper<<" ";
        }
        else if(this->xAxis->range().lower+len <= rightPressCount - _buffSize){
            hamper = 1;
            //qDebug()<<"mouseMove:"<<this->xAxis->range().lower+len<<" "<< rightPressCount - _buffSize;
        }
        if(hamper == 0){
            int start = m_xStart+_buffSize;
            int wind = static_cast<int>(this->xAxis->range().upper);
            setIntervalSize(start - wind); //始终是正的
            //mouseEventIntervaChanged(start - wind); //发送变化信号
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
    if((event ->button() & Qt::RightButton) && rightPressCount>1){ //表示是进过了拖拽状态的
        if(isZoom == 0){//未在缩放状态下，进行拖拽后允许运动
            enableMoveX(1);
        }
        //复位各个控制量
        rightPress = 0 ; //true 按下   false 未按下
        rightPressCount = 0; //初始按下的时间
        mouseMoveLast = 0; //鼠标按下时上一次的值
        rightPressX = 0; //用于判断鼠标是否移动
    }
    else if(event ->button() & Qt::RightButton){ //单纯的鼠标右键点击事件，创建次啊单
        //复位各个控制量
        resetPlotView();
        rightPress = 0 ; //true 按下   false 未按下
        rightPressCount = 0; //初始按下的时间
        mouseMoveLast = 0; //鼠标按下时上一次的值
        rightPressX = 0; //用于判断鼠标是否移动
    }
    if((event->button() & Qt::LeftButton) && leftMove == 1){
        isZoom = 1;  //进入缩放状态
        hideDataLinex();//隐藏图元

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
    if(_plot.size()<1) return; //没有数据不能执行

    if(x  > 1)  //如果输入了X就覆盖原来的值，如果没有输入X的值就不改变
        dataLineX = x;

    //重新划线
    dataLine->point1->setPixelPosition(QPointF(dataLineX,1));
    dataLine->point2->setPixelPosition(QPointF(dataLineX,2));

    //获取数据点的索引,所有线条的数据点数一样多，所以可以只用一条线来找
    double sortkey = this->xAxis->pixelToCoord(dataLineX);

    //更新X,时间的显示
    dataKey->setText(QString::number(sortkey-m_xStart));
    double y = this->yAxis->coordToPixel(this->yAxis->range().lower);
    dataKey->position->setPixelPosition(QPointF(dataLineX,y-8));

    //更新点和数据
    int index = _plot.at(0)->findEnd(sortkey); //获取索引
    int penWidth= _plot.at(0)->pen().width()/2+3;  //小圆圈始终比线宽大4个像素点
    for(int i = 0;i<_plot.size();i++){
        if(_plot.at(i)->visible() == false) {
            dataEllipses.at(i)->setVisible(false); //不显示
        }
        else {
            double value = _plot.at(i)->data()->at(index)->value;
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

void drawPlot::hideDataLinex()
{
    for(int i = 0;i<this->dataTexts.size();i++){
        dataTexts.at(i)->setVisible(false);
        dataEllipses.at(i)->setVisible(false);//显示
    }
}



void drawPlot::resetPlotView()
{
    this->xAxis->setRange(_buffSize-_windSize,_buffSize);
    isZoom = 0;
    setStopShow(0);
    enableAutoY(1);
    setIntervalSize(0);
    enableMoveX(1);

}

void drawPlot::showAllPlot()
{
    for(int i = 0;i<_plot.size();i++){
        _plot.at(i)->setVisible(true);
        QCPPlottableLegendItem *mitem = this->legend->itemWithPlottable(_plot.at(i));
        mitem->setSelected(false);
        mitem->setTextColor(_plot.at(i)->pen().color()); //恢复颜色
    }
}

void drawPlot::hideAllPlot()
{
    for(int i = 0;i<_plot.size();i++){
        _plot.at(i)->setVisible(false);
        QCPPlottableLegendItem *mitem = this->legend->itemWithPlottable(_plot.at(i));
        mitem->setSelected(false);
        mitem->setTextColor(QColor(0xDDDDDD)); //恢复颜色
    }
}






