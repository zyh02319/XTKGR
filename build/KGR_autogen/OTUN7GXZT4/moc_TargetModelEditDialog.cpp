/****************************************************************************
** Meta object code from reading C++ file 'TargetModelEditDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../view/TargetModelEditDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TargetModelEditDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TargetModelEditDialog_t {
    QByteArrayData data[7];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TargetModelEditDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TargetModelEditDialog_t qt_meta_stringdata_TargetModelEditDialog = {
    {
QT_MOC_LITERAL(0, 0, 21), // "TargetModelEditDialog"
QT_MOC_LITERAL(1, 22, 12), // "onSaveTarget"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 11), // "onCreateRcs"
QT_MOC_LITERAL(4, 48, 9), // "onEditRcs"
QT_MOC_LITERAL(5, 58, 11), // "onDeleteRcs"
QT_MOC_LITERAL(6, 70, 21) // "onRcsSelectionChanged"

    },
    "TargetModelEditDialog\0onSaveTarget\0\0"
    "onCreateRcs\0onEditRcs\0onDeleteRcs\0"
    "onRcsSelectionChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TargetModelEditDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x08 /* Private */,
       3,    0,   40,    2, 0x08 /* Private */,
       4,    0,   41,    2, 0x08 /* Private */,
       5,    0,   42,    2, 0x08 /* Private */,
       6,    0,   43,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TargetModelEditDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TargetModelEditDialog *_t = static_cast<TargetModelEditDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSaveTarget(); break;
        case 1: _t->onCreateRcs(); break;
        case 2: _t->onEditRcs(); break;
        case 3: _t->onDeleteRcs(); break;
        case 4: _t->onRcsSelectionChanged(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject TargetModelEditDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_TargetModelEditDialog.data,
      qt_meta_data_TargetModelEditDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TargetModelEditDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TargetModelEditDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TargetModelEditDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int TargetModelEditDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
