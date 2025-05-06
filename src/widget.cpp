#include "widget.h"
#include "ui_widget.h"
#include <QtMath>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>

/*!
 * \brief Widget::Widget
 * \param resizeEnable
 * \param shadowBorder
 * \param winNativeEvent
 * \param parent
 */
Widget::Widget(bool resizeEnable,
               bool shadowBorder,
               bool winNativeEvent,
               QWidget *parent)
    : QFramelessWidget(parent, resizeEnable, shadowBorder, winNativeEvent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->initForm(); //设置无标题窗口栏
//成员初始化

    //串口相关内容初始化
    serialport = new QSerialPort(this);
    serialInfo = new SerialInfo(this);
    connect(serialInfo, &SerialInfo::portListChanged, this, &Widget::portListChanged);
    connect(serialport,&QSerialPort::readyRead,this,&Widget::onReadyRead);

    //数据解析
    yframe = new YFrame(this);
    connect(yframe,&YFrame::frameReceived,this,&Widget::onFrameReceived);;
    yframe->startAutoParse(5);//5ms解析一次数据


    plotdemo = new PlotDemo(this);
    connect(plotdemo, &PlotDemo::readyRead, yframe, &YFrame::receiveData);


 //读取配置文件
    settings = new QSettings(QCoreApplication::applicationDirPath()+"/config.ini",QSettings::IniFormat, this);

    int buffsize = settings->value("buffsize",30).toInt();
    int watchsize = settings->value("watchsize",10).toInt();
   if(buffsize < watchsize)
        watchsize = buffsize;

    //视窗大小初始化
    ui->plotView->setBuffSize(buffsize);
    ui->plotView->setWindSize(watchsize);
    ui->spinBox_buff->setValue(buffsize);
    ui->spinBox_wind->setValue(watchsize);

    //滑块初始化，
    //滑动条总长度 = maximum() - minimum() + pageStep()
    //滑块大小 = pageStep()
    scrollBar = new MyScorllBar(ui->scrollBar_pos,this);
    scrollBar->setRange(0,buffsize);
    scrollBar->setPageRange(0,watchsize);
    connect(scrollBar,&MyScorllBar::sliderMoved,this,&Widget::slot_scrollBarMove);

    connect(ui->plotView,&drawPlot::xVisibleRangeChanged,this,&Widget::slot_plotviewXRangeChanged);


    //设置波特率
    QString baud = settings->value("baud","115200").toString();
    ui->comboBox_baud->setCurrentText(baud);

    //UI控件初始状态
    ui->checkBox_stop->setChecked(false);
    ui->scrollBar_pos->setEnabled(false);



    //命令发送窗口初始设置
    cmdList = new CmdList(this);
    cmdList->loadCmd(QCoreApplication::applicationDirPath()+"/config.ini");
    QHBoxLayout *layout = new QHBoxLayout(ui->widgetCmd);
    layout->addWidget(cmdList);

    ui->widgetCmd->setLayout(layout);
    connect(cmdList,&CmdList::readySend,this,&Widget::onReadySend);
}

Widget::~Widget()
{
    //主页面数据保存
    if(ui->comboBox_port->currentText().split(':').length() > 1){
        QString portName = ui->comboBox_port->currentText().split(':')[0];
        settings->setValue("port",portName);
    }

    settings->setValue("buffsize",ui->spinBox_buff->value());
    settings->setValue("watchsize",ui->spinBox_wind->value());
    settings->setValue("baud",ui->comboBox_baud->currentText());

    serialport->close();
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    cmdList->keyPressEvent(e);
    QWidget::keyPressEvent(e);
}

void Widget::initForm()
{
    //设置标题栏控件
//    this->setWindowTitle(ui->label_title->text());
    this->framelessHelper()->setTitleBar(ui->widget_title);

//    //关联信号
    connect(framelessHelper(), SIGNAL(maximizedChanged(bool)), this, SLOT(maximizedChanged(bool)));
}

//窗口最大化和normal尺寸变化时出现的信号
void Widget::maximizedChanged(bool max)
{
    if(!max){   //normal size

        ui->pushButton_size->setIcon(QIcon(":/img/size-2.svg"));
    }
    else{
        ui->pushButton_size->setIcon(QIcon(":/img/size-1.svg"));
    }
}

//关闭窗口
void Widget::on_pushButton_close_clicked()
{
    this->close();
}

//最小化窗口
void Widget::on_pushButton_little_clicked()
{
    framelessHelper()->showMinimized();
}

//窗口最大化变换
void Widget::on_pushButton_size_clicked()
{
    framelessHelper()->switchMaximizedNormal();
}


