#include "drawPlot.h"

drawPlot::drawPlot(QWidget *parent) :
    QCustomPlot(parent)
{
    //数据相关初始化


    refreshTimer = new QTimer(this);
    connect(refreshTimer,&QTimer::timeout,this,&drawPlot::refreshView);
    refreshTimer->start(17); //60Hz
    qDebug()<<QThread::currentThread();

    //图表初始化
    //坐标轴初始化
    //this->xAxis->setTickLabelFont(QFont("Helvetica",9));
    this->xAxis->setRange(m_buffSize-m_watchSize,m_buffSize);
    this->xAxis->ticker()->setTickCount(5);//主刻度
    this->xAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);//可读性优于设置
    //设置tick字体
    this->xAxis->setTickLabelFont(QFont("Helvetica",8));
    //this->xAxis->setTickLabels(false);


    //Y轴初始化
    this->yAxis->setPadding(10);
    this->yAxis->setTickLabelFont(QFont("Helvetica",8));
    this->yAxis->setRange(-1, 1);
    this->yAxis->ticker()->setTickCount(8);//主刻度
    this->yAxis->ticker()->setTickStepStrategy(QCPAxisTicker::tssReadability);//可读性优于设置


    //框选放大样式设置
    this->selectionRect()->setPen(QPen(Qt::black,1,Qt::DashLine));//设置选框的样式：虚线
    this->selectionRect()->setBrush(QBrush(QColor(0,0,100,50)));//设置选框的样式：半透明浅蓝
    this->setSelectionRectMode(QCP::SelectionRectMode::srmZoom);

    //曲线可选，图例可选，可多选
    //取消曲线可选 QCP::iSelectPlottables|
    this->setInteractions(  QCP::iSelectLegend| QCP::iMultiSelect|QCP::iSelectItems);
    this->setMultiSelectModifier(Qt::ControlModifier);// 使用ctrl键来多选

    //启用拖拽和缩放功能
    this->setInteractions(this->interactions() | QCP::iRangeDrag| QCP::iRangeZoom);


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
            this,SLOT(onLegendClick(QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)));
    connect(this,SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)),
            this,SLOT(onLegendDoubleClick(QCPLegend*, QCPAbstractLegendItem*, QMouseEvent*)));


    connect(this,SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)),
            this,SLOT(onPlottableClick (QCPAbstractPlottable*, int, QMouseEvent*)));
    connect(this,SIGNAL(plottableDoubleClick(QCPAbstractPlottable*,int,QMouseEvent*)),
            this,SLOT(onPlottableDoubleClick(QCPAbstractPlottable*, int, QMouseEvent*)));


    //初始化颜色
    initColor(1);

    //鼠标拖动检测
    mouseDrag = new MouseDrag(this);
    connect(mouseDrag, &MouseDrag::startDrag, this, &drawPlot::mouseDragStart);
    connect(mouseDrag, &MouseDrag::drag, this, &drawPlot::mouseDragMove);
    connect(mouseDrag, &MouseDrag::endDrag, this, &drawPlot::mouseDragEnd);
    connect(mouseDrag, &MouseDrag::clicked, this, &drawPlot::mouseClick);


    //移动
    setAutoXRange(true);
    setAutoYRange(true);

    buoy = new MyBuoy(this);
    buoy->setFont(QFont("Helvetica",9));
}

