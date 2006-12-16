/****************************************************************************
** PreviewMgr meta object code from reading C++ file 'preview_mgr.h'
**
** Created: So 16. gru 22:34:52 2006
**      by: The Qt MOC ($Id: moc_yacc.cpp,v 1.1.1.13 2006/05/05 17:43:42 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "preview_mgr.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *PreviewMgr::className() const
{
    return "PreviewMgr";
}

QMetaObject *PreviewMgr::metaObj = 0;
static QMetaObjectCleanUp cleanUp_PreviewMgr( "PreviewMgr", &PreviewMgr::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString PreviewMgr::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PreviewMgr", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString PreviewMgr::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "PreviewMgr", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* PreviewMgr::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    metaObj = QMetaObject::new_metaobject(
	"PreviewMgr", parentObject,
	0, 0,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_PreviewMgr.setMetaObject( metaObj );
    return metaObj;
}

void* PreviewMgr::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "PreviewMgr" ) )
	return this;
    return QObject::qt_cast( clname );
}

bool PreviewMgr::qt_invoke( int _id, QUObject* _o )
{
    return QObject::qt_invoke(_id,_o);
}

bool PreviewMgr::qt_emit( int _id, QUObject* _o )
{
    return QObject::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool PreviewMgr::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool PreviewMgr::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
