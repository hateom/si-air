/****************************************************************************
** myButton meta object code from reading C++ file 'my_button.h'
**
** Created: ?r 3. sty 23:00:18 2007
**      by: The Qt MOC ($Id: moc_yacc.cpp,v 1.1.1.13 2006/05/05 17:43:42 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "my_button.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *myButton::className() const
{
    return "myButton";
}

QMetaObject *myButton::metaObj = 0;
static QMetaObjectCleanUp cleanUp_myButton( "myButton", &myButton::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString myButton::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "myButton", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString myButton::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "myButton", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* myButton::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QPushButton::staticMetaObject();
    static const QUMethod slot_0 = {"on_click", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "on_click()", &slot_0, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "id", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"clicked", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "clicked(int)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"myButton", parentObject,
	slot_tbl, 1,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_myButton.setMetaObject( metaObj );
    return metaObj;
}

void* myButton::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "myButton" ) )
	return this;
    return QPushButton::qt_cast( clname );
}

// SIGNAL clicked
void myButton::clicked( int t0 )
{
    activate_signal( staticMetaObject()->signalOffset() + 0, t0 );
}

bool myButton::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: on_click(); break;
    default:
	return QPushButton::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool myButton::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: clicked((int)static_QUType_int.get(_o+1)); break;
    default:
	return QPushButton::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool myButton::qt_property( int id, int f, QVariant* v)
{
    return QPushButton::qt_property( id, f, v);
}

bool myButton::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
