#include "helpdialog.h"
#include "ui_helpdialog.h"

helpDialog::helpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpDialog)
{
    ui->setupUi(this);
    ui->webEngineView->load(QUrl("qrc:/help/help.html"));
}

helpDialog::~helpDialog()
{
    delete ui;
}
