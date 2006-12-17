/****************************************************************************
** ModuleMgr meta object code from reading C++ file 'module_mgr.h'
**
** Created: N 17. gru 15:53:12 2006
**      by: The Qt MOC ($Id: moc_yacc.cpp,v 1.1.1.13 2006/05/05 17:43:42 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "module_mgr.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *ModuleMgr::className() const
{
    return "ModuleMgr";
}

QMetaObject *ModuleMgr::metaObj = 0;
static QMetaObjectCleanUp cleanUp_ModuleMgr( "ModuleMgr", &ModuleMgr::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString ModuleMgr::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ModuleMgr", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString ModuleMgr::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "ModuleMgr", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* ModuleMgr::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QObject::staticMetaObject();
    static const QUMethod slot_0 = {"clear_path", 0, 0 };
    static const QUParameter param_slot_1[] = {
	{ "module", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"add_to_path", 1, param_slot_1 };
    static const QUMethod slot_2 = {"start_processing", 0, 0 };
    static const QUMethod slot_3 = {"stop_processing", 0, 0 };
    static const QUMethod slot_4 = {"process_frame", 0, 0 };
    static const QUParameter param_slot_5[] = {
	{ "sx", &static_QUType_int, 0, QUParameter::In },
	{ "sy", &static_QUType_int, 0, QUParameter::In },
	{ "sw", &static_QUType_int, 0, QUParameter::In },
	{ "sh", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_5 = {"mouse_select", 4, param_slot_5 };
    static const QUParameter param_slot_6[] = {
	{ "module", &static_QUType_int, 0, QUParameter::In },
	{ "on", &static_QUType_bool, 0, QUParameter::In }
    };
    static const QUMethod slot_6 = {"switch_preview", 2, param_slot_6 };
    static const QMetaData slot_tbl[] = {
	{ "clear_path()", &slot_0, QMetaData::Public },
	{ "add_to_path(int)", &slot_1, QMetaData::Public },
	{ "start_processing()", &slot_2, QMetaData::Public },
	{ "stop_processing()", &slot_3, QMetaData::Public },
	{ "process_frame()", &slot_4, QMetaData::Public },
	{ "mouse_select(int,int,int,int)", &slot_5, QMetaData::Public },
	{ "switch_preview(int,bool)", &slot_6, QMetaData::Public }
    };
    static const QUParameter param_signal_0[] = {
	{ "base", &static_QUType_ptr, "moduleBase", QUParameter::In },
	{ "no", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_0 = {"module_loaded", 2, param_signal_0 };
    static const QUParameter param_signal_1[] = {
	{ "base", &static_QUType_ptr, "moduleBase", QUParameter::In },
	{ "no", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_1 = {"module_unload", 2, param_signal_1 };
    static const QUParameter param_signal_2[] = {
	{ "base", &static_QUType_ptr, "moduleBase", QUParameter::In },
	{ "no", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod signal_2 = {"added_to_path", 2, param_signal_2 };
    static const QUMethod signal_3 = {"path_cleared", 0, 0 };
    static const QUMethod signal_4 = {"processing_started", 0, 0 };
    static const QUMethod signal_5 = {"processing_finished", 0, 0 };
    static const QMetaData signal_tbl[] = {
	{ "module_loaded(moduleBase*,int)", &signal_0, QMetaData::Public },
	{ "module_unload(moduleBase*,int)", &signal_1, QMetaData::Public },
	{ "added_to_path(moduleBase*,int)", &signal_2, QMetaData::Public },
	{ "path_cleared()", &signal_3, QMetaData::Public },
	{ "processing_started()", &signal_4, QMetaData::Public },
	{ "processing_finished()", &signal_5, QMetaData::Public }
    };
    metaObj = QMetaObject::new_metaobject(
	"ModuleMgr", parentObject,
	slot_tbl, 7,
	signal_tbl, 6,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_ModuleMgr.setMetaObject( metaObj );
    return metaObj;
}

void* ModuleMgr::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "ModuleMgr" ) )
	return this;
    return QObject::qt_cast( clname );
}

#include <qobjectdefs.h>
#include <qsignalslotimp.h>

// SIGNAL module_loaded
void ModuleMgr::module_loaded( moduleBase* t0, int t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 0 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_ptr.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL module_unload
void ModuleMgr::module_unload( moduleBase* t0, int t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 1 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_ptr.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL added_to_path
void ModuleMgr::added_to_path( moduleBase* t0, int t1 )
{
    if ( signalsBlocked() )
	return;
    QConnectionList *clist = receivers( staticMetaObject()->signalOffset() + 2 );
    if ( !clist )
	return;
    QUObject o[3];
    static_QUType_ptr.set(o+1,t0);
    static_QUType_int.set(o+2,t1);
    activate_signal( clist, o );
}

// SIGNAL path_cleared
void ModuleMgr::path_cleared()
{
    activate_signal( staticMetaObject()->signalOffset() + 3 );
}

// SIGNAL processing_started
void ModuleMgr::processing_started()
{
    activate_signal( staticMetaObject()->signalOffset() + 4 );
}

// SIGNAL processing_finished
void ModuleMgr::processing_finished()
{
    activate_signal( staticMetaObject()->signalOffset() + 5 );
}

bool ModuleMgr::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: clear_path(); break;
    case 1: add_to_path((int)static_QUType_int.get(_o+1)); break;
    case 2: start_processing(); break;
    case 3: stop_processing(); break;
    case 4: process_frame(); break;
    case 5: mouse_select((int)static_QUType_int.get(_o+1),(int)static_QUType_int.get(_o+2),(int)static_QUType_int.get(_o+3),(int)static_QUType_int.get(_o+4)); break;
    case 6: switch_preview((int)static_QUType_int.get(_o+1),(bool)static_QUType_bool.get(_o+2)); break;
    default:
	return QObject::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool ModuleMgr::qt_emit( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->signalOffset() ) {
    case 0: module_loaded((moduleBase*)static_QUType_ptr.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 1: module_unload((moduleBase*)static_QUType_ptr.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 2: added_to_path((moduleBase*)static_QUType_ptr.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 3: path_cleared(); break;
    case 4: processing_started(); break;
    case 5: processing_finished(); break;
    default:
	return QObject::qt_emit(_id,_o);
    }
    return TRUE;
}
#ifndef QT_NO_PROPERTIES

bool ModuleMgr::qt_property( int id, int f, QVariant* v)
{
    return QObject::qt_property( id, f, v);
}

bool ModuleMgr::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
