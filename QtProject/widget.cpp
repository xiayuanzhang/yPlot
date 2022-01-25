#include "widget.h"
#include "ui_widget.h"
#include "outputdata.h"

#include "callout.h"
#include <QtMath>


#include <QPushButton>
#include <QComboBox>
#pragma execution_character_set("utf-8")

Widget::Widget(bool resizeEnable,
               bool shadowBorder,
               bool winNativeEvent,
               QWidget *parent)
    : QFramelessWidget(parent, resizeEnable, shadowBorder, winNativeEvent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    this->initForm();

    //串口相关内容初始化
    findPortTimer = new QTimer(this);
    findPortTimer->start(100);//周期100ms启动定时器
    connect(this->findPortTimer,SIGNAL(timeout()),
            this,SLOT(findPortTimer_timeout()));//连接定时器溢出信号和槽函数
    connect(&this->serialport,SIGNAL(readyRead()),
            this,SLOT(serialport_readyread()));

    createCmd(); //创建命令输入窗口

    //获取配置数据
        //打开配置文件
    configFile.open(QCoreApplication::applicationDirPath());//获取程序当前路径
         //通道数
    int channels = configFile.readInt("channel");
    if(channels < 1)
        channels = 1;
        //按键指令
    memcpy(keyCmd,configFile.readString("keyCmd").toUtf8().data()
           ,sizeof(char)*50);
    for(uint i = 0;i<sizeof(keyCmd);i++)
    {
        if(!(keyCmd[i] >= 65 && keyCmd[i] <= 90))
            keyCmd[i] = '*';
    }
        //数据类型
    QString type = configFile.readString("dataType");
    //qDebug()<<type;
    if(type != "uint8" &&
            type != "uint16" &&
            type != "uint32" &&
            type != "int8" &&
            type != "int16" &&
            type != "int32" &&
            type != "float" &&
            type != "double"
            )
        type = "float";

     //设置页面数据读取
    int watchsize = configFile.readInt("watchSize");
    if(watchsize < 10) watchsize = 10;
    if(watchsize > 10000) watchsize = 10000;

    int buffsize = configFile.readInt("buffSize");
    if(buffsize < 1000) buffsize = 1000;
    if(buffsize > 10000) buffsize = 10000;

    //设置页面初始化
    setupPage = new setup(this);
    connect(setupPage,&setup::finished,
                    this,&Widget::setup_finish);
    setupPage->setBuffSize(buffsize);
    setupPage->setWatchSize(watchsize);

    //帮助界面
    helpPage = new helpDialog(this);

    //主界面控数据填充
    ui->spinBox_channel->setValue(channels);
    ui->comboBox_datatype->setCurrentText(type);
    ui->comboBox_baud->setCurrentText(configFile.readString("baud"));

    for (int i = 0;i < 50;i++) {
        QString name = "cmdli"+QString::number(i);
        QLineEdit *cmdli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        cmdli->setText(configFile.readString(name));

        name = "keyli"+QString::number(i);
        QLineEdit *keyli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        keyli->setText(QString(keyCmd[i]));

    }

    //数据解析类初始化
    analysis.setDataType(type);
    analysis.setChannelNum(channels);

    //波形显示类初始化
    plot.setChannels(channels);
    plot.setBuffSize(buffsize);
    plot.setWatchSize(watchsize);
    connect(&analysis,&dataAnalysis::haveNewData,
                    this,&Widget::haveNewPoint_drawPlot);
    connect(&analysis,&dataAnalysis::haveNewName,
                    this,&Widget::haveNewName_drawPlot);

    //chartview初始化
    ui->chartview->setChart(plot.chart); //加载数据表
    ui->chartview->setRenderHint(QPainter::Antialiasing);//设置抗锯齿
    ui->chartview->setRubberBand(QChartView::RectangleRubberBand); //橡皮筋放大

    //鼠标操作chartview的视窗
    connect(ui->chartview,&myChartView::mouseClicked,
                    this,&Widget::chartview_mouseClicked);
    connect(ui->chartview,&myChartView::mouseDoubleClicked,
                    this,&Widget::chartview_mouseDoubleClicked);
    connect(ui->chartview,&myChartView::mouseMove,
                    this,&Widget::chartview_mouseMove);
    connect(ui->chartview,&myChartView::mouseWheel,
                    this,&Widget::chartview_mouseWheel);
    connect(ui->chartview,&myChartView::mouseRelease,
                    this,&Widget::chartview_mouseRelease);

    tooltip = new Callout(plot.chart);

}

