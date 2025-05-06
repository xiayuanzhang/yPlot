#include "cmdlist.h"
#include "ui_cmdlist.h"
#include <QFileInfo>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QDebug>
#include <QKeyEvent>
CmdListWidget::CmdListWidget(QWidget *parent, QString key, QString cmd)
{
    keyEdit = new QLineEdit(parent);
    cmdEdit = new QLineEdit(parent);
    btn = new QPushButton(parent);

    keyEdit->setText(key);
    cmdEdit->setText(cmd);
    btn->setText("");

    QFont font = keyEdit->font();
    QFontMetrics fm(font);
    QRect rect = fm.boundingRect("AB");
    qDebug() << rect.width();

    //keyEdit->setFixedWidth(rect.width());
    keyEdit->setAlignment(Qt::AlignCenter);
    keyEdit->setFixedWidth(20);
    btn->setFixedWidth(50);
    btn->setIconSize(QSize(25,25));
    btn->setIcon(QIcon(":/img/send.svg"));

   btn->setStyleSheet("background-color:#DEF1FF;\
                         max-height:30px;\
                         max-width:60px;\
                         min-height:30px;\
                         min-width:60px;\
                         border-radius:5px;");  //设置样式

       // keyli->setStyleSheet("background-color:#DEF1FF;\
       //                       max-height:30px;\
       //                       max-width:25px;\
       //                       min-height:30px;\
       //                       min-width:25px;\
       //                       border-radius:5px;");  //设置样式
       // cmdli->setStyleSheet("background-color:#EBEBED;\
       //                      max-height:30px;\
       //                      min-height:30px;\
       //                       border-radius:5px;");  //设置样式




    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(keyEdit);
    layout->addWidget(cmdEdit);
    layout->addWidget(btn);
    // layout->setStretchFactor(keyEdit,0);
    // layout->setStretchFactor(cmdEdit,1);
    // layout->setStretchFactor(btn,0);

    setLayout(layout);

    connect(btn,&QPushButton::clicked,this,&CmdListWidget::btnClicked);
    connect(cmdEdit,&QLineEdit::returnPressed,this,&CmdListWidget::cmdEditFinish);
}

CmdListWidget::~CmdListWidget()
{

}

void CmdListWidget::cmdEditFinish()
{
    if(cmdEdit->text().isEmpty()){
        return;
    }
    emit readySend(cmdEdit->text());
}

void CmdListWidget::btnClicked(bool checked)
{
    Q_UNUSED(checked);
    if(cmdEdit->text().isEmpty()){
        return;
    }
    emit readySend(cmdEdit->text());
}



CmdList::CmdList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CmdList)
{
    ui->setupUi(this);
}

void CmdList::loadCmd(QString settingFile)
{
    QFileInfo file(settingFile);
    if(file.isFile() == false){
        QMessageBox::warning(this, "错误", "配置文件不存在");
        return;
    }
    settings = new QSettings(settingFile, QSettings::IniFormat,this);
    settings->setIniCodec("UTF-8");
    if(settings->status() != QSettings::NoError){
        QMessageBox::warning(this, "错误", "配置文件打开失败");
        return;
    }

    for(int i =0;i < 50; ++i){
        QString key = settings->value("key/"+QString::number(i),"*").toString();
        QString cmd = settings->value("cmd/"+QString::number(i),"").toString();

        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        CmdListWidget *itemWidget = new CmdListWidget(ui->listWidget,key,cmd);
        item->setSizeHint(itemWidget->sizeHint());
        ui->listWidget->setItemWidget(item,itemWidget);

        connect(itemWidget,&CmdListWidget::readySend,this,&CmdList::onReadySend);

    }
}

void CmdList::saveCmd()
{
    for(int i = 0; i < ui->listWidget->count(); ++i){
        QListWidgetItem *item = ui->listWidget->item(i);
        CmdListWidget *widget = qobject_cast<CmdListWidget *>(ui->listWidget->itemWidget(item));
        settings->setValue("key/"+QString::number(i),widget->keyEdit->text());
        settings->setValue("cmd/"+QString::number(i),widget->cmdEdit->text());
    }
    settings->sync();
}

void CmdList::clearCmd()
{
    for(int i = 0; i < ui->listWidget->count(); ++i){
        QListWidgetItem *item = ui->listWidget->item(i);
        CmdListWidget *widget = qobject_cast<CmdListWidget *>(ui->listWidget->itemWidget(item));
        widget->cmdEdit->clear();
    }
}

void CmdList::clearKey()
{
    for(int i = 0; i < ui->listWidget->count(); ++i){
        QListWidgetItem *item = ui->listWidget->item(i);
        CmdListWidget *widget = qobject_cast<CmdListWidget *>(ui->listWidget->itemWidget(item));
        widget->keyEdit->setText("*");
    }
}


CmdList::~CmdList()
{
    saveCmd();



    delete ui;
}

void CmdList::keyPressEvent(QKeyEvent *e)
{
    if(e->key() >= 0x41 && e->key() <= 0x5a){
        for(int i = 0; i < ui->listWidget->count(); ++i){
            QListWidgetItem *item = ui->listWidget->item(i);
            CmdListWidget *widget = qobject_cast<CmdListWidget *>(ui->listWidget->itemWidget(item));
            if(widget->keyEdit->text().toUpper() == e->text().toUpper()){
                if(widget->cmdEdit->text().isEmpty()){
                    return;
                }
                emit widget->readySend(widget->cmdEdit->text());
                return;
            }
        }
    }
}

void CmdList::onReadySend(QString cmd)
{
    emit readySend(cmd);
}



