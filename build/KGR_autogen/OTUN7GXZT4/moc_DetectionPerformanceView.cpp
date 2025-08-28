/****************************************************************************
** Meta object code from reading C++ file 'DetectionPerformanceView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../view/DetectionPerformanceView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DetectionPerformanceView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DetectionPerformanceView_t {
    QByteArrayData data[20];
    char stringdata0[378];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DetectionPerformanceView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DetectionPerformanceView_t qt_meta_stringdata_DetectionPerformanceView = {
    {
QT_MOC_LITERAL(0, 0, 24), // "DetectionPerformanceView"
QT_MOC_LITERAL(1, 25, 18), // "onConditionChanged"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 5), // "index"
QT_MOC_LITERAL(4, 51, 13), // "onSelectRadar"
QT_MOC_LITERAL(5, 65, 14), // "onSelectJammer"
QT_MOC_LITERAL(6, 80, 14), // "onSelectTarget"
QT_MOC_LITERAL(7, 95, 10), // "onEvaluate"
QT_MOC_LITERAL(8, 106, 16), // "showRadarDetails"
QT_MOC_LITERAL(9, 123, 17), // "showJammerDetails"
QT_MOC_LITERAL(10, 141, 17), // "showTargetDetails"
QT_MOC_LITERAL(11, 159, 27), // "onFormationConditionChanged"
QT_MOC_LITERAL(12, 187, 22), // "onSelectFormationRadar"
QT_MOC_LITERAL(13, 210, 19), // "onAddFormationRadar"
QT_MOC_LITERAL(14, 230, 23), // "onSelectFormationJammer"
QT_MOC_LITERAL(15, 254, 23), // "onSelectFormationTarget"
QT_MOC_LITERAL(16, 278, 19), // "onFormationEvaluate"
QT_MOC_LITERAL(17, 298, 25), // "showFormationRadarDetails"
QT_MOC_LITERAL(18, 324, 26), // "showFormationJammerDetails"
QT_MOC_LITERAL(19, 351, 26) // "showFormationTargetDetails"

    },
    "DetectionPerformanceView\0onConditionChanged\0"
    "\0index\0onSelectRadar\0onSelectJammer\0"
    "onSelectTarget\0onEvaluate\0showRadarDetails\0"
    "showJammerDetails\0showTargetDetails\0"
    "onFormationConditionChanged\0"
    "onSelectFormationRadar\0onAddFormationRadar\0"
    "onSelectFormationJammer\0onSelectFormationTarget\0"
    "onFormationEvaluate\0showFormationRadarDetails\0"
    "showFormationJammerDetails\0"
    "showFormationTargetDetails"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DetectionPerformanceView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x08 /* Private */,
       4,    0,  102,    2, 0x08 /* Private */,
       5,    0,  103,    2, 0x08 /* Private */,
       6,    0,  104,    2, 0x08 /* Private */,
       7,    0,  105,    2, 0x08 /* Private */,
       8,    0,  106,    2, 0x08 /* Private */,
       9,    0,  107,    2, 0x08 /* Private */,
      10,    0,  108,    2, 0x08 /* Private */,
      11,    1,  109,    2, 0x08 /* Private */,
      12,    0,  112,    2, 0x08 /* Private */,
      13,    0,  113,    2, 0x08 /* Private */,
      14,    0,  114,    2, 0x08 /* Private */,
      15,    0,  115,    2, 0x08 /* Private */,
      16,    0,  116,    2, 0x08 /* Private */,
      17,    0,  117,    2, 0x08 /* Private */,
      18,    0,  118,    2, 0x08 /* Private */,
      19,    0,  119,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DetectionPerformanceView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DetectionPerformanceView *_t = static_cast<DetectionPerformanceView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onConditionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onSelectRadar(); break;
        case 2: _t->onSelectJammer(); break;
        case 3: _t->onSelectTarget(); break;
        case 4: _t->onEvaluate(); break;
        case 5: _t->showRadarDetails(); break;
        case 6: _t->showJammerDetails(); break;
        case 7: _t->showTargetDetails(); break;
        case 8: _t->onFormationConditionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onSelectFormationRadar(); break;
        case 10: _t->onAddFormationRadar(); break;
        case 11: _t->onSelectFormationJammer(); break;
        case 12: _t->onSelectFormationTarget(); break;
        case 13: _t->onFormationEvaluate(); break;
        case 14: _t->showFormationRadarDetails(); break;
        case 15: _t->showFormationJammerDetails(); break;
        case 16: _t->showFormationTargetDetails(); break;
        default: ;
        }
    }
}

const QMetaObject DetectionPerformanceView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_DetectionPerformanceView.data,
      qt_meta_data_DetectionPerformanceView,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DetectionPerformanceView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DetectionPerformanceView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DetectionPerformanceView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DetectionPerformanceView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
