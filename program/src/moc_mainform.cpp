/****************************************************************************
** MainForm meta object code from reading C++ file 'mainform.h'
**
** Created: Cz 28. gru 16:48:22 2006
**      by: The Qt MOC ($Id: moc_yacc.cpp,v 1.1.1.13 2006/05/05 17:43:42 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#undef QT_NO_COMPAT
#include "mainform.h"
#include <qmetaobject.h>
#include <qapplication.h>

#include <private/qucomextra_p.h>
#if !defined(Q_MOC_OUTPUT_REVISION) || (Q_MOC_OUTPUT_REVISION != 26)
#error "This file was generated using the moc from 3.3.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

const char *MainForm::className() const
{
    return "MainForm";
}

QMetaObject *MainForm::metaObj = 0;
static QMetaObjectCleanUp cleanUp_MainForm( "MainForm", &MainForm::staticMetaObject );

#ifndef QT_NO_TRANSLATION
QString MainForm::tr( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainForm", s, c, QApplication::DefaultCodec );
    else
	return QString::fromLatin1( s );
}
#ifndef QT_NO_TRANSLATION_UTF8
QString MainForm::trUtf8( const char *s, const char *c )
{
    if ( qApp )
	return qApp->translate( "MainForm", s, c, QApplication::UnicodeUTF8 );
    else
	return QString::fromUtf8( s );
}
#endif // QT_NO_TRANSLATION_UTF8

#endif // QT_NO_TRANSLATION

QMetaObject* MainForm::staticMetaObject()
{
    if ( metaObj )
	return metaObj;
    QMetaObject* parentObject = QMainWindow::staticMetaObject();
    static const QUParameter param_slot_0[] = {
	{ "base", &static_QUType_ptr, "moduleBase", QUParameter::In },
	{ "no", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_0 = {"module_loaded", 2, param_slot_0 };
    static const QUParameter param_slot_1[] = {
	{ "base", &static_QUType_ptr, "moduleBase", QUParameter::In },
	{ "no", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_1 = {"module_unload", 2, param_slot_1 };
    static const QUParameter param_slot_2[] = {
	{ "base", &static_QUType_ptr, "moduleBase", QUParameter::In },
	{ "no", &static_QUType_int, 0, QUParameter::In }
    };
    static const QUMethod slot_2 = {"added_to_path", 2, param_slot_2 };
    static const QUMethod slot_3 = {"path_cleared", 0, 0 };
    static const QUMethod slot_4 = {"processing_started", 0, 0 };
    static const QUMethod slot_5 = {"processing_finished", 0, 0 };
    static const QUParameter param_slot_6[] = {
	{ "mod", &static_QUType_ptr, "moduleBase", QUParameter::In }
    };
    static const QUMethod slot_6 = {"add_module", 1, param_slot_6 };
    static const QUMethod slot_7 = {"run", 0, 0 };
    static const QUMethod slot_8 = {"stop", 0, 0 };
    static const QUMethod slot_9 = {"close_app", 0, 0 };
    static const QUMethod slot_10 = {"load_modules", 0, 0 };
    static const QUMethod slot_11 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "module_loaded(moduleBase*,int)", &slot_0, QMetaData::Public },
	{ "module_unload(moduleBase*,int)", &slot_1, QMetaData::Public },
	{ "added_to_path(moduleBase*,int)", &slot_2, QMetaData::Public },
	{ "path_cleared()", &slot_3, QMetaData::Public },
	{ "processing_started()", &slot_4, QMetaData::Public },
	{ "processing_finished()", &slot_5, QMetaData::Public },
	{ "add_module(moduleBase*)", &slot_6, QMetaData::Public },
	{ "run()", &slot_7, QMetaData::Public },
	{ "stop()", &slot_8, QMetaData::Public },
	{ "close_app()", &slot_9, QMetaData::Public },
	{ "load_modules()", &slot_10, QMetaData::Public },
	{ "languageChange()", &slot_11, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MainForm", parentObject,
	slot_tbl, 12,
	0, 0,
#ifndef QT_NO_PROPERTIES
	0, 0,
	0, 0,
#endif // QT_NO_PROPERTIES
	0, 0 );
    cleanUp_MainForm.setMetaObject( metaObj );
    return metaObj;
}

void* MainForm::qt_cast( const char* clname )
{
    if ( !qstrcmp( clname, "MainForm" ) )
	return this;
    return QMainWindow::qt_cast( clname );
}

bool MainForm::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: module_loaded((moduleBase*)static_QUType_ptr.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 1: module_unload((moduleBase*)static_QUType_ptr.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 2: added_to_path((moduleBase*)static_QUType_ptr.get(_o+1),(int)static_QUType_int.get(_o+2)); break;
    case 3: path_cleared(); break;
    case 4: processing_started(); break;
    case 5: processing_finished(); break;
    case 6: add_module((moduleBase*)static_QUType_ptr.get(_o+1)); break;
    case 7: run(); break;
    case 8: stop(); break;
    case 9: close_app(); break;
    case 10: load_modules(); break;
    case 11: languageChange(); break;
    default:
	return QMainWindow::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MainForm::qt_emit( int _id, QUObject* _o )
{
    return QMainWindow::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MainForm::qt_property( int id, int f, QVariant* v)
{
    return QMainWindow::qt_property( id, f, v);
}

bool MainForm::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
