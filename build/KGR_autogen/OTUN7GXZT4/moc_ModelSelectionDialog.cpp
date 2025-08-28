/****************************************************************************
** Meta object code from reading C++ file 'ModelSelectionDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../view/ModelSelectionDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ModelSelectionDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModelSelectionDialog_t {
    QByteArrayData data[13];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModelSelectionDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModelSelectionDialog_t qt_meta_stringdata_ModelSelectionDialog = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ModelSelectionDialog"
QT_MOC_LITERAL(1, 21, 13), // "modelSelected"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "model"
QT_MOC_LITERAL(4, 42, 11), // "rcsSelected"
QT_MOC_LITERAL(5, 54, 7), // "RcsData"
QT_MOC_LITERAL(6, 62, 3), // "rcs"
QT_MOC_LITERAL(7, 66, 15), // "onModelSelected"
QT_MOC_LITERAL(8, 82, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(9, 99, 4), // "item"
QT_MOC_LITERAL(10, 104, 13), // "onRcsSelected"
QT_MOC_LITERAL(11, 118, 8), // "onAccept"
QT_MOC_LITERAL(12, 127, 8) // "onReturn"

    },
    "ModelSelectionDialog\0modelSelected\0\0"
    "model\0rcsSelected\0RcsData\0rcs\0"
    "onModelSelected\0QListWidgetItem*\0item\0"
    "onRcsSelected\0onAccept\0onReturn"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelSelectionDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   50,    2, 0x08 /* Private */,
      10,    1,   53,    2, 0x08 /* Private */,
      11,    0,   56,    2, 0x08 /* Private */,
      12,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVariant,    3,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ModelSelectionDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModelSelectionDialog *_t = static_cast<ModelSelectionDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->modelSelected((*reinterpret_cast< const QVariant(*)>(_a[1]))); break;
        case 1: _t->rcsSelected((*reinterpret_cast< const RcsData(*)>(_a[1]))); break;
        case 2: _t->onModelSelected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->onRcsSelected((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->onAccept(); break;
        case 5: _t->onReturn(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< RcsData >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ModelSelectionDialog::*_t)(const QVariant & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModelSelectionDialog::modelSelected)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ModelSelectionDialog::*_t)(const RcsData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ModelSelectionDialog::rcsSelected)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ModelSelectionDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ModelSelectionDialog.data,
      qt_meta_data_ModelSelectionDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ModelSelectionDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelSelectionDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModelSelectionDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ModelSelectionDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ModelSelectionDialog::modelSelected(const QVariant & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModelSelectionDialog::rcsSelected(const RcsData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
