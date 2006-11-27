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
#include <qfiledialog.h>
#include <qcheckbox.h>

#include "optform.h"
#include "prevform.h"
#include "mp_path.h"
#include "../../modules/module_base/src/status_codes.h"

/*
 *  Constructs a MainForm as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
MainForm::MainForm( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl ), timer(NULL)
{
    if ( !name )
	setName( "MainForm" );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setGeometry( QRect( 420, 160, 195, 26 ) );

	buttonRun = new QPushButton( this, "buttonRun" );
	buttonRun->setGeometry( QRect( 10, 160, 195, 26 ) );

	groupBoxVI = new QGroupBox( this, "groupBoxVI" );
	groupBoxVI->setGeometry( QRect( 10, 10, 195, 130 ) );

	comboVI = new QComboBox( groupBoxVI, "comboVI" );
	comboVI->setGeometry( QRect( 10, 20, 175, 25 ) );

	checkVI = new QCheckBox( groupBoxVI, "checkVI" );
	checkVI->setGeometry( QRect( 10, 50, 85, 25 ) );
	checkVI->setChecked( true );

	checkAvi = new QCheckBox( groupBoxVI, "checkAvi" );
	checkAvi->setGeometry( QRect( 100, 50, 85, 25 ) );
	checkAvi->setChecked( true );

	groupBoxPI = new QGroupBox( this, "groupBoxPI" );
	groupBoxPI->setGeometry( QRect( 215, 10, 195, 130 ) );

	comboPI = new QComboBox( groupBoxPI, "comboPI" );
	comboPI->setGeometry( QRect( 10, 20, 175, 25 ) );

	checkPI = new QCheckBox( groupBoxPI, "checkPI" );
	checkPI->setGeometry( QRect( 10, 50, 175, 25 ) );
	checkPI->setChecked( true );

	groupBoxPD = new QGroupBox( this, "groupBoxPD" );
	groupBoxPD->setGeometry( QRect( 420, 10, 195, 130 ) );

	comboPD = new QComboBox( groupBoxPD, "comboPD" );
	comboPD->setGeometry( QRect( 10, 20, 175, 25 ) );

	checkPD = new QCheckBox( groupBoxPD, "checkPD" );
	checkPD->setGeometry( QRect( 10, 50, 175, 25 ) );
	checkPD->setChecked( false );

	buttonVIcfg = new QPushButton( groupBoxVI, "buttonVIcfg" );
	buttonVIcfg->setGeometry( QRect( 10, 80, 175, 26 ) );

	buttonPIcfg = new QPushButton( groupBoxPI, "buttonPIcfg" );
	buttonPIcfg->setGeometry( QRect( 10, 80, 175, 26 ) );

	buttonPDcfg = new QPushButton( groupBoxPD, "buttonPDcfg" );
	buttonPDcfg->setGeometry( QRect( 10, 80, 175, 26 ) );

	connect( buttonVIcfg, SIGNAL(clicked()), this, SLOT(configure_va_mod()) );
	connect( buttonPIcfg, SIGNAL(clicked()), this, SLOT(configure_pi_mod()) );
	connect( buttonPDcfg, SIGNAL(clicked()), this, SLOT(configure_pd_mod()) );

	memset( &p_data, 0, sizeof(processing_data) );

	connect( buttonOk, SIGNAL(clicked()), this, SLOT(close_app()) );
	connect( buttonRun, SIGNAL(clicked()), this, SLOT(run()) );

    languageChange();
    resize( QSize(630, 200).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

void MainForm::close_app()
{
	release_proc_data( &p_data );
	close();
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
	groupBoxVI->setTitle( tr( "Video ACQ" ) );
	groupBoxPI->setTitle( tr( "Probability M" ) );
	groupBoxPD->setTitle( tr( "Gestures and Position" ) );
    buttonOk->setText( tr( "OK" ) );
	buttonRun->setText( tr( "Run!" ) );

	checkVI->setText( tr("Preview") );
	checkPI->setText( tr("Preview") );
	checkPD->setText( tr("Preview") );

	checkAvi->setText( tr("From File") );

	buttonVIcfg->setText( tr("Configure") );
	buttonPIcfg->setText( tr("Configure") );
	buttonPDcfg->setText( tr("Configure") );
}

void MainForm::configure_va_mod()
{
	OptForm * opt_form;

	opt_form = new OptForm( 0, 0, TRUE, 0, va_list[comboVI->currentItem()] );
	opt_form->show();
}

void MainForm::configure_pi_mod()
{
	OptForm * opt_form;

	opt_form = new OptForm( 0, 0, TRUE, 0, pi_list[comboPI->currentItem()] );
	opt_form->show();
}

void MainForm::configure_pd_mod()
{
	OptForm * opt_form;

	opt_form = new OptForm( 0, 0, TRUE, 0, pd_list[comboPD->currentItem()] );
	opt_form->show();
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
//			listModule->insertItem( tr( mod->filename.c_str() ) );
			switch( mod->type )
			{
			case MT_VIDEO_ACQ:
				comboVI->insertItem( tr( mod->description.c_str() ) );
				va_list.push_back( mgr.load_va_module( mod ) );
				found[0] = true;
				break;
			case MT_PROBABILITY:
				comboPI->insertItem( tr( mod->description.c_str() ) );
				pi_list.push_back( mgr.load_pi_module( mod ) );
				found[1] = true;
				break;
			case MT_GESTURES:
				comboPD->insertItem( tr( mod->description.c_str() ) );
				pd_list.push_back( mgr.load_pd_module( mod ) );
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
	if( result != ST_OK )
	{
		release_proc_data( &p_data );
		return;
	}

	// p_data.prevForm->render_frame( frame );

	pi_struct * ps;

	try 
	{
		ps = p_data.pi_base->process_frame( frame, &result );
	}
	catch( ... )
	{
		printf( "not good :(\n" );
	}

	if( p_data.prevForm1 ) p_data.prevForm1->render_frame( frame );
	if( p_data.prevForm2 ) p_data.prevForm2->render_frame( ps->frame );
}

void MainForm::run()
{
	int va_item, pi_item, pd_item;
	int result;

	va_item = comboVI->currentItem();
	pi_item = comboPI->currentItem();
	pd_item = comboPD->currentItem();

	p_data.va_base = va_list[va_item];
	p_data.pi_base = pi_list[va_item];
	p_data.pd_base = NULL;

	QFileDialog* fd = new QFileDialog( this, "file dialog", TRUE );
	fd->setMode( QFileDialog::AnyFile );

	if( checkAvi->isChecked() )
	{
		QString s = QFileDialog::getOpenFileName(
			NULL,
			"Videos (*.avi *.mpg *.mpeg)",
			this,
			"open file dialog"
			"Choose a file" );

		result = p_data.va_base->init( 0, (char *)s.ascii() );
		if( result != ST_OK )
		{
			printf( "Could not render media file.\n" );
			return;
		}
	}
	else
	{
		result = p_data.va_base->init( 0, 0 );
		if( result != ST_OK )
		{
			printf( "Video Device not found.\n" );
			return;
		}
	}

	if( checkVI->isChecked() )
	{
		p_data.prevForm1 = new PrevForm();
		p_data.prevForm1->show();
		p_data.prevForm1->move( QPoint( 100, 100 ) );
	}

	if( checkPI->isChecked() )
	{
		p_data.prevForm2 = new PrevForm();
		p_data.prevForm2->show();
		p_data.prevForm2->move( QPoint( 500, 100 ) );
	}

	timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()), this, SLOT(process_frame()));

	timer->start( 4 );

	connect( buttonRun, SIGNAL(clicked()), this, SLOT(stop()) );
	disconnect( buttonRun, SIGNAL(clicked()), this, SLOT(run()) );
	buttonRun->setText( "Stop!" );
}

void MainForm::stop()
{
	release_proc_data( &p_data );
}

void MainForm::release_proc_data( processing_data * data )
{
	if( !data ) return;

	if( timer )
	{
		timer->stop();
		delete timer;
		timer = NULL;
	}

	if( data->va_base )
	{
		data->va_base->free();
//		delete data->va_base;
		data->va_base = NULL;
	}

	if( data->pi_base )
	{
		data->pi_base->free();
//		delete data->pi_base;
		data->pi_base = NULL;
	}

	if( data->pd_base )
	{
		data->pd_base->free();
//		delete data->pd_base;
		data->pd_base = NULL;
	}

	if( data->prevForm1 )
	{
		data->prevForm1->close();
		delete data->prevForm1;
		data->prevForm1 = NULL;
	}

	if( data->prevForm2 )
	{
		data->prevForm2->close();
		delete data->prevForm2;
		data->prevForm2 = NULL;
	}

	connect( buttonRun, SIGNAL(clicked()), this, SLOT(run()) );
	disconnect( buttonRun, SIGNAL(clicked()), this, SLOT(stop()) );
	buttonRun->setText( "Run!" );
}

