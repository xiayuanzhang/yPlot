#include "setupframe.h"
#include "ui_setupframe.h"
#include <QSettings>
#include <QApplication>

QSettings g_settings(QApplication::applicationDirPath(), QSettings::IniFormat);

SetupFrame::SetupFrame(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SetupFrame)
{
    ui->setupUi(this);

    connect(ui->listWidget,&QListWidget::itemPressed,this,[=](QListWidgetItem *item){
        QString pageName = item->text();
        ui->stackedWidget->setCurrentWidget(pages[pageName]);
        ui->label->setText(pageName);
    });
}

SetupFrame::~SetupFrame()
{
    delete ui;
}

void SetupFrame::addPage(QString pageName, QWidget *setupPage)
{
    setupPage->setParent(this);

    ui->stackedWidget->addWidget(setupPage);
    ui->listWidget->addItem(pageName);

    pages.insert(pageName,setupPage);
}

void SetupFrame::removePage(QString pageName)
{
    QList<QListWidgetItem*> items = ui->listWidget->findItems(pageName,Qt::MatchCaseSensitive); //区分大小写的
    if(items.size() != 1)
        return;

    ui->stackedWidget->removeWidget(pages[pageName]);
    ui->listWidget->removeItemWidget(items.at(0));


    pages.remove(pageName);
}

void SetupFrame::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);
    if(pages.size() == 0)
        return;

    ui->stackedWidget->setCurrentWidget(pages.first());
    ui->label->setText(pages.firstKey());

}

void SetupFrame::on_ok_clicked()
{
    g_settings.sync();
    emit applySettings();
    close();
}


void SetupFrame::on_cancel_clicked()
{
    close();
}


void SetupFrame::on_apply_clicked()
{
    g_settings.sync();
    emit applySettings();
}

