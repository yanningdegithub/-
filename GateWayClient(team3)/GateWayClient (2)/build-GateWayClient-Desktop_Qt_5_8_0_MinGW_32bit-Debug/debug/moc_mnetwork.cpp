/****************************************************************************
** Meta object code from reading C++ file 'mnetwork.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../GateWayClient/mnetwork.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mnetwork.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MNetwork_t {
    QByteArrayData data[7];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MNetwork_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MNetwork_t qt_meta_stringdata_MNetwork = {
    {
QT_MOC_LITERAL(0, 0, 8), // "MNetwork"
QT_MOC_LITERAL(1, 9, 15), // "netDataReceived"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 11), // "netDataSend"
QT_MOC_LITERAL(4, 38, 20), // "onClientDataReceived"
QT_MOC_LITERAL(5, 59, 20), // "onDisconnectedHandle"
QT_MOC_LITERAL(6, 80, 16) // "onClientDataSend"

    },
    "MNetwork\0netDataReceived\0\0netDataSend\0"
    "onClientDataReceived\0onDisconnectedHandle\0"
    "onClientDataSend"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MNetwork[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   45,    2, 0x0a /* Public */,
       5,    0,   46,    2, 0x0a /* Public */,
       6,    1,   47,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArrayList,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,

       0        // eod
};

void MNetwork::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MNetwork *_t = static_cast<MNetwork *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->netDataReceived((*reinterpret_cast< const QByteArrayList(*)>(_a[1]))); break;
        case 1: _t->netDataSend((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        case 2: _t->onClientDataReceived(); break;
        case 3: _t->onDisconnectedHandle(); break;
        case 4: _t->onClientDataSend((*reinterpret_cast< const QJsonObject(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MNetwork::*_t)(const QByteArrayList & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MNetwork::netDataReceived)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (MNetwork::*_t)(const QJsonObject & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MNetwork::netDataSend)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject MNetwork::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MNetwork.data,
      qt_meta_data_MNetwork,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MNetwork::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MNetwork::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MNetwork.stringdata0))
        return static_cast<void*>(const_cast< MNetwork*>(this));
    return QObject::qt_metacast(_clname);
}

int MNetwork::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MNetwork::netDataReceived(const QByteArrayList & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MNetwork::netDataSend(const QJsonObject & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
