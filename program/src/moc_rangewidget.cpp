/****************************************************************************
** rangeWidget meta object code from reading C++ file 'rangewidget.h'
**
** Created: Pn 25. gru 18:32:03 2006
**      by: The Qt MOC ($Id: moc_yacc.cpp,v 1.1.1.13 2006/05/05 17:43:42 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "rangewidget.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *rangeWidget::className() const
{
    return "rangeWidget";
}

QMetaObject *rangeWidget::metaObj = 0;
static QMetaObjectCleanUp cleanUp_rangeWidget( "rangeWidget", &rangeWidget::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString rangeWidget::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "rangeWidget", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString rangeWidget::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "rangeWidget", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* rangeWidget::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QWidget::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "sv", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"slider_changed", 1, param_slot_0 };
    static const QUMethod slot_1 = {"edit_changed", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "slider_changed(int)", &slot_0, QMetaData::Public },
	{ "edit_changed()", &slot_1, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"rangeWidget", parentObject,
	slot_tbl, 2,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_rangeWidget.setMetaObject( metaObj );
    return metaObj;
}

void* rangeWidget::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "rangeWidget" ) )
	return this;
    return QWidget::qt_cast( clname );
}

bool rangeWidget::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: slider_changed((int)static_QUType_int.get(_o+1)); break;
    case 1: edit_changed(); break;
    default:
	return QWidget::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool rangeWidget::qt_emit( int _id, QUObject* _o )
{
    return QWidget::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool rangeWidget::qt_property( int id, int f, QVariant* v)
{
    return QWidget::qt_property( id, f, v);
}

bool rangeWidget::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