//开启串口
void Widget::on_checkBox_open_clicked(bool checked)
{
    if( checked == true &&ui->comboBox_port->currentIndex()>=0){

        if(ui->comboBox_port->currentText().split(':').length() < 1){
            QMessageBox::warning(this,"提示" ,"串口名称应为 COMx:info, 出现该提示为系统未适配,请联系开发者进行适配.",QMessageBox::Ok);
            ui->checkBox_open->setChecked(false);
            return;
        }
        QString name = ui->comboBox_port->currentText().split(':')[0];
        QString baud = ui->comboBox_baud->currentText();//获取下拉框中设置波特率
        serialport->setPortName(name);//设置串口名字
        serialport->setBaudRate(baud.toInt());//设置串口波特率
        serialport->setDataBits(QSerialPort::Data8);//设置数据位
        serialport->setStopBits(QSerialPort::OneStop);//设置停止位
        serialport->setParity(QSerialPort::NoParity);//设置奇偶校验
        serialport->setFlowControl(QSerialPort::NoFlowControl);//设置流控制
        if(serialport->open(QIODevice::ReadWrite)){ //以可读可写的方式打开串口
            ui->comboBox_baud->setDisabled(true);
            ui->comboBox_port->setDisabled(true);

            //关闭demo
            if(plotdemo->isStart()){
                plotdemo->stop();
            }
        }
        else{// 串口打开失败
            QMessageBox::warning(this,"提示" ,"连接失败\n串口可能被占用",QMessageBox::Ok);
            ui->checkBox_open->setChecked(false);
            ui->comboBox_baud->setDisabled(false);
            ui->comboBox_port->setDisabled(false);
        }
    }
    else if(!checked){// 需要关闭串口
        serialport->clear();
        serialport->close();//关闭串口
        yframe->clear();
        ui->comboBox_baud->setDisabled(false);
        ui->comboBox_port->setDisabled(false);
        qDebug()<<"1";
    }
}


//串口接收函数
void Widget::onReadyRead()
{
    //接收状态下，需要解析数据
    QByteArray data_byte = serialport->readAll();
    yframe->receiveData(data_byte);
}

//暂停接收按钮
void Widget::on_checkBox_stop_clicked(bool checked)
{
    m_stopReceivePlotData = checked;
    ui->scrollBar_pos->setEnabled(checked); //不允许拖动滑块。

    if(!checked){
        ui->plotView->resetXYRange();
    }
}



//按键重置
void Widget::on_pushButton_resetKey_clicked()
{
    cmdList->clearKey();
}

//指令框复位
void Widget::on_pushButton_resetCmd_clicked()
{
    cmdList->clearCmd();
}



//清除数据
void Widget::on_pushButton_clear_clicked()
{
    ui->plotView->clearAllPlot();
}
//数据导出
void Widget::on_pushButton_output_clicked()
{
//    stopFlag = true;
    //outputData output(plot.series);
//    stopFlag = false;
}


//帮助按钮
void Widget::on_pushButton_help_clicked()
{
    const QUrl regUrl(QLatin1String("https://blog.csdn.net/xia3976/article/details/122690888"));
    QDesktopServices::openUrl(regUrl);
}

//是否自适应Y值
void Widget::on_checkBox_auto_clicked(bool checked)
{
    //ui->plotView->enableAutoY(!checked);
}

void Widget::on_pushButton_reset_clicked()
{
    ui->plotView->resetXYRange();
    ui->checkBox_auto->setChecked(false);
}


void Widget::on_pushButton_showall_clicked()
{
    ui->plotView->showAllPlot();
}

void Widget::on_spinBox_buff_editingFinished()
{
    int arg1 = ui->spinBox_buff->value();
    if(arg1<30)
        arg1 = 30;
    if(ui->plotView->getBuffSize() == arg1)
        return;
    ui->spinBox_buff->setValue(arg1);
    ui->plotView->setBuffSize(arg1);

    //滑块范围为[0, buffSize]
    scrollBar->setRange(0,ui->plotView->getBuffSize());
    scrollBar->setPageRange(0,ui->plotView->getWindSize());
}

void Widget::on_spinBox_wind_editingFinished()
{
    int arg1 = ui->spinBox_wind->value();
    if(arg1<10)
        arg1 = 10;

    if(ui->plotView->getWindSize() == arg1)
        return;
    ui->spinBox_wind->setValue(arg1);
    ui->plotView->setWindSize(arg1);

    scrollBar->setRange(0,ui->plotView->getBuffSize());
    scrollBar->setPageRange(0,ui->plotView->getWindSize());

}