Widget::~Widget()
{
    //主页面数据保存
    configFile.write("baud",ui->comboBox_baud->currentText());
    configFile.write("channel",ui->spinBox_channel->value());
    configFile.write("dataType",ui->comboBox_datatype->currentText());

    for (int i = 0;i < 50;i++) {
        QString name = "keyli"+QString::number(i);
        QLineEdit *keyli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        keyCmd[i] = keyli->text().toUtf8().data()[0];
    }

    configFile.write("keyCmd",QString(keyCmd));

    for (int i = 0;i < 50;i++) {
        QString name = "cmdli"+QString::number(i);
        QLineEdit *cmdli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        configFile.write(name,cmdli->text());
    }

    //设置页面数据保存
    configFile.write("watchSize",setupPage->getWatchSize());
    configFile.write("buffSize",setupPage->getBuffSize());

    configFile.close();
    serialport.close();
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() >= 0x41 && e->key() <= 0x5a){ //0x41 = A  0x5a = Z 不区分大小写
        for(int i = 0;i<50;i++){
            int cmdbuff = keyCmd[i];
            if(cmdbuff >= 65 && cmdbuff <= 90){ //符合大写字母区间才进行判断
                if(e->key() == cmdbuff){  //找一下有没有响应的指令，有的话就发送
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


//创建命令的函数
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
                    serialport.write(cmdli->text().toLocal8Bit());
               });

       connect(keyli,&QLineEdit::editingFinished, //完成可输入按键值
              this,&Widget::lineEdit_finish);
       connect(cmdli,&QLineEdit::returnPressed, //按下了回车键
                     this,&Widget::lineEdit_return);
    }
    //将布局添加到窗口中
    ui->scrollArea->widget()->setLayout(pLayout);//把布局放置到QScrollArea的内部QWidget中
}

//回车或将光标点击到非该lineedit区域时触发
void Widget::lineEdit_finish()
{
    QLineEdit *keyli = qobject_cast<QLineEdit *>(sender());
    QString num = keyli->objectName(); //对象名格式为 keyli0~keyli50
    num.remove(0,5);//删除keyli
    int n = num.toInt();//把剩下的字符转换为int型,获得对象名中的数字

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
              if(cmd == keyCmd[j])
              {
                  errFlag = true;
              }
          }
      }


      //输入错误、自动重置为""
      if(errFlag == true){
          cmd = keyCmd[n]; //将字符保存到对应的按键中
          keyli->setText(QString(cmd)); //重新设置键值，避免出现小写
      }
       //更新值
      else {
          keyli->setText(QString(cmd)); //重新设置键值，避免出现小写
          keyCmd[n] = cmd; //将字符保存到对应的按键中
      }
}

//只有回车时会执行该信号
void Widget::lineEdit_return()
{
     QLineEdit *cmdli = qobject_cast<QLineEdit *>(sender());
     QString name = cmdli->objectName(); //对象名格式为 cmdli0~cmdli50
     name.replace(0,5,"cmdbt");//将cmdli替换为cmdbt，也就是按钮的对象名
     QPushButton *button = ui->scrollArea->widget()->findChild<QPushButton*>(name); //找到对应的按钮
     emit button->click(); //激发对应按钮的点击信号从而发送数据
}




