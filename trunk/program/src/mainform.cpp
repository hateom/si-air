/****************************************************************************
** Form implementation generated from reading ui file 'mainform.ui'
**
** Created: Wt 21. lis 13:12:54 2006
**      by: The User Interface Compiler ($Id: main.cpp,v 1.1.1.16 2006/05/05 18:20:12 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "mainform.h"

#include <qvariant.h>
#include <qgroupbox.h>
#include <qtextedit.h>
#include <qlistbox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a MainForm as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
MainForm::MainForm( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "MainForm" );

    groupBox1 = new QGroupBox( this, "groupBox1" );
    groupBox1->setGeometry( QRect( 10, 10, 401, 290 ) );

    textModule = new QTextEdit( groupBox1, "textModule" );
    textModule->setGeometry( QRect( 10, 210, 380, 70 ) );

    listModule = new QListBox( groupBox1, "listModule" );
    listModule->setGeometry( QRect( 10, 20, 380, 180 ) );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setGeometry( QRect( 420, 20, 120, 26 ) );

	connect( listModule, SIGNAL(selectionChanged(QListBoxItem*)), this, SLOT(selection_changed(QListBoxItem*)) );	

    languageChange();
    resize( QSize(547, 307).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
MainForm::~MainForm()
{
	mgr.free();
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MainForm::languageChange()
{
    setCaption( tr( "SI Module List" ) );
    groupBox1->setTitle( tr( "Module List" ) );
    buttonOk->setText( tr( "OK" ) );
}

void MainForm::selection_changed( QListBoxItem * item )
{
	mp_dll_module * ptr;

	for( int i=0; i<mgr.count(); ++i )
	{
		ptr = mgr.get_module_info( i );
		if( strcmp( ptr->filename.c_str(), item->text().ascii() ) == 0 )
		{
			textModule->setText( tr( ptr->description.c_str() ) );
		}
	}
}

void MainForm::loadModules( const char * directory )
{
	mgr.read_module_directory( directory );
	for( int i=0; i<mgr.count(); ++i )
	{
		mp_dll_module * mod = mgr.get_module_info( i );
		if( mod )
		{
			listModule->insertItem( tr( mod->filename.c_str() ) );
		}
		else
		{
			qWarning( "ERROR: Cannot find any modules!\n" );
		}
	}
}

