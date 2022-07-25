#-------------------------------------------------
#
# Project created by QtCreator 2021-11-01T20:44:37
#
#-------------------------------------------------

QT       += core gui serialport printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = Y-serialplot
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
        main.cpp \
        widget.cpp \
    jsonfile.cpp \
    dataanalysis.cpp \
    outputdata.cpp \
    qcustomplot.cpp \
    drawplot.cpp

HEADERS += \
        widget.h \
    jsonfile.h \
    dataanalysis.h \
    outputdata.h \
    qcustomplot.h \
    drawplot.h

FORMS += \
        widget.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target




INCLUDEPATH += $$PWD/qframeless
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


