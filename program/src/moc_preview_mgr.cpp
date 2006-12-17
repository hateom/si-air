/****************************************************************************
** PreviewMgr meta object code from reading C++ file 'preview_mgr.h'
**
** Created: N 17. gru 13:31:39 2006
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
    static const QUParameter param_slot_0[] = {
	{ "sx", &static_QUType_int, 0, QUParameter::In },
	{ "sy", &static_QUType_int, 0, QUParameter::In },
	{ "sw", &static_QUType_int, 0, QUParameter::In },
	{ "sh", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"in_mouse_select", 4, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "in_mouse_select(int,int,int,int)", &slot_0, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "sx", &static_QUType_int, 0, QUParameter::In },
	{ "sy", &static_QUType_int, 0, QUParameter::In },
	{ "sw", &static_QUType_int, 0, QUParameter::In },
	{ "sh", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"mouse_select", 4, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "mouse_select(int,int,int,int)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"PreviewMgr", parentObject,
	slot_tbl, 1,
	signal_tbl, 1,
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

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL mouse_select
void PreviewMgr::mouse_select( int t0, int t1, int t2, int t3 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[5];
    static_QUType_int.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    static_QUType_int.set(o+3,t2);
    static_QUType_int.set(o+4,t3);
    activate_signal( clist, o );
}

bool PreviewMgr::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: in_mouse_select((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2),(int)static_QUType_int.get(_o+3),(int)static_QUType_int.get(_o+4)); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool PreviewMgr::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: mouse_select((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2),(int)static_QUType_int.get(_o+3),(int)static_QUType_int.get(_o+4)); break;
    default:
	return QObject::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool PreviewMgr::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool PreviewMgr::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
