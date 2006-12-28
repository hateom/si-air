/****************************************************************************
** previewWidget meta object code from reading C++ file 'previewwidget.h'
**
** Created: Cz 28. gru 16:48:23 2006
**      by: The Qt MOC ($Id: moc_yacc.cpp,v 1.1.1.13 2006/05/05 17:43:42 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "previewwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *previewWidget::className() const
{
    return "previewWidget";
}

QMetaObject *previewWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_previewWidget( "previewWidget", &previewWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString previewWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "previewWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString previewWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "previewWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* previewWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUMethod slot_0 = {"on_timer", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "on_timer()", &slot_0, QMetaData::Private }
    };
    metaObj = QMetaObject::new_metaobject(
	"previewWidget", parentObject,
	slot_tbl, 1,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_previewWidget.setMetaObject( metaObj );
    return metaObj;
}

void* previewWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "previewWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool previewWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: on_timer(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool previewWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool previewWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool previewWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
