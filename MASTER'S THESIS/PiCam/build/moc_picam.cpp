/****************************************************************************
** Meta object code from reading C++ file 'picam.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DP/picam.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'picam.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Picam_t {
    QByteArrayData data[16];
    char stringdata[132];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Picam_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Picam_t qt_meta_stringdata_Picam = {
    {
QT_MOC_LITERAL(0, 0, 5),
QT_MOC_LITERAL(1, 6, 9),
QT_MOC_LITERAL(2, 16, 4),
QT_MOC_LITERAL(3, 21, 2),
QT_MOC_LITERAL(4, 24, 5),
QT_MOC_LITERAL(5, 30, 8),
QT_MOC_LITERAL(6, 39, 6),
QT_MOC_LITERAL(7, 46, 6),
QT_MOC_LITERAL(8, 53, 8),
QT_MOC_LITERAL(9, 62, 11),
QT_MOC_LITERAL(10, 74, 11),
QT_MOC_LITERAL(11, 86, 5),
QT_MOC_LITERAL(12, 92, 4),
QT_MOC_LITERAL(13, 97, 10),
QT_MOC_LITERAL(14, 108, 10),
QT_MOC_LITERAL(15, 119, 12)
    },
    "Picam\0colEffect\0None\0BW\0Sepia\0Negative\0"
    "Emboss\0Sketch\0Sky_Blue\0Grass_Green\0"
    "Skin_Whiten\0Vivid\0Aqua\0Art_Freeze\0"
    "Silhouette\0Solarization"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Picam[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       1,   14, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data
       1, 0x0,   14,   18,

 // enum data: key, value
       2, uint(Picam::None),
       3, uint(Picam::BW),
       4, uint(Picam::Sepia),
       5, uint(Picam::Negative),
       6, uint(Picam::Emboss),
       7, uint(Picam::Sketch),
       8, uint(Picam::Sky_Blue),
       9, uint(Picam::Grass_Green),
      10, uint(Picam::Skin_Whiten),
      11, uint(Picam::Vivid),
      12, uint(Picam::Aqua),
      13, uint(Picam::Art_Freeze),
      14, uint(Picam::Silhouette),
      15, uint(Picam::Solarization),

       0        // eod
};

void Picam::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

const QMetaObject Picam::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Picam.data,
      qt_meta_data_Picam,  qt_static_metacall, 0, 0}
};


const QMetaObject *Picam::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Picam::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Picam.stringdata))
        return static_cast<void*>(const_cast< Picam*>(this));
    return QObject::qt_metacast(_clname);
}

int Picam::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
