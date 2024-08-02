#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QSettings>

#include "qframelesswidget.h"
#include "serialinfo.h"
#include "qcustomplot.h"
#include "drawplot.h"

#include "data/yframe.h"
#include "plotdemo.h"
#include "myscorllbar.h"

namespace Ui {
class Widget;
}

class Widget : public QFramelessWidget
{
    Q_OBJECT

public:
    explicit Widget(bool resizeEnable = true,
                    bool shadowBorder = true,
                    bool winNativeEvent = true,
                    QWidget *parent = 0);
    ~Widget();

private:
    void initForm();

    void keyPressEvent(QKeyEvent *e);  //widget下的按键按下事件

    void createCmd();
private slots:

    void maximizedChanged(bool max);

    void on_pushButton_close_clicked();

    void on_pushButton_little_clicked();

    void on_pushButton_size_clicked();

    void lineEdit_finish();
    void lineEdit_return();

    void on_checkBox_open_clicked(bool checked);

    void onReadyRead();

    void on_checkBox_stop_clicked(bool checked);


    void on_pushButton_resetKey_clicked();

    void on_pushButton_resetCmd_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_output_clicked();

    void on_pushButton_help_clicked();

    void on_checkBox_auto_clicked(bool checked);

    void on_pushButton_reset_clicked();


    void on_pushButton_showall_clicked();

    void on_spinBox_buff_editingFinished();
    void on_spinBox_wind_editingFinished();

    void slot_plotviewXRangeChanged(double low,double up);



    void slot_scrollBarMove(int min, int max);



    void on_pushButton_hideall_clicked();

    //串口列表出现改变
    void portListChanged(const QList<QSerialPortInfo> &portlist);
    //接收解析的帧数据
    void onFrameReceived(QVector<YFrame_t> frame);
    void on_pushButton_demo_clicked();

private:
    Ui::Widget *ui;
    bool m_stopReceivePlotData = false;

    QSerialPort *serialport;//串口对象
    SerialInfo *serialInfo;//串口信息对象

    QChar cmdKey[50];//命令

    PlotDemo *plotdemo;
//数据
    YFrame *yframe;//数据解析对象
//参数
    QSettings *settings;

    MyScorllBar *scrollBar;

};

#endif // WIDGET_H
