#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    QFont f("楷体",12);
    a.setFont(f);
    return a.exec();
}
