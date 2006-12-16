/****************************************************************************
** fnWidget meta object code from reading C++ file 'fnwidget.h'
**
** Created: N 3. gru 18:50:29 2006
**      by: The Qt MOC ($Id: moc_yacc.cpp,v 1.1.1.13 2006/05/05 17:43:42 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "fnwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *fnWidget::className() const
{
    return "fnWidget";
}

QMetaObject *fnWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_fnWidget( "fnWidget", &fnWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString fnWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "fnWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString fnWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "fnWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* fnWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"select_file", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "select_file()", &slot_0, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"fnWidget", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_fnWidget.setMetaObject( metaObj );
    return metaObj;
}

void* fnWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "fnWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool fnWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: select_file(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool fnWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool fnWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool fnWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
