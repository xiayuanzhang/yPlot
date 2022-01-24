#ifndef SETUP_H
#define SETUP_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class setup;
}

class setup : public QDialog
{
    Q_OBJECT

public:
    explicit setup(QWidget *parent = nullptr);
    ~setup();
    void setWatchSize(int size);
    void setBuffSize(int size);
    int getWatchSize();
    int getBuffSize();

private slots:

    void on_spinBox_watch_valueChanged(int arg1);

    void on_spinBox_buff_valueChanged(int arg1);

private:
    Ui::setup *ui;

    int buffSize = 0;
    int watchSize = 0;
};

#endif // SETUP_H
