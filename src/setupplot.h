#ifndef SETUPPLOT_H
#define SETUPPLOT_H

#include <QWidget>

namespace Ui {
class setupPlot;
}

class setupPlot : public QWidget
{
    Q_OBJECT

public:
    explicit setupPlot(QWidget *parent = nullptr);
    ~setupPlot();

private:
    Ui::setupPlot *ui;
};

#endif // SETUPPLOT_H
