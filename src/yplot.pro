#-------------------------------------------------
#
# Project created by QtCreator 2021-11-01T20:44:37
#
#-------------------------------------------------

QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = yplot
TEMPLATE = app

RC_ICONS = Icon.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    cmdlist.cpp \
    data/yframe.cpp \
    main.cpp \
    myscorllbar.cpp \
    mytimer.cpp \
    plot/mybuoy.cpp \
    plot/plotdemo.cpp \
    serialinfo.cpp \
    setupframe.cpp \
    setupmanage.cpp \
    setupplot.cpp \
    widget.cpp \
    plot/qcustomplot.cpp \
    plot/drawplot.cpp\
    plot/verticalline.cpp

HEADERS += \
    cmdlist.h \
    data/ringqueue.h \
    data/yframe.h \
    myscorllbar.h \
    mytimer.h \
    plot/mybuoy.h \
    plot/plotdemo.h \
    serialinfo.h \
    setupframe.h \
    setupmanage.h \
    setupplot.h \
    widget.h \
    plot/qcustomplot.h \
    plot/drawplot.h\
    plot/verticalline.h

FORMS += \
    cmdlist.ui \
    setupframe.ui \
    setupplot.ui \
        widget.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




INCLUDEPATH += $$PWD/qframeless \
    $$PWD/plot \
    $$PWD/data
include ($$PWD/qframeless/qframeless.pri)

DISTFILES += \
    img/output.svg \
    img/send.svg \
    img/setup.svg \
    img/size-1.svg \
    img/size-2.svg \
    img/stop-off.svg \
    img/stop-on.svg

RESOURCES += \
    Resource/img.qrc


