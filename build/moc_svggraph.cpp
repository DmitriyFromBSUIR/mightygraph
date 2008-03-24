/****************************************************************************
** Meta object code from reading C++ file 'svggraph.h'
**
** Created: Mon Mar 24 12:02:46 2008
**      by: The Qt Meta Object Compiler version 59 (Qt 4.3.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/svggraph.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'svggraph.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 59
#error "This file was generated using the moc from 4.3.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

static const uint qt_meta_data_SvgGraph[] = {

 // content:
       1,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   10, // methods
       0,    0, // properties
       0,    0, // enums/sets

 // slots: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_SvgGraph[] = {
    "SvgGraph\0\0open()\0"
};

const QMetaObject SvgGraph::staticMetaObject = {
    { &QSvgWidget::staticMetaObject, qt_meta_stringdata_SvgGraph,
      qt_meta_data_SvgGraph, 0 }
};

const QMetaObject *SvgGraph::metaObject() const
{
    return &staticMetaObject;
}

void *SvgGraph::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_SvgGraph))
	return static_cast<void*>(const_cast< SvgGraph*>(this));
    return QSvgWidget::qt_metacast(_clname);
}

int SvgGraph::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSvgWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: open(); break;
        }
        _id -= 1;
    }
    return _id;
}
