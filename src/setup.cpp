#include "setup.h"
#include "ui_setup.h"
#include <QDebug>
#include <QPushButton>
setup::setup(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::setup)
{
    ui->setupUi(this);
    ui->spinBox_buff->setRange(1000,10000);
    ui->spinBox_watch->setRange(10,10000);
}

setup::~setup()
{
    delete ui;
}

void setup::setWatchSize(int size)
{
    watchSize = size;
    ui->spinBox_watch->setValue(watchSize);
}

void setup::setBuffSize(int size)
{
    buffSize = size;
    ui->spinBox_buff->setValue(buffSize);

}

int setup::getWatchSize()
{
    return watchSize;
}

int setup::getBuffSize()
{
    return buffSize;
}

void setup::on_spinBox_watch_valueChanged(int arg1)
{
    setWatchSize(arg1);
}

void setup::on_spinBox_buff_valueChanged(int arg1)
{
    setBuffSize(arg1);
}
