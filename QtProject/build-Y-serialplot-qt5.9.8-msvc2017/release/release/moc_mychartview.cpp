/****************************************************************************
** Meta object code from reading C++ file 'mychartview.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../../../y-serialplot-master/QtProject/mychartview.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mychartview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_myChartView_t {
    QByteArrayData data[20];
    char stringdata0[191];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_myChartView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_myChartView_t qt_meta_stringdata_myChartView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "myChartView"
QT_MOC_LITERAL(1, 12, 9), // "mouseMove"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 3), // "key"
QT_MOC_LITERAL(4, 27, 6), // "nowPos"
QT_MOC_LITERAL(5, 34, 13), // "mouseMoveSize"
QT_MOC_LITERAL(6, 48, 2), // "dx"
QT_MOC_LITERAL(7, 51, 2), // "dy"
QT_MOC_LITERAL(8, 54, 18), // "mouseDoubleClicked"
QT_MOC_LITERAL(9, 73, 8), // "clickPos"
QT_MOC_LITERAL(10, 82, 12), // "mouseClicked"
QT_MOC_LITERAL(11, 95, 11), // "mousePressd"
QT_MOC_LITERAL(12, 107, 8), // "pressPos"
QT_MOC_LITERAL(13, 116, 12), // "mouseRelease"
QT_MOC_LITERAL(14, 129, 11), // "releasekPos"
QT_MOC_LITERAL(15, 141, 20), // "mousePressdToRelease"
QT_MOC_LITERAL(16, 162, 5), // "xsize"
QT_MOC_LITERAL(17, 168, 5), // "ysize"
QT_MOC_LITERAL(18, 174, 10), // "mouseWheel"
QT_MOC_LITERAL(19, 185, 5) // "value"

    },
    "myChartView\0mouseMove\0\0key\0nowPos\0"
    "mouseMoveSize\0dx\0dy\0mouseDoubleClicked\0"
    "clickPos\0mouseClicked\0mousePressd\0"
    "pressPos\0mouseRelease\0releasekPos\0"
    "mousePressdToRelease\0xsize\0ysize\0"
    "mouseWheel\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_myChartView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    3,   59,    2, 0x06 /* Public */,
       8,    2,   66,    2, 0x06 /* Public */,
      10,    2,   71,    2, 0x06 /* Public */,
      11,    2,   76,    2, 0x06 /* Public */,
      13,    2,   81,    2, 0x06 /* Public */,
      15,    3,   86,    2, 0x06 /* Public */,
      18,    1,   93,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF,    3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::QReal, QMetaType::QReal,    3,    6,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF,    3,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF,    3,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF,    3,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::QPointF,    3,   14,
    QMetaType::Void, QMetaType::Int, QMetaType::Double, QMetaType::Double,    3,   16,   17,
    QMetaType::Void, QMetaType::Int,   19,

       0        // eod
};

void myChartView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        myChartView *_t = static_cast<myChartView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->mouseMove((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 1: _t->mouseMoveSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qreal(*)>(_a[2])),(*reinterpret_cast< qreal(*)>(_a[3]))); break;
        case 2: _t->mouseDoubleClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 3: _t->mouseClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 4: _t->mousePressd((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 5: _t->mouseRelease((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QPointF(*)>(_a[2]))); break;
        case 6: _t->mousePressdToRelease((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< double(*)>(_a[2])),(*reinterpret_cast< double(*)>(_a[3]))); break;
        case 7: _t->mouseWheel((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (myChartView::*_t)(int , QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myChartView::mouseMove)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (myChartView::*_t)(int , qreal , qreal );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myChartView::mouseMoveSize)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (myChartView::*_t)(int , QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myChartView::mouseDoubleClicked)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (myChartView::*_t)(int , QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myChartView::mouseClicked)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (myChartView::*_t)(int , QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myChartView::mousePressd)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (myChartView::*_t)(int , QPointF );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myChartView::mouseRelease)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (myChartView::*_t)(int , double , double );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myChartView::mousePressdToRelease)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (myChartView::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&myChartView::mouseWheel)) {
                *result = 7;
                return;
            }
        }
    }
}

const QMetaObject myChartView::staticMetaObject = {
    { &QChartView::staticMetaObject, qt_meta_stringdata_myChartView.data,
      qt_meta_data_myChartView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *myChartView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *myChartView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_myChartView.stringdata0))
        return static_cast<void*>(this);
    return QChartView::qt_metacast(_clname);
}

int myChartView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QChartView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void myChartView::mouseMove(int _t1, QPointF _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void myChartView::mouseMoveSize(int _t1, qreal _t2, qreal _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void myChartView::mouseDoubleClicked(int _t1, QPointF _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void myChartView::mouseClicked(int _t1, QPointF _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void myChartView::mousePressd(int _t1, QPointF _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void myChartView::mouseRelease(int _t1, QPointF _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void myChartView::mousePressdToRelease(int _t1, double _t2, double _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void myChartView::mouseWheel(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
