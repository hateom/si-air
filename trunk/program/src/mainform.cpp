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
#include <qcombobox.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qtimer.h>

#include "optform.h"
#include "prevform.h"
#include "mp_path.h"

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
    buttonOk->setGeometry( QRect( 420, 20, 195, 26 ) );

	buttonRun = new QPushButton( this, "buttonRun" );
	buttonRun->setGeometry( QRect( 420, 50, 195, 26 ) );

	groupBoxVI = new QGroupBox( this, "groupBoxVI" );
	groupBoxVI->setGeometry( QRect( 10, 310, 195, 90 ) );

	comboVI = new QComboBox( groupBoxVI, "comboVI" );
	comboVI->setGeometry( QRect( 10, 20, 175, 25 ) );

	groupBoxPI = new QGroupBox( this, "groupBoxPI" );
	groupBoxPI->setGeometry( QRect( 215, 310, 195, 90 ) );

	comboPI = new QComboBox( groupBoxPI, "comboPI" );
	comboPI->setGeometry( QRect( 10, 20, 175, 25 ) );

	groupBoxPD = new QGroupBox( this, "groupBoxPD" );
	groupBoxPD->setGeometry( QRect( 420, 310, 195, 90 ) );

	comboPD = new QComboBox( groupBoxPD, "comboPD" );
	comboPD->setGeometry( QRect( 10, 20, 175, 25 ) );

	connect( listModule, SIGNAL(selectionChanged(QListBoxItem*)), this, SLOT(selection_changed(QListBoxItem*)) );	
	connect( listModule, SIGNAL(selected(int)), this, SLOT(selected(int)) );	

	connect( buttonOk, SIGNAL(clicked()), this, SLOT(close()) );
	connect( buttonRun, SIGNAL(clicked()), this, SLOT(run()) );

    languageChange();
    resize( QSize(630, 410).expandedTo(minimumSizeHint()) );
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
	groupBoxVI->setTitle( tr( "Video ACQ" ) );
	groupBoxPI->setTitle( tr( "Probability M" ) );
	groupBoxPD->setTitle( tr( "Gestures and Position" ) );
    buttonOk->setText( tr( "OK" ) );
	buttonRun->setText( tr( "Run!" ) );
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
			textModule->insertParagraph( tr( mt_description[ptr->type] ), 1 );
			textModule->insertParagraph( tr( ptr->filename.c_str() ), 2 );
		}
	}
}

void MainForm::selected( int item )
{
	mp_dll_module * mod;

	if( mod = mgr.get_module_info( item ) )
	{
		/*
		if( mod->type != MT_VIDEO_ACQ )
		{
			printf( "Only VIDEO_ACQ module is supported by now." );
			return;
		}
		*/

		vaBase * base;
		base = mgr.load_va_module( mod );
		if( base )
		{
			OptForm * opt_form = new OptForm( 0, 0, TRUE, 0, base );
			opt_form->show();
		}
	}
}

void MainForm::loadModules( const char * directory )
{
	bool found[3] = { false, false, false };

	mgr.read_module_directory( directory );
	for( int i=0; i<mgr.count(); ++i )
	{
		mp_dll_module * mod = mgr.get_module_info( i );
		if( mod )
		{
			listModule->insertItem( tr( mod->filename.c_str() ) );
			switch( mod->type )
			{
			case MT_VIDEO_ACQ:
				comboVI->insertItem( tr( mod->description.c_str() ) );
				va_list.push_back( mod );
				found[0] = true;
				break;
			case MT_PROBABILITY:
				comboPI->insertItem( tr( mod->description.c_str() ) );
				pi_list.push_back( mod );
				found[1] = true;
				break;
			case MT_GESTURES:
				comboPD->insertItem( tr( mod->description.c_str() ) );
				pd_list.push_back( mod );
				found[2] = true;
				break;
			}
		}
	}

	if( !found[0] )
	{
		comboVI->insertItem( tr( "!!! Not Found !!!" ) );
	}

	if( !found[1] )
	{
		comboPI->insertItem( tr( "!!! Not Found !!!") );
	}

	if( !found[2] )
	{
		comboPD->insertItem( tr( "!!! Not Found !!!") );
	}
}

void MainForm::process_frame()
{
	int result;
	frame_data * frame;

	frame = p_data.va_base->process_frame( &result );
	if( result < 0 )
	{
		timer->stop();
		delete timer;
		timer = NULL;
		return;
	}

	// p_data.prevForm->render_frame( frame );

	pi_struct * ps;

	try 
	{
		ps = p_data.pi_base->process_frame( frame, &result );

		printf( "??? " );

		for( int x=0; x<frame->width; ++x )
		{
			for( int y=0; y<frame->height; ++y )
			{
				frame->bits[(x+y*frame->width)*4+0] = (uchar)(ps->prob_table[x+y*frame->width]*256.0f);
				frame->bits[(x+y*frame->width)*4+1] = (uchar)(ps->prob_table[x+y*frame->width]*256.0f);
				frame->bits[(x+y*frame->width)*4+2] = (uchar)(ps->prob_table[x+y*frame->width]*256.0f);
			}
		}
	}
	catch( ... )
	{
		printf( "not good :(\n" );
	}

	p_data.prevForm->render_frame( frame );
}

void MainForm::run()
{
	int va_item, pi_item, pd_item;

	va_item = comboVI->currentItem();
	pi_item = comboPI->currentItem();
	pd_item = comboPD->currentItem();

	p_data.va_base = mgr.load_va_module( va_list[va_item] );
	p_data.pi_base = mgr.load_pi_module( pi_list[va_item] );
	p_data.pd_base = NULL;

	p_data.va_base->init( 0, GETPATH("video.avi"));

	p_data.prevForm = new PrevForm();
	p_data.prevForm->show();

	timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()), this, SLOT(process_frame()));

	timer->start( 10 );
}

