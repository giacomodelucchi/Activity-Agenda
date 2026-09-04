/****************************************************************************
** Meta object code from reading C++ file 'VistaElencoAttivita.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../gui/VistaElencoAttivita.h"
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VistaElencoAttivita.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_VistaElencoAttivita_t {
    uint offsetsAndSizes[38];
    char stringdata0[20];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[3];
    char stringdata4[24];
    char stringdata5[12];
    char stringdata6[4];
    char stringdata7[13];
    char stringdata8[5];
    char stringdata9[14];
    char stringdata10[17];
    char stringdata11[5];
    char stringdata12[7];
    char stringdata13[20];
    char stringdata14[5];
    char stringdata15[17];
    char stringdata16[15];
    char stringdata17[17];
    char stringdata18[13];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_VistaElencoAttivita_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_VistaElencoAttivita_t qt_meta_stringdata_VistaElencoAttivita = {
    {
        QT_MOC_LITERAL(0, 19),  // "VistaElencoAttivita"
        QT_MOC_LITERAL(20, 16),  // "activitySelected"
        QT_MOC_LITERAL(37, 0),  // ""
        QT_MOC_LITERAL(38, 2),  // "id"
        QT_MOC_LITERAL(41, 23),  // "deleteSelectedRequested"
        QT_MOC_LITERAL(65, 11),  // "QList<uint>"
        QT_MOC_LITERAL(77, 3),  // "ids"
        QT_MOC_LITERAL(81, 12),  // "addRequested"
        QT_MOC_LITERAL(94, 4),  // "type"
        QT_MOC_LITERAL(99, 13),  // "onItemClicked"
        QT_MOC_LITERAL(113, 16),  // "QTreeWidgetItem*"
        QT_MOC_LITERAL(130, 4),  // "item"
        QT_MOC_LITERAL(135, 6),  // "column"
        QT_MOC_LITERAL(142, 19),  // "onSearchTextChanged"
        QT_MOC_LITERAL(162, 4),  // "text"
        QT_MOC_LITERAL(167, 16),  // "onDeleteSelected"
        QT_MOC_LITERAL(184, 14),  // "onAddRequested"
        QT_MOC_LITERAL(199, 16),  // "updateVisibility"
        QT_MOC_LITERAL(216, 12)   // "visibleCount"
    },
    "VistaElencoAttivita",
    "activitySelected",
    "",
    "id",
    "deleteSelectedRequested",
    "QList<uint>",
    "ids",
    "addRequested",
    "type",
    "onItemClicked",
    "QTreeWidgetItem*",
    "item",
    "column",
    "onSearchTextChanged",
    "text",
    "onDeleteSelected",
    "onAddRequested",
    "updateVisibility",
    "visibleCount"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_VistaElencoAttivita[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   62,    2, 0x06,    1 /* Public */,
       4,    1,   65,    2, 0x06,    3 /* Public */,
       7,    1,   68,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       9,    2,   71,    2, 0x08,    7 /* Private */,
      13,    1,   76,    2, 0x08,   10 /* Private */,
      15,    0,   79,    2, 0x08,   12 /* Private */,
      16,    1,   80,    2, 0x08,   13 /* Private */,
      17,    1,   83,    2, 0x08,   15 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Int,    8,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int,   11,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   18,

       0        // eod
};

Q_CONSTINIT const QMetaObject VistaElencoAttivita::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_VistaElencoAttivita.offsetsAndSizes,
    qt_meta_data_VistaElencoAttivita,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_VistaElencoAttivita_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<VistaElencoAttivita, std::true_type>,
        // method 'activitySelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned int, std::false_type>,
        // method 'deleteSelectedRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QVector<unsigned int> &, std::false_type>,
        // method 'addRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onItemClicked'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'onSearchTextChanged'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'onDeleteSelected'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onAddRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'updateVisibility'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void VistaElencoAttivita::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VistaElencoAttivita *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->activitySelected((*reinterpret_cast< std::add_pointer_t<uint>>(_a[1]))); break;
        case 1: _t->deleteSelectedRequested((*reinterpret_cast< std::add_pointer_t<QList<uint>>>(_a[1]))); break;
        case 2: _t->addRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->onItemClicked((*reinterpret_cast< std::add_pointer_t<QTreeWidgetItem*>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 4: _t->onSearchTextChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->onDeleteSelected(); break;
        case 6: _t->onAddRequested((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 7: _t->updateVisibility((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QList<uint> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VistaElencoAttivita::*)(unsigned int );
            if (_t _q_method = &VistaElencoAttivita::activitySelected; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VistaElencoAttivita::*)(const QVector<unsigned int> & );
            if (_t _q_method = &VistaElencoAttivita::deleteSelectedRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VistaElencoAttivita::*)(int );
            if (_t _q_method = &VistaElencoAttivita::addRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *VistaElencoAttivita::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VistaElencoAttivita::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VistaElencoAttivita.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "AttivitaConstVisitor"))
        return static_cast< AttivitaConstVisitor*>(this);
    return QWidget::qt_metacast(_clname);
}

int VistaElencoAttivita::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void VistaElencoAttivita::activitySelected(unsigned int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VistaElencoAttivita::deleteSelectedRequested(const QVector<unsigned int> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VistaElencoAttivita::addRequested(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
