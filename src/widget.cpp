#include "widget.h"
#include "ui_widget.h"
#include <QtMath>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>


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
    connect(yframe,YFrame::frameReceived,this,onFrameReceived);
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
    scrollBar->setValueRange(0,watchsize);
    connect(scrollBar,&MyScorllBar::valueChanged,this,&Widget::slot_scrollBarvalueChanged);


//    ui->scrollBar_pos->setEnabled(false); //不允许拖动滑块。
    connect(ui->plotView,SIGNAL(xVisibleRangeChanged(double,double)),
            this,SLOT(slot_plotviewXRangeChanged(double,double)));//连接定时器溢出信号和槽函数
    connect(ui->plotView,SIGNAL(stopStatusChanged(bool)),
            this,SLOT(onStopStatusChanged(bool)));//连接定时器溢出信号和槽函数

    //创建命令输入窗口
    createCmd();
    settings->beginGroup("key");
    for(int i = 0;i<50;i++){
        cmdKey[i] = settings->value(QString::number(i),'*').toChar();
        qDebug()<<"key = "<<cmdKey[i];
        QString name = "keyli"+QString::number(i);
        name = "keyli"+QString::number(i);
        QLineEdit *keyli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        keyli->setText(QString(cmdKey[i]));
    }
    settings->endGroup();
    //控制命令填充填充
    settings->beginGroup("cmd");
    for (int i = 0;i < 50;i++) {
        QString name = "cmdli"+QString::number(i);
        QLineEdit *cmdli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        cmdli->setText(settings->value(QString::number(i),"").toString());
    }
    settings->endGroup();

    //设置波特率
    QString baud = settings->value("baud","115200").toString();
    ui->comboBox_baud->setCurrentText(baud);
}

