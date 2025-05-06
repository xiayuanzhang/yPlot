#ifndef CMDLIST_H
#define CMDLIST_H

#include <QWidget>
#include <QSettings>
#include <QLineEdit>
#include <QPushButton>

//按键指令的listview中的单个item的widget

namespace Ui {
class CmdList;
}

class CmdListWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CmdListWidget(QWidget *parent = nullptr,QString key = "*", QString cmd = "");
    ~CmdListWidget();

    QLineEdit *keyEdit;
    QLineEdit *cmdEdit;
    QPushButton *btn;
public slots:
    //void keyEditFinish();
    void cmdEditFinish();
    void btnClicked(bool checked);

signals:
    void readySend(QString cmd);


private:

};



class CmdList : public QWidget
{
    Q_OBJECT

public:
    explicit CmdList(QWidget *parent = nullptr);
    void loadCmd(QString settingFile);
    void saveCmd();

    void clearCmd();
    void clearKey();

    ~CmdList();

    void keyPressEvent(QKeyEvent *e);
protected:
    //bool eventFilter(QObject *watched, QEvent *event);

private slots:
    void onReadySend(QString cmd);

signals:
    void readySend(QString cmd);
private:
    Ui::CmdList *ui;
    QSettings *settings;
};

#endif // CMDLIST_H