//滑块跟随视窗运动
void Widget::slot_plotviewXRangeChanged(double low,double up)
{
    scrollBar->setPageRange(low,up);
}


//视窗跟随滑块运动
void Widget::slot_scrollBarMove(int min,int max)
{
    //如果处于暂停状态,滑块可以拖动视窗, 如果处于接收数据状态, 滑块禁止滑动
    qDebug()<<"min = "<<min<<" max = "<<max;
    qDebug()<<"plotView->getHeadXIndex() = "<<ui->plotView->getHeadXIndex();
    ui->plotView->setXRange(min+ui->plotView->getHeadXIndex(),max+ui->plotView->getHeadXIndex());
}

//隐藏全部
void Widget::on_pushButton_hideall_clicked()
{
    ui->plotView->hideAllPlot();
}

//更新串口列表
void Widget::portListChanged(const QList<QSerialPortInfo> &portlist)
{
    bool isInit = false;

    //一般为初始状态
    if(ui->comboBox_port->count() == 0 && !ui->checkBox_open->checkState()){
        isInit = true;
    }

    //更新列表
    ui->comboBox_port->clear(); //清除之前的显示
    for(int i=0;i<portlist.size();i++){//添加更新后的设备信息
        ui->comboBox_port->addItem(portlist[i].portName()
                                   +":"+portlist[i].description());
    }

    QString nowname{};
    if(isInit){
        nowname = settings->value("port","").toString();
    }else if(ui->checkBox_open->checkState()){
        nowname = serialport->portName();  // 长这样 "COM3"
    }

    if(!nowname.isEmpty()){
        QString boxName;
        bool ok = false;
        for(int i = 0;i<portlist.size();i++){
            boxName = portlist[i].portName();
            qDebug()<<boxName << nowname;
            if(boxName == nowname){
                ui->comboBox_port->setCurrentIndex(i);
                ok = true;
                break;
            }
        }
        if(!ok && ui->checkBox_open->checkState()){
            ui->checkBox_open->setChecked(false); //不会触发槽函数
            on_checkBox_open_clicked(false);//手动调用槽函数
            QMessageBox::warning(this,"提示","设备已拔出",QMessageBox::Ok);
        }
    }
}

void Widget::onFrameReceived(QVector<YFrame_t> frame)
{
    QVector<QVector<double>> newData;
    QVector<QString> name;
    QVector<float> data;
    QVector<double> ddata;

    QDateTime time;
    QString str = "";
    for(int i = 0;i < frame.length();i++){
        auto m = frame.at(i);
        switch(m.id){
        case YPLOT_ID_PLOTNAME: //名称
            name = YFrame::byteArrayToQString(m.data);
            ui->plotView->setPlotName(name);
            break;
        case YPLOT_ID_PLOT: //波形
            if(m_stopReceivePlotData)
                break;
            data.clear();
            ddata.clear();

            data = YFrame::byteArrayToFloat(m.data);

            for (int i = 0; i < data.size(); ++i) {
                ddata.append(static_cast<double>(data.at(i)));
            }

            newData.append(ddata);
            break;
        case YPLOT_ID_INFO: //发送指令
            //time: [Info] data
            time = QDateTime::currentDateTime();
            str = time.toString("hh:mm:ss") + ":[Info--] " + m.data;
            break;
        case YPLOT_ID_DEBUG: //debug信息
            time = QDateTime::currentDateTime();
            //time: [Debug] data
            str = time.toString("hh:mm:ss") + ":[Debug] " + m.data;
            break;
        case YPLOT_ID_WARNING: //warning信息
            time = QDateTime::currentDateTime();
            //time: [Warning] data
            str = time.toString("hh:mm:ss") + ":[Warning] " + m.data;
            break;
        }
    }
    //限制最大行数
    if(str != ""){
        ui->plainTextEditRx->appendPlainText(str);
        if(ui->plainTextEditRx->document()->lineCount() > 30000){
            ui->plainTextEditRx->clear();
        }
    }

    if(newData.length() > 0){
        ui->plotView->addPoint(newData); //添加新的波形
    }
}

//点击Demo按钮
void Widget::on_pushButton_demo_clicked()
{
    if(plotdemo->isStart()){
        plotdemo->stop();
    }else{
        plotdemo->start(3);
    }
}

void Widget::onReadySend(QString cmd)
{
    QByteArray pack =  yframe->packData(YPLOT_ID_SENDCMD,cmd);
    serialport->write(pack);
    qDebug()<<"send cmd = "<<cmd;
}

