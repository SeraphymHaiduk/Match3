/****************************************************************************
** Meta object code from reading C++ file 'mymodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mymodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mymodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyModel_t {
    QByteArrayData data[28];
    char stringdata0[317];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyModel_t qt_meta_stringdata_MyModel = {
    {
QT_MOC_LITERAL(0, 0, 7), // "MyModel"
QT_MOC_LITERAL(1, 8, 16), // "rowsCountChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 19), // "columnsCountChanged"
QT_MOC_LITERAL(4, 46, 12), // "scoreChanged"
QT_MOC_LITERAL(5, 59, 12), // "stepsChanged"
QT_MOC_LITERAL(6, 72, 11), // "wrongChoise"
QT_MOC_LITERAL(7, 84, 11), // "rightChoise"
QT_MOC_LITERAL(8, 96, 15), // "matchesHappened"
QT_MOC_LITERAL(9, 112, 18), // "matchesNotHappened"
QT_MOC_LITERAL(10, 131, 16), // "readyToDisappear"
QT_MOC_LITERAL(11, 148, 13), // "readyToRemove"
QT_MOC_LITERAL(12, 162, 8), // "gameOver"
QT_MOC_LITERAL(13, 171, 8), // "populate"
QT_MOC_LITERAL(14, 180, 7), // "pressOn"
QT_MOC_LITERAL(15, 188, 5), // "index"
QT_MOC_LITERAL(16, 194, 13), // "stateToString"
QT_MOC_LITERAL(17, 208, 21), // "MyModel::ElementState"
QT_MOC_LITERAL(18, 230, 5), // "state"
QT_MOC_LITERAL(19, 236, 9), // "rowsCount"
QT_MOC_LITERAL(20, 246, 12), // "columnsCount"
QT_MOC_LITERAL(21, 259, 5), // "score"
QT_MOC_LITERAL(22, 265, 5), // "steps"
QT_MOC_LITERAL(23, 271, 12), // "ElementState"
QT_MOC_LITERAL(24, 284, 7), // "Pressed"
QT_MOC_LITERAL(25, 292, 10), // "NotPressed"
QT_MOC_LITERAL(26, 303, 5), // "Wrong"
QT_MOC_LITERAL(27, 309, 7) // "Deleted"

    },
    "MyModel\0rowsCountChanged\0\0columnsCountChanged\0"
    "scoreChanged\0stepsChanged\0wrongChoise\0"
    "rightChoise\0matchesHappened\0"
    "matchesNotHappened\0readyToDisappear\0"
    "readyToRemove\0gameOver\0populate\0pressOn\0"
    "index\0stateToString\0MyModel::ElementState\0"
    "state\0rowsCount\0columnsCount\0score\0"
    "steps\0ElementState\0Pressed\0NotPressed\0"
    "Wrong\0Deleted"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       4,  102, // properties
       1,  118, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    0,   86,    2, 0x06 /* Public */,
       5,    0,   87,    2, 0x06 /* Public */,
       6,    0,   88,    2, 0x06 /* Public */,
       7,    0,   89,    2, 0x06 /* Public */,
       8,    0,   90,    2, 0x06 /* Public */,
       9,    0,   91,    2, 0x06 /* Public */,
      10,    0,   92,    2, 0x06 /* Public */,
      11,    0,   93,    2, 0x06 /* Public */,
      12,    0,   94,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
      13,    0,   95,    2, 0x02 /* Public */,
      14,    1,   96,    2, 0x02 /* Public */,
      16,    1,   99,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void,
    QMetaType::Bool, QMetaType::Int,   15,
    QMetaType::QString, 0x80000000 | 17,   18,

 // properties: name, type, flags
      19, QMetaType::Int, 0x00495001,
      20, QMetaType::Int, 0x00495001,
      21, QMetaType::Int, 0x00495001,
      22, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

 // enums: name, alias, flags, count, data
      23,   23, 0x2,    4,  123,

 // enum data: key, value
      24, uint(MyModel::ElementState::Pressed),
      25, uint(MyModel::ElementState::NotPressed),
      26, uint(MyModel::ElementState::Wrong),
      27, uint(MyModel::ElementState::Deleted),

       0        // eod
};

void MyModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rowsCountChanged(); break;
        case 1: _t->columnsCountChanged(); break;
        case 2: _t->scoreChanged(); break;
        case 3: _t->stepsChanged(); break;
        case 4: _t->wrongChoise(); break;
        case 5: _t->rightChoise(); break;
        case 6: _t->matchesHappened(); break;
        case 7: _t->matchesNotHappened(); break;
        case 8: _t->readyToDisappear(); break;
        case 9: _t->readyToRemove(); break;
        case 10: _t->gameOver(); break;
        case 11: _t->populate(); break;
        case 12: { bool _r = _t->pressOn((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 13: { QString _r = _t->stateToString((*reinterpret_cast< MyModel::ElementState(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyModel::rowsCountChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyModel::columnsCountChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyModel::scoreChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyModel::stepsChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MyModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyModel::wrongChoise)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MyModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyModel::rightChoise)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (MyModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyModel::matchesHappened)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (MyModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyModel::matchesNotHappened)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (MyModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyModel::readyToDisappear)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (MyModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyModel::readyToRemove)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (MyModel::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyModel::gameOver)) {
                *result = 10;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<MyModel *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->getRowsCount(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->getColumnsCount(); break;
        case 2: *reinterpret_cast< int*>(_v) = _t->getScore(); break;
        case 3: *reinterpret_cast< int*>(_v) = _t->getSteps(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject MyModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_MyModel.data,
    qt_meta_data_MyModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MyModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int MyModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void MyModel::rowsCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyModel::columnsCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyModel::scoreChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void MyModel::stepsChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MyModel::wrongChoise()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MyModel::rightChoise()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void MyModel::matchesHappened()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void MyModel::matchesNotHappened()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}

// SIGNAL 8
void MyModel::readyToDisappear()
{
    QMetaObject::activate(this, &staticMetaObject, 8, nullptr);
}

// SIGNAL 9
void MyModel::readyToRemove()
{
    QMetaObject::activate(this, &staticMetaObject, 9, nullptr);
}

// SIGNAL 10
void MyModel::gameOver()
{
    QMetaObject::activate(this, &staticMetaObject, 10, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
