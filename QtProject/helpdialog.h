#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>

namespace Ui {
class helpDialog;
}

class helpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit helpDialog(QWidget *parent = nullptr);
    ~helpDialog();

private:
    Ui::helpDialog *ui;
};

#endif // HELPDIALOG_H
