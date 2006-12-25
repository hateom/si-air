/****************************************************************************
** procFrame meta object code from reading C++ file 'processing_panel.h'
**
** Created: N 24. gru 23:07:51 2006
**      by: The Qt MOC ($Id: moc_yacc.cpp,v 1.1.1.13 2006/05/05 17:43:42 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "processing_panel.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *procFrame::className() const
{
    return "procFrame";
}

QMetaObject *procFrame::metaObj = 0;
static QMetaObjectCleanUp cleanUp_procFrame( "procFrame", &procFrame::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString procFrame::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "procFrame", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString procFrame::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "procFrame", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* procFrame::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QFrame::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "id", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"in_popup", 1, param_slot_0 };
    static const QMetaData slot_tbl[] = {
	{ "in_popup(int)", &slot_0, QMetaData::Private }
    };
    static const QUParameter param_signal_0[] = {
	{ "mod", &static_QUType_ptr, "moduleBase", QUParameter::In }
    };
    static const QUMethod signal_0 = {"popup_exe", 1, param_signal_0 };
    static const QMetaData signal_tbl[] = {
	{ "popup_exe(moduleBase*)", &signal_0, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"procFrame", parentObject,
	slot_tbl, 1,
	signal_tbl, 1,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_procFrame.setMetaObject( metaObj );
    return metaObj;
}

void* procFrame::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "procFrame" ) )
	return this;
    return QFrame::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL popup_exe
void procFrame::popup_exe( moduleBase* t0 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[2];
    static_QUType_ptr.set(o+1,t0);
    activate_signal( clist, o );
}

bool procFrame::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: in_popup((int)static_QUType_int.get(_o+1)); break;
    default:
	return QFrame::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool procFrame::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: popup_exe((moduleBase*)static_QUType_ptr.get(_o+1)); break;
    default:
	return QFrame::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool procFrame::qt_property( int id, int f, QVariant* v)
{
    return QFrame::qt_property( id, f, v);
}

bool procFrame::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