// 自动搜索并添加设备的定时器槽函数
void Widget::findPortTimer_timeout()
{
    static int listsize = portlist.size();
    portlist = QSerialPortInfo::availablePorts();
    if(listsize != portlist.size()){//判断是否改变了设备数量
        ui->comboBox_port->clear(); //清除之前的显示
        for(int i=0;i<portlist.size();i++){//添加更新后的设备信息
            ui->comboBox_port->addItem(portlist[i].portName()
                            +":"+portlist[i].description());
        }
    }
    listsize = portlist.size(); // 记录设备数量，用以判断设备数量是否改变
}


void Widget::on_checkBox_open_clicked(bool checked)
{
    if( checked == true &&ui->comboBox_port->currentIndex()>=0){
        QString name =
           portlist[ui->comboBox_port->currentIndex()].portName();//获取选中的串口的名字
        QString baud = ui->comboBox_baud->currentText();//获取下拉框中设置波特率
        serialport.setPortName(name);//设置串口名字
        serialport.setBaudRate(baud.toInt());//设置串口波特率
        serialport.setDataBits(QSerialPort::Data8);//设置数据位
        serialport.setStopBits(QSerialPort::OneStop);//设置停止位
        serialport.setParity(QSerialPort::NoParity);//设置奇偶校验
        serialport.setFlowControl(QSerialPort::NoFlowControl);//设置流控制
        if(serialport.open(QIODevice::ReadWrite)){ //以可读可写的方式打开串口
            ui->comboBox_baud->setDisabled(true);
            ui->comboBox_port->setDisabled(true);
        }
        else{// 串口打开失败
            QMessageBox::warning(this,"提示" ,"连接失败\n串口可能被占用",QMessageBox::Ok);
            ui->checkBox_open->setChecked(false);
            ui->comboBox_baud->setDisabled(false);
            ui->comboBox_port->setDisabled(false);
        }
    }else if(ui->comboBox_port->currentIndex()<0){//没有搜索到串口
        ui->checkBox_open->setChecked(false);
        QMessageBox::warning(this,"提示","设备未连接",QMessageBox::Ok);
        ui->comboBox_baud->setDisabled(false);
        ui->comboBox_port->setDisabled(false);
    }
    else{// 需要关闭串口
        serialport.clear();
        analysis.clearAnalysisBuff();
        serialport.close();//关闭串口
        ui->comboBox_baud->setDisabled(false);
        ui->comboBox_port->setDisabled(false);
    }
}



void Widget::serialport_readyread()
{
    if(stopFlag){//处于暂停状态中,直接读取数据不处理
        serialport.clear();
        analysis.clearAnalysisBuff();
        return;
    }
    //接收状态下，需要解析数据
    QByteArray data_byte = serialport.readAll();
    analysis.inputDataStream(data_byte); //输入到数据解析类中去

   // QString data_str = QString::fromLocal8Bit(data_byte);
}

//暂停接收按钮
void Widget::on_checkBox_stop_clicked(bool checked)
{
    stopFlag = checked; //true 为暂停状态
}

void Widget::on_pushButton_help_clicked()
{
    //还是用离线帮助吧，等会创建一个窗口，显示帮助内容
    helpPage->show();
}

void Widget::on_spinBox_channel_valueChanged(int arg1)
{
    if(arg1 < 1)
    {
        arg1 = 1;
        ui->spinBox_channel->setValue(1);
    }
    analysis.setChannelNum(arg1);
    plot.setChannels(arg1);
}

void Widget::on_comboBox_datatype_currentTextChanged(const QString &arg1)
{
    analysis.setDataType(arg1);
}





//按键复位
void Widget::on_pushButton_resetKey_clicked()
{
    memset(keyCmd,0,sizeof (keyCmd));
    for (int i = 0;i < 50;i++) {
        QString name = "keyli"+QString::number(i);
        QLineEdit *keyli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        keyli->setText("*");
    }
}

//串口发送数据复位
void Widget::on_pushButton_resetCmd_clicked()
{
    for (int i = 0;i < 50;i++) {
        QString name = "cmdli"+QString::number(i);
        QLineEdit *cmdli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        cmdli->setText("");
    }
}


