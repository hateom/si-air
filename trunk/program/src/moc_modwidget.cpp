/****************************************************************************
** modWidget meta object code from reading C++ file 'modwidget.h'
**
** Created: N 17. gru 13:41:55 2006
**      by: The Qt MOC ($Id: moc_yacc.cpp,v 1.1.1.13 2006/05/05 17:43:42 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "modwidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *modWidget::className() const
{
    return "modWidget";
}

QMetaObject *modWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_modWidget( "modWidget", &modWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString modWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "modWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString modWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "modWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* modWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QGroupBox::staticMetaObject();
    static const QUMethod slot_0 = {"configure_mod", 0, 0 };
    static const QUMethod slot_1 = {"rm_mod", 0, 0 };
    static const QUMethod slot_2 = {"preview_changed", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "configure_mod()", &slot_0, QMetaData::Public },
	{ "rm_mod()", &slot_1, QMetaData::Public },
	{ "preview_changed()", &slot_2, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"modWidget", parentObject,
	slot_tbl, 3,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_modWidget.setMetaObject( metaObj );
    return metaObj;
}

void* modWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "modWidget" ) )
	return this;
    return QGroupBox::qt_cast( clname );
}

bool modWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: configure_mod(); break;
    case 1: rm_mod(); break;
    case 2: preview_changed(); break;
    default:
	return QGroupBox::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool modWidget::qt_emit( int _id, QUObject* _o )
{
    return QGroupBox::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool modWidget::qt_property( int id, int f, QVariant* v)
{
    return QGroupBox::qt_property( id, f, v);
}

bool modWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
