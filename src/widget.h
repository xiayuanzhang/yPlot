#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCharts>
#include <QtSerialPort>
#include <QSerialPortInfo>

#include "jsonfile.h"
#include "dataanalysis.h"
#include "setup.h"

#include "qframelesswidget.h"

using namespace QtCharts;

class Callout;

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


    void on_spinBox_channel_valueChanged(int arg1);

    void on_comboBox_datatype_currentTextChanged(const QString &arg1);




    void on_pushButton_resetKey_clicked();

    void on_pushButton_resetCmd_clicked();

    void haveNewPoint_drawPlot(QVector<QVector<double>> newdata);
    void haveNewName_drawPlot(QVector<QString> name);


    void setup_finish(int a);


    void on_pushButton_setup_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_output_clicked();

    void on_pushButton_help_clicked();

private:
    Ui::Widget *ui;
    QPoint m_startMovePoint;
    bool m_startMoveFlag;

    QSerialPort serialport;//串口对象
    QTimer *findPortTimer; // 定时器，用于定时搜索串口
    QList<QSerialPortInfo> portlist;

    //配置文件
    jsonFile configFile;
    //设置参数
    bool stopFlag = false; //控制暂停和继续的变量 true = 目前处于暂停状态
    char keyCmd[55];

    //数据解析对象
    dataAnalysis analysis;
    setup *setupPage;
    Callout *tooltip;

    bool plotShowDataFlag = true;

};

#endif // WIDGET_H