void Widget::haveNewPoint_drawPlot(QVector<QVector<double> > newdata)
{
    plot.addPoint(newdata);

    if(plotShowDataFlag == false)
        tooltip->hideChartPos();
    else {
        QRect rect = ui->widget_title->geometry();
        QRect crect = ui->chartview->geometry();
        crect.setY(crect.y()+rect.height());
        if (crect.contains(this->mapFromGlobal(QCursor::pos()))) //判断鼠标在不在chartview中
        {
            QPointF position =  ui->chartview->mapFromGlobal(QCursor::pos());
            QVector<double> rect;
            double min,max;
            plot.getMinMax_x(&min,&max); //返回的是chart中的value

            rect.append(min);
            rect.append(max);
            plot.getMinMax_y(&min,&max);
            rect.append(min);
            rect.append(max);

            tooltip->showChartPos(position,plot.series,rect);
        }
        else {
            tooltip->hideChartPos();
        }
    }


}

void Widget::haveNewName_drawPlot(QVector<QString> name)
{
       plot.setChannelsName(name);
}

void Widget::chartview_mouseClicked(int key, QPointF clickPos)
{
    Q_UNUSED(clickPos) //表示 未使用
    if(key == RIGHT){  //右键单击复位示波器窗口
        plot.viewZoomReset();
    }

}

void Widget::chartview_mouseDoubleClicked(int key, QPointF clickPos)
{
    Q_UNUSED(clickPos)
    if(key == RIGHT){
        plot.viewZoomReset();
        plot.showAllPlot();
    }
}

void Widget::chartview_mouseMove(int key, QPointF nowPos)
{
    static QPointF lastPos(0,0);

    if(key == RIGHT){
        double size_view = ui->chartview->geometry().width();
        double min,max;
        plot.getMinMax_x(&min,&max);
        double size_axis = max - min;
        double e = size_axis / size_view;
        double d = e * ( lastPos.x()-nowPos.x() );

        plot.moveX(d);

    }

    lastPos = nowPos;

    if(key == NOONE){   // 没有按键按下
        lastPos = nowPos;
        plotShowDataFlag = true;  //显示图元
    }
    else {
        plotShowDataFlag = false; //不显示图元
        tooltip->hideChartPos();
    }

    if(stopFlag == true && serialport.isOpen() == false){
        plotShowDataFlag = false;
        QRect rect = ui->widget_title->geometry();
        QRect crect = ui->chartview->geometry();
        crect.setY(crect.y()+rect.height());
        if (crect.contains(this->mapFromGlobal(QCursor::pos()))) //判断鼠标在不在chartview中
        {
            QPointF position =  ui->chartview->mapFromGlobal(QCursor::pos());
            QVector<double> rect;
            double min,max;
            plot.getMinMax_x(&min,&max); //返回的是chart中的value

            rect.append(min);
            rect.append(max);
            plot.getMinMax_y(&min,&max);
            rect.append(min);
            rect.append(max);

            tooltip->showChartPos(position,plot.series,rect);
        }
    }

}

void Widget::chartview_mouseWheel(int value)
{
    plot.moveY(value/100);
}

void Widget::chartview_mouseRelease(int key, QPointF releasekPos)
{
     Q_UNUSED(releasekPos)
    if (key == LEFT) {  //左键释放
        if(plotShowDataFlag == false){//释放时就可以显示图元了
            plotShowDataFlag = true;
        }

    }
}

void Widget::setup_finish(int a)
{
    Q_UNUSED(a)
    int buffsize;
    int watchsize;
    buffsize = setupPage->getBuffSize();
    watchsize = setupPage->getWatchSize();
    plot.setBuffSize(buffsize);
    plot.setWatchSize(watchsize);
}

void Widget::on_pushButton_setup_clicked()
{
    setupPage->show();
}
//清除数据
void Widget::on_pushButton_clear_clicked()
{
    plot.clearPlot();
}
//数据导出
void Widget::on_pushButton_output_clicked()
{
    stopFlag = true;
    outputData output(plot.series);
    stopFlag = false;
}



