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
    char stringdata0[262];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_drawPlot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_drawPlot_t qt_meta_stringdata_drawPlot = {
    {
QT_MOC_LITERAL(0, 0, 8), // "drawPlot"
QT_MOC_LITERAL(1, 9, 14), // "intervaChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 13), // "interval_size"
QT_MOC_LITERAL(4, 39, 24), // "mouseEventIntervaChanged"
QT_MOC_LITERAL(5, 64, 16), // "selectionChanged"
QT_MOC_LITERAL(6, 81, 13), // "onLegendClick"
QT_MOC_LITERAL(7, 95, 10), // "QCPLegend*"
QT_MOC_LITERAL(8, 106, 6), // "legend"
QT_MOC_LITERAL(9, 113, 22), // "QCPAbstractLegendItem*"
QT_MOC_LITERAL(10, 136, 4), // "item"
QT_MOC_LITERAL(11, 141, 12), // "QMouseEvent*"
QT_MOC_LITERAL(12, 154, 5), // "event"
QT_MOC_LITERAL(13, 160, 19), // "onLegendDoubleClick"
QT_MOC_LITERAL(14, 180, 16), // "onPlottableClick"
QT_MOC_LITERAL(15, 197, 21), // "QCPAbstractPlottable*"
QT_MOC_LITERAL(16, 219, 9), // "plottable"
QT_MOC_LITERAL(17, 229, 9), // "dataIndex"
QT_MOC_LITERAL(18, 239, 22) // "onPlottableDoubleClick"

    },
    "drawPlot\0intervaChanged\0\0interval_size\0"
    "mouseEventIntervaChanged\0selectionChanged\0"
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
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   55,    2, 0x08 /* Private */,
       6,    3,   56,    2, 0x08 /* Private */,
      13,    3,   63,    2, 0x08 /* Private */,
      14,    3,   70,    2, 0x08 /* Private */,
      18,    3,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
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
        case 0: _t->intervaChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->mouseEventIntervaChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->selectionChanged(); break;
        case 3: _t->onLegendClick((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 4: _t->onLegendDoubleClick((*reinterpret_cast< QCPLegend*(*)>(_a[1])),(*reinterpret_cast< QCPAbstractLegendItem*(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 5: _t->onPlottableClick((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        case 6: _t->onPlottableDoubleClick((*reinterpret_cast< QCPAbstractPlottable*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< QMouseEvent*(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractLegendItem* >(); break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPLegend* >(); break;
            }
            break;
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
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCPAbstractPlottable* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (drawPlot::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&drawPlot::intervaChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (drawPlot::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&drawPlot::mouseEventIntervaChanged)) {
                *result = 1;
                return;
            }
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
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void drawPlot::intervaChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void drawPlot::mouseEventIntervaChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
