/****************************************************************************
** Meta object code from reading C++ file 'mserialport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GateWayClient/mserialport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mserialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MSerialPort_t {
    QByteArrayData data[6];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MSerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MSerialPort_t qt_meta_stringdata_MSerialPort = {
    {
QT_MOC_LITERAL(0, 0, 11), // "MSerialPort"
QT_MOC_LITERAL(1, 12, 13), // "writeFinished"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "dataReceived"
QT_MOC_LITERAL(4, 40, 17), // "onDataQueueHandle"
QT_MOC_LITERAL(5, 58, 20) // "onSerialDataReceived"

    },
    "MSerialPort\0writeFinished\0\0dataReceived\0"
    "onDataQueueHandle\0onSerialDataReceived"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MSerialPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    1,   35,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   38,    2, 0x0a /* Public */,
       5,    0,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArrayList,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MSerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MSerialPort *_t = static_cast<MSerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->writeFinished(); break;
        case 1: _t->dataReceived((*reinterpret_cast< const QByteArrayList(*)>(_a[1]))); break;
        case 2: _t->onDataQueueHandle(); break;
        case 3: _t->onSerialDataReceived(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MSerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MSerialPort::writeFinished)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MSerialPort::*_t)(const QByteArrayList & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MSerialPort::dataReceived)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MSerialPort::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MSerialPort.data,
      qt_meta_data_MSerialPort,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MSerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MSerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MSerialPort.stringdata0))
        return static_cast<void*>(const_cast< MSerialPort*>(this));
    return QObject::qt_metacast(_clname);
}

int MSerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void MSerialPort::writeFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void MSerialPort::dataReceived(const QByteArrayList & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
