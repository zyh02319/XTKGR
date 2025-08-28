/****************************************************************************
** Meta object code from reading C++ file 'ModelManagerView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../view/ModelManagerView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ModelManagerView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModelManagerView_t {
    QByteArrayData data[10];
    char stringdata0[105];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModelManagerView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModelManagerView_t qt_meta_stringdata_ModelManagerView = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ModelManagerView"
QT_MOC_LITERAL(1, 17, 18), // "onModelTypeChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 2), // "id"
QT_MOC_LITERAL(4, 40, 13), // "onCreateModel"
QT_MOC_LITERAL(5, 54, 11), // "onEditModel"
QT_MOC_LITERAL(6, 66, 3), // "row"
QT_MOC_LITERAL(7, 70, 13), // "onDeleteModel"
QT_MOC_LITERAL(8, 84, 11), // "onViewModel"
QT_MOC_LITERAL(9, 96, 8) // "onSearch"

    },
    "ModelManagerView\0onModelTypeChanged\0"
    "\0id\0onCreateModel\0onEditModel\0row\0"
    "onDeleteModel\0onViewModel\0onSearch"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModelManagerView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x08 /* Private */,
       4,    0,   47,    2, 0x08 /* Private */,
       5,    1,   48,    2, 0x08 /* Private */,
       7,    1,   51,    2, 0x08 /* Private */,
       8,    1,   54,    2, 0x08 /* Private */,
       9,    0,   57,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,

       0        // eod
};

void ModelManagerView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModelManagerView *_t = static_cast<ModelManagerView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onModelTypeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onCreateModel(); break;
        case 2: _t->onEditModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onDeleteModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onViewModel((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onSearch(); break;
        default: ;
        }
    }
}

const QMetaObject ModelManagerView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ModelManagerView.data,
      qt_meta_data_ModelManagerView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ModelManagerView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModelManagerView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModelManagerView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ModelManagerView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