Widget::~Widget()
{
    //主页面数据保存
    settings->beginGroup("key");
    for(int i = 0;i<50;i++){
        settings->setValue(QString::number(i),cmdKey[i]);
    }
    settings->endGroup();

    settings->beginGroup("cmd");
    for(int i = 0;i<50;i++){
        QString name = "cmdli"+QString::number(i);
        QLineEdit *cmdli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        settings->setValue(QString::number(i),cmdli->text());
    }
    settings->endGroup();

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
    if(e->key() >= 0x41 && e->key() <= 0x5a){ //0x41 = A  0x5a = Z 不区分大小写
        for(int i = 0;i<50;i++){
            if(cmdKey[i] >= 65 && cmdKey[i] <= 90){ //符合大写字母区间才进行判断
                if(e->key() == cmdKey[i]){  //找一下有没有响应的指令，有的话就发送
                    QString name = "cmdbt"+QString::number(i);
                    QPushButton *button = ui->scrollArea->widget()->findChild<QPushButton*>(name); //找到对应的按钮
                    emit button->click(); //激发对应按钮的点击信号从而发送数据
                    break;
                }
            }
        }
    }
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


//创建命令框的函数
void Widget::createCmd()
{
    QGridLayout *pLayout = new QGridLayout();//网格布局
    for(int i = 0; i < 50; i++){
       //创建对象
       QLineEdit *keyli = new QLineEdit("", this);
       keyli->setStyleSheet("background-color:#DEF1FF;\
                             max-height:30px;\
                             max-width:25px;\
                             min-height:30px;\
                             min-width:25px;\
                             border-radius:5px;");  //设置样式
       keyli->setAlignment(Qt::AlignHCenter);

       QLineEdit *cmdli = new QLineEdit(QString(""), this);
       cmdli->setStyleSheet("background-color:#EBEBED;\
                            max-height:30px;\
                            min-height:30px;\
                             border-radius:5px;");  //设置样式

       QPushButton *cmdbt = new QPushButton(this);
       cmdbt->setStyleSheet("background-color:#DEF1FF;\
                             max-height:30px;\
                             max-width:60px;\
                             min-height:30px;\
                             min-width:60px;\
                             border-radius:5px;");  //设置样式
       cmdbt->setIconSize(QSize(25,25));
       cmdbt->setIcon(QIcon(":/img/send.svg"));
       cmdbt->setCursor(Qt::PointingHandCursor);

       //指定对象名
       keyli->setObjectName(QString("keyli%1").arg(i));
       cmdli->setObjectName(QString("cmdli%1").arg(i));
       cmdbt->setObjectName(QString("cmdbt%1").arg(i));


       //添加到布局中
       //pLe->setMinimumWidth(500);//可以注释掉该行，观察效果
       pLayout->setColumnMinimumWidth(3,100);
       pLayout->addWidget(keyli, i/2, (i%2)*3+1);//把输入框添加到栅格布局的第i行第0/3列
       pLayout->addWidget(cmdli, i/2, (i%2)*3+2);//把按钮添加到栅格布局的第i行第1/4列
       pLayout->addWidget(cmdbt, i/2, (i%2)*3+3);//把输入框添加到栅格布局的第i行第2/5列


       connect(cmdbt,&QPushButton::clicked,  //点击按钮发送数据
               [=]()
               {
                    //qDebug()<<cmdli->text();
                    serialport->write(cmdli->text().toLocal8Bit());
               });

       connect(keyli,&QLineEdit::editingFinished, //完成可输入按键值
              this,&Widget::lineEdit_finish);
       connect(cmdli,&QLineEdit::returnPressed, //按下了回车键
                     this,&Widget::lineEdit_return);
    }
    //将布局添加到窗口中
    ui->scrollArea->widget()->setLayout(pLayout);//把布局放置到QScrollArea的内部QWidget中
}

//命令输入完成 回车或将光标点击到非该lineedit区域时触发
void Widget::lineEdit_finish()
{
    QLineEdit *keyli = qobject_cast<QLineEdit *>(sender());
    QString num = keyli->objectName(); //对象名格式为 keyli0~keyli50
    num.remove(0,5);//删除keyli,得到序号
    int n = num.toInt();//把剩下的字符转换为int型,获得对象名中的数字
    cmdKey[n] = '*'; //复位为*

      bool errFlag = false;
      char cmd = keyli->text().toUtf8().data()[0];
      if(cmd >= 97)  //如果是是小写区间的就减去32，转换为大写字母
        cmd -= 32;

      //判断是否为字符 A-Z,不区分大小写 大写 65-90
      if(errFlag == true
              ||!(cmd >= 65&&cmd <= 90)){
          errFlag = true;
      }
      //判断是否重复
      if(errFlag == false){
          for(int j = 0;j<50;j++){
              if(cmd == cmdKey[j])
              {
                  errFlag = true;
              }
          }
      }


      //输入错误、自动重置为""
      if(errFlag == true){
          keyli->setText(QString('*')); //重新设置键值，避免出现小写
      }
       //更新值
      else {
          keyli->setText(QString(cmd)); //重新设置键值，避免出现小写
          cmdKey[n] = cmd; //将字符保存到对应的按键中
      }
}

//命令输入完成 只有回车时会执行该信号
void Widget::lineEdit_return()
{
     QLineEdit *cmdli = qobject_cast<QLineEdit *>(sender());
     QString name = cmdli->objectName(); //对象名格式为 cmdli0~cmdli50
     name.replace(0,5,"cmdbt");//将cmdli替换为cmdbt，也就是按钮的对象名
     QPushButton *button = ui->scrollArea->widget()->findChild<QPushButton*>(name); //找到对应的按钮
     emit button->click(); //激发对应按钮的点击信号从而发送数据
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
    //ui->plotView->setStopShow(checked); //true 为暂停状态
}

void Widget::onStopStatusChanged(bool stop)
{
    ui->checkBox_stop->setChecked(stop);
}



//按键快捷键复位
void Widget::on_pushButton_resetKey_clicked()
{
    memset(cmdKey,0,sizeof (cmdKey));
    for (int i = 0;i < 50;i++) {
        QString name = "keyli"+QString::number(i);
        QLineEdit *keyli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        keyli->setText("*");
    }
}

//指令框复位
void Widget::on_pushButton_resetCmd_clicked()
{
    for (int i = 0;i < 50;i++) {
        QString name = "cmdli"+QString::number(i);
        QLineEdit *cmdli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        cmdli->setText("");
    }
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
    scrollBar->setValueRange(0,ui->plotView->getWindSize());
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
    scrollBar->setValueRange(0,ui->plotView->getWindSize());

}



//滑块跟随视窗运动
void Widget::slot_plotviewXRangeChanged(double low,double up)
{
    //阻止发出信号
    scrollBar->setValueRange(low,up);
}


//视窗跟随滑块运动
void Widget::slot_scrollBarvalueChanged(int value)
{
    qDebug()<<"the scollbar valueChanged";
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
    for(int i = 0;i < frame.length();i++){
        auto m = frame.at(i);
        switch(m.id){
        case ID_NAME: //名称
            name = YFrame::byteArrayToQString(m.data);
            ui->plotView->setPlotName(name);
            break;
        case ID_WAVE: //波形
            data.clear();
            ddata.clear();

            data = YFrame::byteArrayToFloat(m.data);

            for (int i = 0; i < data.size(); ++i) {
                ddata.append(static_cast<double>(data.at(i)));
            }

            newData.append(ddata);
            break;
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

