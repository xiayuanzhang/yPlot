#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    w.move ((QApplication::desktop()->width() - w.width())/2
            ,(QApplication::desktop()->height() - w.height())/2);
    QFont f("楷体",12);
    a.setFont(f);
    return a.exec();
}