//颜色获取网站
//  https://mokole.com/palette.html
void drawPlot::initColor(int i)
{
    if(i == 0){
        m_color.append(0x2f4f4f); //darkslategray
        m_color.append(0x8b0000); // darkred
        m_color.append(0x808000); // olive
        m_color.append(0x3cb371); //mediumseagreen
        m_color.append(0x00008b); // darkblue
        m_color.append(0xb03060); //maroon3
        m_color.append(0xff0000); //red
        m_color.append(0xff8c00); //darkorange
        m_color.append(0xffd700); //gold
        m_color.append(0x00ff7f); //springgreen
        m_color.append(0x4169e1); //royalblue
        m_color.append(0x00ffff); //aqua
        m_color.append(0x00bfff); //deepskyblue
        m_color.append(0x0000ff); //greenyellow
        m_color.append(0xadff2f); //blue
        m_color.append(0xda70d6); //orchid
        m_color.append(0xd8bfd8); //thistle
        m_color.append(0xff00ff); //fuchsia
        m_color.append(0xeee8aa); //palegoldenrod
        m_color.append(0xffa07a); //lightsalmon
    }
    else if(i == 1){
        m_color.append(0x000001); //black
        m_color.append(0x2e8b57); // maroon
        m_color.append(0x800000); //olive
        m_color.append(0x808000); // purple2
        m_color.append(0x7f007f); //maroon3
        m_color.append(0xff0000); //red
        m_color.append(0x0000cd); //mediumblue
        m_color.append(0xffd700); //gold
        m_color.append(0x00ff00); //lime
        m_color.append(0x00fa9a); //mediumspringgreen
        m_color.append(0x4169e1); //royalblue
        m_color.append(0x00ffff); //aqua
        m_color.append(0x00bfff); //deepskyblue
        m_color.append(0xf08080); //lightcoral
        m_color.append(0xff00ff); //fuchsia
        m_color.append(0xeee8aa); //palegoldenrod
        m_color.append(0xffff54); //laserlemon
        m_color.append(0xdda0dd); //plum
        m_color.append(0xff1493); //deeppink
        m_color.append(0x696969); // seagreen
    }
}

QColor drawPlot::getColor(int i)
{
    if(m_color.isEmpty()){
        return QColor(0x000001);//black
    }
    if(i>=m_color.size()){
        i = i % m_color.size();
    }
    return m_color.at(i);
}

QString drawPlot::getName(int i)
{
    if(m_name.isEmpty()){
        return QString("CH%1").arg(i);
    }
    if(i>=m_name.size()){
        i = i % m_name.size();
    }
    return m_name.at(i);
}

double drawPlot::getXIndex()
{
    return xIndexCount;
}

double drawPlot::increaseXIndex()
{
    xIndexCount++;
    return xIndexCount;
}

void drawPlot::resetXIndex()
{
    xIndexCount = 0;
}

void drawPlot::resetXRange()
{
    if(getXIndex() < m_watchSize){
        this->xAxis->setRange(0,m_watchSize);
    }
    else{
        this->xAxis->setRange(getXIndex()-m_watchSize,getXIndex());
    }
    //this->replot(QCustomPlot::rpQueuedReplot);
}

void drawPlot::resetYRange()
{
    this->yAxis->setRange(-0.00000001,0.00000001);
    //this->yAxis->setRange(-300,300);
    //this->replot(QCustomPlot::rpQueuedReplot);
}

void drawPlot::resetXYRange()
{
    resetXRange();
    resetYRange();

}

void drawPlot::setAutoXRange(bool enable)
{
    m_autoMoveX = enable;
}

void drawPlot::autoXRange()
{
    double x = getXIndex();
    //拖拽状态对X轴自动移动, 有最高优先级的限制作用
    if(x > m_watchSize && m_autoMoveX && !m_isDrag && !m_isRoom){
        this->xAxis->setRange(x - m_watchSize,x);
    }
}

void drawPlot::setAutoYRange(bool enable)
{
    m_autoMoveY = enable;
}

void drawPlot::autoYRange()
{
    //自动调整Y轴
    if(m_autoMoveY && !m_isDrag && !m_isRoom){
        this->yAxis->rescale(true); //true表示值控制可见的曲线
    }
}

void drawPlot::setRefreshInterval(int interval_ms)
{
    refreshTimer->start(interval_ms);
}

