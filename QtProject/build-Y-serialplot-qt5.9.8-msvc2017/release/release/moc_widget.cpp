/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../y-serialplot-master/QtProject/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[41];
    char stringdata0[765];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 16), // "maximizedChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 3), // "max"
QT_MOC_LITERAL(4, 29, 27), // "on_pushButton_close_clicked"
QT_MOC_LITERAL(5, 57, 28), // "on_pushButton_little_clicked"
QT_MOC_LITERAL(6, 86, 26), // "on_pushButton_size_clicked"
QT_MOC_LITERAL(7, 113, 15), // "lineEdit_finish"
QT_MOC_LITERAL(8, 129, 15), // "lineEdit_return"
QT_MOC_LITERAL(9, 145, 24), // "on_checkBox_open_clicked"
QT_MOC_LITERAL(10, 170, 7), // "checked"
QT_MOC_LITERAL(11, 178, 21), // "findPortTimer_timeout"
QT_MOC_LITERAL(12, 200, 20), // "serialport_readyread"
QT_MOC_LITERAL(13, 221, 24), // "on_checkBox_stop_clicked"
QT_MOC_LITERAL(14, 246, 26), // "on_pushButton_help_clicked"
QT_MOC_LITERAL(15, 273, 31), // "on_spinBox_channel_valueChanged"
QT_MOC_LITERAL(16, 305, 4), // "arg1"
QT_MOC_LITERAL(17, 310, 39), // "on_comboBox_datatype_currentT..."
QT_MOC_LITERAL(18, 350, 30), // "on_pushButton_resetKey_clicked"
QT_MOC_LITERAL(19, 381, 30), // "on_pushButton_resetCmd_clicked"
QT_MOC_LITERAL(20, 412, 21), // "haveNewPoint_drawPlot"
QT_MOC_LITERAL(21, 434, 25), // "QVector<QVector<double> >"
QT_MOC_LITERAL(22, 460, 7), // "newdata"
QT_MOC_LITERAL(23, 468, 20), // "haveNewName_drawPlot"
QT_MOC_LITERAL(24, 489, 16), // "QVector<QString>"
QT_MOC_LITERAL(25, 506, 4), // "name"
QT_MOC_LITERAL(26, 511, 22), // "chartview_mouseClicked"
QT_MOC_LITERAL(27, 534, 3), // "key"
QT_MOC_LITERAL(28, 538, 8), // "clickPos"
QT_MOC_LITERAL(29, 547, 28), // "chartview_mouseDoubleClicked"
QT_MOC_LITERAL(30, 576, 19), // "chartview_mouseMove"
QT_MOC_LITERAL(31, 596, 6), // "nowPos"
QT_MOC_LITERAL(32, 603, 20), // "chartview_mouseWheel"
QT_MOC_LITERAL(33, 624, 5), // "value"
QT_MOC_LITERAL(34, 630, 22), // "chartview_mouseRelease"
QT_MOC_LITERAL(35, 653, 11), // "releasekPos"
QT_MOC_LITERAL(36, 665, 12), // "setup_finish"
QT_MOC_LITERAL(37, 678, 1), // "a"
QT_MOC_LITERAL(38, 680, 27), // "on_pushButton_setup_clicked"
QT_MOC_LITERAL(39, 708, 27), // "on_pushButton_clear_clicked"
QT_MOC_LITERAL(40, 736, 28) // "on_pushButton_output_clicked"

    },
    "Widget\0maximizedChanged\0\0max\0"
    "on_pushButton_close_clicked\0"
    "on_pushButton_little_clicked\0"
    "on_pushButton_size_clicked\0lineEdit_finish\0"
    "lineEdit_return\0on_checkBox_open_clicked\0"
    "checked\0findPortTimer_timeout\0"
    "serialport_readyread\0on_checkBox_stop_clicked\0"
    "on_pushButton_help_clicked\0"
    "on_spinBox_channel_valueChanged\0arg1\0"
    "on_comboBox_datatype_currentTextChanged\0"
    "on_pushButton_resetKey_clicked\0"
    "on_pushButton_resetCmd_clicked\0"
    "haveNewPoint_drawPlot\0QVector<QVector<double> >\0"
    "newdata\0haveNewName_drawPlot\0"
    "QVector<QString>\0name\0chartview_mouseClicked\0"
    "key\0clickPos\0chartview_mouseDoubleClicked\0"
    "chartview_mouseMove\0nowPos\0"
    "chartview_mouseWheel\0value\0"
    "chartview_mouseRelease\0releasekPos\0"
    "setup_finish\0a\0on_pushButton_setup_clicked\0"
    "on_pushButton_clear_clicked\0"
    "on_pushButton_output_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      26,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,  144,    2, 0x08 /* Private */,
       4,    0,  147,    2, 0x08 /* Private */,
       5,    0,  148,    2, 0x08 /* Private */,
       6,    0,  149,    2, 0x08 /* Private */,
       7,    0,  150,    2, 0x08 /* Private */,
       8,    0,  151,    2, 0x08 /* Private */,
       9,    1,  152,    2, 0x08 /* Private */,
      11,    0,  155,    2, 0x08 /* Private */,
      12,    0,  156,    2, 0x08 /* Private */,
      13,    1,  157,    2, 0x08 /* Private */,
      14,    0,  160,    2, 0x08 /* Private */,
      15,    1,  161,    2, 0x08 /* Private */,
      17,    1,  164,    2, 0x08 /* Private */,
      18,    0,  167,    2, 0x08 /* Private */,
      19,    0,  168,    2, 0x08 /* Private */,
      20,    1,  169,    2, 0x08 /* Private */,
      23,    1,  172,    2, 0x08 /* Private */,
      26,    2,  175,    2, 0x08 /* Private */,
      29,    2,  180,    2, 0x08 /* Private */,
      30,    2,  185,    2, 0x08 /* Private */,
      32,    1,  190,    2, 0x08 /* Private */,
      34,    2,  193,    2, 0x08 /* Private */,
      36,    1,  198,    2, 0x08 /* Private */,
      38,    0,  201,    2, 0x08 /* Private */,
      39,    0,  202,    2, 0x08 /* Private */,
      40,    0,  203,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, 0x80000000 | 24,   25,
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF,   27,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF,   27,   28,
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF,   27,   31,
    QMetaType::Void, QMetaType::Int,   33,
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF,   27,   35,
    QMetaType::Void, QMetaType::Int,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Widget *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->maximizedChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->on_pushButton_close_clicked(); break;
        case 2: _t->on_pushButton_little_clicked(); break;
        case 3: _t->on_pushButton_size_clicked(); break;
        case 4: _t->lineEdit_finish(); break;
        case 5: _t->lineEdit_return(); break;
        case 6: _t->on_checkBox_open_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->findPortTimer_timeout(); break;
        case 8: _t->serialport_readyread(); break;
        case 9: _t->on_checkBox_stop_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_pushButton_help_clicked(); break;
        case 11: _t->on_spinBox_channel_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_comboBox_datatype_currentTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->on_pushButton_resetKey_clicked(); break;
        case 14: _t->on_pushButton_resetCmd_clicked(); break;
        case 15: _t->haveNewPoint_drawPlot((*reinterpret_cast< QVector<QVector<double> >(*)>(_a[1]))); break;
        case 16: _t->haveNewName_drawPlot((*reinterpret_cast< QVector<QString>(*)>(_a[1]))); break;
        case 17: _t->chartview_mouseClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 18: _t->chartview_mouseDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 19: _t->chartview_mouseMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 20: _t->chartview_mouseWheel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->chartview_mouseRelease((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 22: _t->setup_finish((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->on_pushButton_setup_clicked(); break;
        case 24: _t->on_pushButton_clear_clicked(); break;
        case 25: _t->on_pushButton_output_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 15:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QVector<double> > >(); break;
            }
            break;
        case 16:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<QString> >(); break;
            }
            break;
        }
    }
}

const QMetaObject Widget::staticMetaObject = {
    { &QFramelessWidget::staticMetaObject, qt_meta_stringdata_Widget.data,
      qt_meta_data_Widget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QFramelessWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFramelessWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 26)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 26;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
