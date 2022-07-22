/****************************************************************************
** Meta object code from reading C++ file 'drawplot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../drawplot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'drawplot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_drawPlot_t {
    QByteArrayData data[19];
    char stringdata0[252];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_drawPlot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_drawPlot_t qt_meta_stringdata_drawPlot = {
    {
QT_MOC_LITERAL(0, 0, 8), // "drawPlot"
QT_MOC_LITERAL(1, 9, 13), // "OnResetAction"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 15), // "OnShowAllAction"
QT_MOC_LITERAL(4, 40, 13), // "OnAutoYAction"
QT_MOC_LITERAL(5, 54, 16), // "selectionChanged"
QT_MOC_LITERAL(6, 71, 13), // "onLegendClick"
QT_MOC_LITERAL(7, 85, 10), // "QCPLegend*"
QT_MOC_LITERAL(8, 96, 6), // "legend"
QT_MOC_LITERAL(9, 103, 22), // "QCPAbstractLegendItem*"
QT_MOC_LITERAL(10, 126, 4), // "item"
QT_MOC_LITERAL(11, 131, 12), // "QMouseEvent*"
QT_MOC_LITERAL(12, 144, 5), // "event"
QT_MOC_LITERAL(13, 150, 19), // "onLegendDoubleClick"
QT_MOC_LITERAL(14, 170, 16), // "onPlottableClick"
QT_MOC_LITERAL(15, 187, 21), // "QCPAbstractPlottable*"
QT_MOC_LITERAL(16, 209, 9), // "plottable"
QT_MOC_LITERAL(17, 219, 9), // "dataIndex"
QT_MOC_LITERAL(18, 229, 22) // "onPlottableDoubleClick"

    },
    "drawPlot\0OnResetAction\0\0OnShowAllAction\0"
    "OnAutoYAction\0selectionChanged\0"
    "onLegendClick\0QCPLegend*\0legend\0"
    "QCPAbstractLegendItem*\0item\0QMouseEvent*\0"
    "event\0onLegendDoubleClick\0onPlottableClick\0"
    "QCPAbstractPlottable*\0plottable\0"
    "dataIndex\0onPlottableDoubleClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_drawPlot[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    3,   58,    2, 0x08 /* Private */,
      13,    3,   65,    2, 0x08 /* Private */,
      14,    3,   72,    2, 0x08 /* Private */,
      18,    3,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9, 0x80000000 | 11,    8,   10,   12,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 9, 0x80000000 | 11,    8,   10,   12,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int, 0x80000000 | 11,   16,   17,   12,
    QMetaType::Void, 0x80000000 | 15, QMetaType::Int, 0x80000000 | 11,   16,   17,   12,

       0        // eod
};

void drawPlot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        drawPlot *_t = static_cast<drawPlot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->OnResetAction(); break;
        case 1: _t->OnShowAllAction(); break;
        case 2: _t->OnAutoYAction(); break;
        case 3: _t->selectionChanged(); break;
        case 4: _t->onLegendClick((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 5: _t->onLegendDoubleClick((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 6: _t->onPlottableClick((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 7: _t->onPlottableDoubleClick((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        }
    }
}

const QMetaObject drawPlot::staticMetaObject = {
    { &QCustomPlot::staticMetaObject, qt_meta_stringdata_drawPlot.data,
      qt_meta_data_drawPlot,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *drawPlot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *drawPlot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_drawPlot.stringdata0))
        return static_cast<void*>(this);
    return QCustomPlot::qt_metacast(_clname);
}

int drawPlot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCustomPlot::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