void drawPlot::selectionChanged()
{
  // 将图形的选择与相应图例项的选择同步
  //
  for (int i=0; i<m_plot.size(); ++i)
  {
    QCPGraph *graph = m_plot.at(i);
    QCPPlottableLegendItem *item = this->legend->itemWithPlottable(graph);

    if(graph -> selected()){
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
    for (int i = 0;i<m_plot.size();i++) {
        QCPGraph *graph = m_plot.at(i);
        QCPPlottableLegendItem *mitem = this->legend->itemWithPlottable(graph);
        /*点击图例切换显示和隐藏*/
        if(mitem == item){
            item->setSelected(false);  //复位选中，不将选中表现出来
            if(graph->visible() == true){
                graph->setVisible(false);//设置为不可见
                item->setTextColor(QColor(0xDDDDDD)); //图例文字颜色变灰，表示隐藏了
                buoy->setEnable(m_plot.at(i),false);
            }
            else {
                graph->setVisible(true);//设置为可见
                item->setTextColor(graph->pen().color()); //恢复颜色
                buoy->setEnable(m_plot.at(i),true);
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

//更新显示
void drawPlot::refreshView()
{
    double min = 0;
    //buff中最早点的x值
    if(!m_plot.isEmpty()){
        min = m_plot.at(0)->data().data()->at(0)->key;
    }

    double lower = this->xAxis->range().lower - min;
    double upper = this->xAxis->range().upper - min;

    //发出当前X轴的范围
    if(lower != lastXAxisLower || upper != lastXAxisUpper){
        //更新历史值
        lastXAxisLower = lower;
        lastXAxisUpper = upper;

        emit xVisibleRangeChanged(lower,upper);
    }

    buoy->refresh();

    //刷新波形
    this->replot(QCustomPlot::rpQueuedReplot);
}


void drawPlot::adjustPlotNums(int chs)
{
    QCPPlottableLegendItem *item;
    m_plot.clear();         //清除句柄保存
    resetXIndex();
    this->clearGraphs();   //清空视图
    this->clearItems(); //清空图元

    //创建数据通道，和对应的，图元
    for(int i = 0;i<chs;i++){
        m_plot.append(this->addGraph()); //初始化空间
        m_plot.at(i)->setPen(QPen(getColor(i)));
        m_plot.at(i)->setName(getName(i));

        //设置图例颜色
        item = this->legend->itemWithPlottable(m_plot.at(i));
        item->setTextColor(m_plot.at(i)->pen().color());
        item->setFont(QFont("Helvetica",9));
    }
    //设置线条粗细
    setPlotWidth(1);

    //设置X轴范围
    resetXYRange();
}

void drawPlot::clearAllPlot()
{
    for(int i = 0;i<m_plot.size();i++){
        m_plot.at(i)->data()->clear();
    }
    resetXYRange();

    //this->replot(QCustomPlot::rpQueuedReplot);
}

//新增数据, 并且进行滚动
void drawPlot::addPoint(QVector<QVector<double>> newdata)
{
    //QVector<QVector<double>> newdata
    //<点数<通道数量>> newdata

   //数据通道出现变化，就先重置线条，然后再添加数据，否则就直接添加
    if(m_plot.size() != newdata[0].length()){
        adjustPlotNums(newdata[0].length());
    }

    QVector<double> xs;
    xs.reserve(newdata.length());
    QVector<double> ys;
    ys.reserve(newdata.length());

    //给出X值
    for(int i = 0;i<newdata.length();++i){
        xs.append(increaseXIndex());
    }

    //组合y值绘制曲线
    for(int i = 0;i<newdata[0].length();++i){ //newdata[0].length()表示通道数量
        ys.clear();
        for(int j = 0;j<newdata.length();j++){
            ys.append(newdata[j][i]);
        }
        m_plot.at(i)->addData(xs,ys);
    }

    //删除超过buffersize的点
    double x = getXIndex();
    if(x > m_buffSize){
        for(int i = 0;i<m_plot.size();i++){
            m_plot.at(i)->data()->removeBefore(x - m_buffSize);
        }
    }

    //移动x轴. x超过默认窗口大小,且使能了自动移动x, 则移动x
    autoXRange();
    //调整y
    autoYRange();
}

void drawPlot::setPlotName(QVector<QString> name)
{
    //数据通道出现变化，就先重置线条，然后再设置名字，否则就直接设置
    m_name = name;
    //更新显示的名字
    for(int i = 0;i<m_plot.size();++i){
        m_plot.at(i)->setName(getName(i));
    }

    // QCPPlottableLegendItem *item;
    // for(int i = 0;i<m_plot.size();i++){
    //     m_plot.at(i)->setName(name.at(i));
    //     item = this->legend->itemWithPlottable(m_plot.at(i));
    //     if(m_plot.at(i)->visible()){
    //         item->setTextColor(m_plot.at(i)->pen().color());
    //     }
    //     else{
    //         item->setTextColor(QColor(0xDDDDDD)); //图例文字颜色变灰，表示隐藏了
    //     }

    // }
}

void drawPlot::setBuffSize(int t)
{
    if(t<=0) t = 300;
    m_buffSize = t;
}

void drawPlot::setWindSize(int t)
{
    if(t<=0) t = 100;
    m_watchSize = t;
    if(m_watchSize > m_buffSize)
        m_watchSize = m_buffSize;
}


void drawPlot::setPlotWidth(int i)
{
    for(int j = 0;j<m_plot.size();j++){
        QPen pen= m_plot.at(j)->pen();
        pen.setWidth(i);
        m_plot.at(j)->setPen(pen);
    }
}

void drawPlot::mousePressEvent(QMouseEvent *event)
{
    buoy->setPixelPos(event->localPos());
    mouseDrag->press(event);

    QCustomPlot::mousePressEvent(event);
}

void drawPlot::mouseMoveEvent(QMouseEvent *event)
{
    buoy->setPixelPos(event->localPos());

    mouseDrag->move(event);

    QCustomPlot::mouseMoveEvent(event);
}

void drawPlot::mouseReleaseEvent(QMouseEvent *event)
{
    buoy->setPixelPos(event->localPos());

    mouseDrag->release(event);
    QCustomPlot::mouseReleaseEvent(event);
}


void drawPlot::wheelEvent(QWheelEvent *event)
{
    m_isRoom = true;
    QCustomPlot::wheelEvent(event);
}



void drawPlot::showAllPlot()
{
    for(int i = 0;i<m_plot.size();i++){
        m_plot.at(i)->setVisible(true);
        QCPPlottableLegendItem *mitem = this->legend->itemWithPlottable(m_plot.at(i));
        mitem->setSelected(false);
        mitem->setTextColor(m_plot.at(i)->pen().color()); //恢复颜色
    }
}

void drawPlot::hideAllPlot()
{
    for(int i = 0;i<m_plot.size();i++){
        m_plot.at(i)->setVisible(false);
        QCPPlottableLegendItem *mitem = this->legend->itemWithPlottable(m_plot.at(i));
        mitem->setSelected(false);
        mitem->setTextColor(QColor(0xDDDDDD)); //恢复颜色
    }
}

void drawPlot::mouseDragStart(Qt::MouseButton but,QPoint point)
{
    Q_UNUSED(point);
    if(but == Qt::RightButton){//进入拖动, 关闭自动X,Y
        m_isDrag = true;
    }else if(but == Qt::LeftButton){
         m_isRoom = true;
    }

}

void drawPlot::mouseDragMove(Qt::MouseButton but,QPoint point)
{
    Q_UNUSED(point);
    //拖拽移动中
    if(but == Qt::RightButton){
    }

}

void drawPlot::mouseDragEnd(Qt::MouseButton but,QPoint point)
{
    Q_UNUSED(point);
    if(but == Qt::RightButton){
    }else if(but == Qt::LeftButton){
        //缩放释放
    }
}

void drawPlot::mouseClick(Qt::MouseButton but, QPoint point)
{
    Q_UNUSED(point);
    if(but == Qt::RightButton){
        //右键单击,将视图还原
        m_isRoom = false;
        m_isDrag = false;
        resetXYRange();

    }
}







MouseDrag::MouseDrag(QObject *parent)
    : QObject(parent)
{

}

MouseDrag::~MouseDrag()
{

}


void MouseDrag::press(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        isPressR = true;
        isDragR = false;
        pressPointR = event->pos();
    }else if(event->button() == Qt::LeftButton){
        isPress = true;
        isDrag = false;
        pressPoint = event->pos();
    }
}

void MouseDrag::move(QMouseEvent *event)
{

    movePointR = event->pos();
    if(isPressR){
        if((pressPointR - movePointR).manhattanLength() > checkDragDirectionPix){
            if(isDragR == false){
                emit startDrag(Qt::RightButton, event->pos());
                isDragR = true;
            }else{
                emit drag(Qt::RightButton,event->pos());
            }
        }
    }

    movePoint = event->pos();
    if(isPress){
        if((pressPoint - movePoint).manhattanLength() > checkDragDirectionPix){
            if(!isDrag){
                emit startDrag(Qt::LeftButton, event->pos());
                isDrag = true;
            }else{
                emit drag(Qt::LeftButton,event->pos());
            }
        }
    }
}

void MouseDrag::release(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        isPressR = false;

        releasePointR = event->pos();
        if(isDragR){
            isDragR = false;
            emit endDrag(Qt::RightButton,event->pos());
        }
        else{
            emit clicked(Qt::RightButton,event->pos());
        }
    }
    else if(event->button() == Qt::LeftButton){
        isPress = false;

        releasePoint = event->pos();
        if(isDrag){
            isDrag = false;
            emit endDrag(Qt::LeftButton,event->pos());
        }
        else{
            emit clicked(Qt::LeftButton,event->pos());
        }
    }
}

