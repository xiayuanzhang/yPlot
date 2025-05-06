#ifndef SETUPFRAME_H
#define SETUPFRAME_H

#include <QWidget>
#include <QMap>

namespace Ui {
class SetupFrame;
}

class SetupFrame : public QWidget
{
    Q_OBJECT

public:
    explicit SetupFrame(QWidget *parent = nullptr);
    ~SetupFrame();
    void addPage(QString pageName,QWidget *setupPage);
    void removePage(QString pageName);
protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

    void on_apply_clicked();

signals:
    void applySettings();
private:
    Ui::SetupFrame *ui;
    QMap<QString,QWidget*> pages;
};

#endif // SETUPFRAME_H
