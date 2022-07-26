#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtSerialPort>
#include <QSerialPortInfo>

#include "jsonfile.h"
#include "dataanalysis.h"

#include "qframelesswidget.h"

#include "qcustomplot.h"
#include "drawplot.h"

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

    void findPortTimer_timeout();
    void serialport_readyread();

    void on_checkBox_stop_clicked(bool checked);
    void onStopStatusChanged(bool stop);


    void on_pushButton_resetKey_clicked();

    void on_pushButton_resetCmd_clicked();

    void haveNewPoint_drawPlot(QVector<double> newdata);
    void haveNewName_drawPlot(QVector<QString> name);

    void on_pushButton_clear_clicked();

    void on_pushButton_output_clicked();

    void on_pushButton_help_clicked();

    void on_checkBox_auto_clicked(bool checked);

    void on_pushButton_reset_clicked();


    void on_pushButton_showall_clicked();

    void on_spinBox_buff_editingFinished();
    void on_spinBox_wind_editingFinished();

    void onIntervaChanged(int interva);



    void on_scrollBar_pos_valueChanged(int value);



    void on_pushButton_hideall_clicked();

private:
    Ui::Widget *ui;
    QPoint m_startMovePoint;
    bool m_startMoveFlag;

    QSerialPort *serialport;//串口对象
    QTimer *findPortTimer; // 定时器，用于定时搜索串口
    QList<QSerialPortInfo> portlist;

    //配置文件
    jsonFile configFile;
    //设置参数
    char keyCmd[55];

    //数据解析对象
    dataAnalysis *analysis;

};

#endif // WIDGET_H
