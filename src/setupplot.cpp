#include "setupplot.h"
#include "ui_setupplot.h"
#include "setupframe.h"

setupPlot::setupPlot(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::setupPlot)
{
    ui->setupUi(this);
}

setupPlot::~setupPlot()
{
    delete ui;
}
