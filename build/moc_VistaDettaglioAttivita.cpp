/****************************************************************************
** Meta object code from reading C++ file 'VistaDettaglioAttivita.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../gui/VistaDettaglioAttivita.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'VistaDettaglioAttivita.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_VistaDettaglioAttivita_t {
    uint offsetsAndSizes[18];
    char stringdata0[23];
    char stringdata1[14];
    char stringdata2[1];
    char stringdata3[3];
    char stringdata4[16];
    char stringdata5[14];
    char stringdata6[7];
    char stringdata7[9];
    char stringdata8[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_VistaDettaglioAttivita_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_VistaDettaglioAttivita_t qt_meta_stringdata_VistaDettaglioAttivita = {
    {
        QT_MOC_LITERAL(0, 22),  // "VistaDettaglioAttivita"
        QT_MOC_LITERAL(23, 13),  // "editRequested"
        QT_MOC_LITERAL(37, 0),  // ""
        QT_MOC_LITERAL(38, 2),  // "id"
        QT_MOC_LITERAL(41, 15),  // "deleteRequested"
        QT_MOC_LITERAL(57, 13),  // "backRequested"
        QT_MOC_LITERAL(71, 6),  // "onEdit"
        QT_MOC_LITERAL(78, 8),  // "onDelete"
        QT_MOC_LITERAL(87, 6)   // "onBack"
    },
    "VistaDettaglioAttivita",
    "editRequested",
    "",
    "id",
    "deleteRequested",
    "backRequested",
    "onEdit",
    "onDelete",
    "onBack"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_VistaDettaglioAttivita[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   50,    2, 0x06,    1 /* Public */,
       4,    1,   53,    2, 0x06,    3 /* Public */,
       5,    0,   56,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       6,    0,   57,    2, 0x08,    6 /* Private */,
       7,    0,   58,    2, 0x08,    7 /* Private */,
       8,    0,   59,    2, 0x08,    8 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void, QMetaType::UInt,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject VistaDettaglioAttivita::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_VistaDettaglioAttivita.offsetsAndSizes,
    qt_meta_data_VistaDettaglioAttivita,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_VistaDettaglioAttivita_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<VistaDettaglioAttivita, std::true_type>,
        // method 'editRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned int, std::false_type>,
        // method 'deleteRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<unsigned int, std::false_type>,
        // method 'backRequested'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onEdit'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onDelete'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'onBack'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void VistaDettaglioAttivita::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VistaDettaglioAttivita *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->editRequested((*reinterpret_cast< std::add_pointer_t<uint>>(_a[1]))); break;
        case 1: _t->deleteRequested((*reinterpret_cast< std::add_pointer_t<uint>>(_a[1]))); break;
        case 2: _t->backRequested(); break;
        case 3: _t->onEdit(); break;
        case 4: _t->onDelete(); break;
        case 5: _t->onBack(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VistaDettaglioAttivita::*)(unsigned int );
            if (_t _q_method = &VistaDettaglioAttivita::editRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (VistaDettaglioAttivita::*)(unsigned int );
            if (_t _q_method = &VistaDettaglioAttivita::deleteRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (VistaDettaglioAttivita::*)();
            if (_t _q_method = &VistaDettaglioAttivita::backRequested; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
    }
}

const QMetaObject *VistaDettaglioAttivita::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VistaDettaglioAttivita::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VistaDettaglioAttivita.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "AttivitaConstVisitor"))
        return static_cast< AttivitaConstVisitor*>(this);
    return QWidget::qt_metacast(_clname);
}

int VistaDettaglioAttivita::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void VistaDettaglioAttivita::editRequested(unsigned int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void VistaDettaglioAttivita::deleteRequested(unsigned int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void VistaDettaglioAttivita::backRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
