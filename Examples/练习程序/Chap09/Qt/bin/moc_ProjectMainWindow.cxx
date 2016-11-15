/****************************************************************************
** Meta object code from reading C++ file 'ProjectMainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ProjectMainWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ProjectMainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ProjectMainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      36,   32,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ProjectMainWindow[] = {
    "ProjectMainWindow\0\0onOpenSlot()\0obj\0"
    "updateCoords(vtkObject*)\0"
};

void ProjectMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ProjectMainWindow *_t = static_cast<ProjectMainWindow *>(_o);
        switch (_id) {
        case 0: _t->onOpenSlot(); break;
        case 1: _t->updateCoords((*reinterpret_cast< vtkObject*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ProjectMainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ProjectMainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_ProjectMainWindow,
      qt_meta_data_ProjectMainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ProjectMainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ProjectMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ProjectMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ProjectMainWindow))
        return static_cast<void*>(const_cast< ProjectMainWindow*>(this));
    if (!strcmp(_clname, "Ui::ProjectMainWindow"))
        return static_cast< Ui::ProjectMainWindow*>(const_cast< ProjectMainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int ProjectMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
