/****************************************************************************
** MainForm meta object code from reading C++ file 'mainform.h'
**
** Created: Pn 27. lis 00:37:28 2006
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
    QMetaObject* parentObject = QDialog::staticMetaObject();
    static const QUMethod slot_0 = {"run", 0, 0 };
    static const QUMethod slot_1 = {"stop", 0, 0 };
    static const QUMethod slot_2 = {"process_frame", 0, 0 };
    static const QUMethod slot_3 = {"close_app", 0, 0 };
    static const QUMethod slot_4 = {"configure_va_mod", 0, 0 };
    static const QUMethod slot_5 = {"configure_pi_mod", 0, 0 };
    static const QUMethod slot_6 = {"configure_pd_mod", 0, 0 };
    static const QUMethod slot_7 = {"languageChange", 0, 0 };
    static const QMetaData slot_tbl[] = {
	{ "run()", &slot_0, QMetaData::Public },
	{ "stop()", &slot_1, QMetaData::Public },
	{ "process_frame()", &slot_2, QMetaData::Public },
	{ "close_app()", &slot_3, QMetaData::Public },
	{ "configure_va_mod()", &slot_4, QMetaData::Public },
	{ "configure_pi_mod()", &slot_5, QMetaData::Public },
	{ "configure_pd_mod()", &slot_6, QMetaData::Public },
	{ "languageChange()", &slot_7, QMetaData::Protected }
    };
    metaObj = QMetaObject::new_metaobject(
	"MainForm", parentObject,
	slot_tbl, 8,
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
    return QDialog::qt_cast( clname );
}

bool MainForm::qt_invoke( int _id, QUObject* _o )
{
    switch ( _id - staticMetaObject()->slotOffset() ) {
    case 0: run(); break;
    case 1: stop(); break;
    case 2: process_frame(); break;
    case 3: close_app(); break;
    case 4: configure_va_mod(); break;
    case 5: configure_pi_mod(); break;
    case 6: configure_pd_mod(); break;
    case 7: languageChange(); break;
    default:
	return QDialog::qt_invoke( _id, _o );
    }
    return TRUE;
}

bool MainForm::qt_emit( int _id, QUObject* _o )
{
    return QDialog::qt_emit(_id,_o);
}
#ifndef QT_NO_PROPERTIES

bool MainForm::qt_property( int id, int f, QVariant* v)
{
    return QDialog::qt_property( id, f, v);
}

bool MainForm::qt_static_property( QObject* , int , int , QVariant* ){ return FALSE; }
#endif // QT_NO_PROPERTIES
