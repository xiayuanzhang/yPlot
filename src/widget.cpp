#include "widget.h"
#include "ui_widget.h"
#include "outputdata.h"

#include <QtMath>

#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QMessageBox>
#pragma execution_character_set("utf-8")

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
    findPortTimer = new QTimer(this);
    serialport = new QSerialPort(this);
    analysis = new dataAnalysis();

    //串口相关内容初始化    
    findPortTimer->start(100);//周期100ms启动定时器
    connect(this->findPortTimer,SIGNAL(timeout()),
            this,SLOT(findPortTimer_timeout()));//连接定时器溢出信号和槽函数
    connect(serialport,SIGNAL(readyRead()),
            this,SLOT(serialport_readyread()));

    //数据更新信号连接
    connect(analysis,SIGNAL(haveNewData(QVector<double>)),
            this,SLOT(haveNewPoint_drawPlot(QVector<double>)));
    connect(analysis,SIGNAL(haveNewName(QVector<QString>)),
            this,SLOT(haveNewName_drawPlot(QVector<QString>)));

    //打开配置文件
    configFile.open(QCoreApplication::applicationDirPath());//获取程序当前路径

    //设置按键指令
    memcpy(keyCmd,configFile.readString("keyCmd").toUtf8().data()
           ,sizeof(char)*50);
    for(uint i = 0;i<sizeof(keyCmd);i++)
    {
        if(!(keyCmd[i] >= 65 && keyCmd[i] <= 90))
            keyCmd[i] = '*';
    }

     //设置页面的 数据读取
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

    //创建命令输入窗口
    createCmd();
    //控制命令填充填充
    for (int i = 0;i < 50;i++) {
        QString name = "cmdli"+QString::number(i);
        QLineEdit *cmdli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        cmdli->setText(configFile.readString(name));

        name = "keyli"+QString::number(i);
        QLineEdit *keyli = ui->scrollArea->widget()->findChild<QLineEdit*>(name);
        keyli->setText(QString(keyCmd[i]));
    }

    //设置波特率
    QString baud = configFile.readString("baud");
    if(baud == "")  //软件第一次运行会没有初始值
        baud = "115200";
    ui->comboBox_baud->setCurrentText(baud);
}

Widget::~Widget()
{
    //主页面数据保存
    configFile.write("baud",ui->comboBox_baud->currentText());

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
    serialport->close();
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
    num.remove(0,5);//删除keyli
    int n = num.toInt();//把剩下的字符转换为int型,获得对象名中的数字
    keyCmd[n] = '*';

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
          keyli->setText(QString('*')); //重新设置键值，避免出现小写
      }
       //更新值
      else {
          keyli->setText(QString(cmd)); //重新设置键值，避免出现小写
          keyCmd[n] = cmd; //将字符保存到对应的按键中
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

//开启串口
void Widget::on_checkBox_open_clicked(bool checked)
{
    if( checked == true &&ui->comboBox_port->currentIndex()>=0){
        QString name =
           portlist[ui->comboBox_port->currentIndex()].portName();//获取选中的串口的名字
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
        serialport->clear();
        analysis->clearAnalysisBuff();
        serialport->close();//关闭串口
        ui->comboBox_baud->setDisabled(false);
        ui->comboBox_port->setDisabled(false);
    }
}


//串口接收函数
void Widget::serialport_readyread()
{
    if(stopFlag){//处于暂停状态中,直接读取数据不处理
        serialport->clear();
        analysis->clearAnalysisBuff();
        return;
    }
    //接收状态下，需要解析数据
    QByteArray data_byte = serialport->readAll();
    analysis->inputDataStream(data_byte); //输入到数据解析类中去

   // QString data_str = QString::fromLocal8Bit(data_byte);
}

//暂停接收按钮
void Widget::on_checkBox_stop_clicked(bool checked)
{
    stopFlag = checked; //true 为暂停状态
}



//按键快捷键复位
void Widget::on_pushButton_resetKey_clicked()
{
    memset(keyCmd,0,sizeof (keyCmd));
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


//有新的数据出现，需要绘制
void Widget::haveNewPoint_drawPlot(QVector<double>  newdata)
{

    //qDebug()<<newdata;
    ui->plotView->addPoint(newdata); //添加新的波形
}

//数据的名称出现了变化
void Widget::haveNewName_drawPlot(QVector<QString> name)
{
    ui->plotView->setPlotName(name);
    qDebug()<<name;
      //plot.setChannelsName(name);
}


//设置完成信号
void Widget::setup_finish(int a)
{
    Q_UNUSED(a)
    int buffsize;
    int watchsize;
    buffsize = setupPage->getBuffSize();
    watchsize = setupPage->getWatchSize();

}


//显示设置页面
void Widget::on_pushButton_setup_clicked()
{
    setupPage->show();
}

//清除数据
void Widget::on_pushButton_clear_clicked()
{

}
//数据导出
void Widget::on_pushButton_output_clicked()
{
    stopFlag = true;
    //outputData output(plot.series);
    stopFlag = false;
}


//帮助按钮
void Widget::on_pushButton_help_clicked()
{

}
