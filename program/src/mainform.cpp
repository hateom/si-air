//////////////////////////////////////////////////////////////////////////

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
#include <qpainter.h>

#include "optform.h"
#include "prevform.h"
#include "mp_path.h"
#include "mp_logger.h"
#include "../../modules/module_base/src/status_codes.h"

//////////////////////////////////////////////////////////////////////////

#define FPS( FRM ) (1000/(FRM))

static int poss1[] = 
{
	240, 10,   240+150,  10,   240+300,   10,  
	240, 130,  240+150,  130,  240+300,  130,  
	240, 250,  240+150,  250,  240+300,  250,
	240, 370,  240+150,  370,  240+300,  370
};

static int poss2[] = 
{
	50,     100,
	50+330, 100,
	50+660, 100,
	50+990, 100,
	50,     380,
	50+330, 380,
	50+660, 380,
	50+990, 380,
	50,     660,
	50+330, 660,
	50+660, 660,
	50+990, 660
};

//////////////////////////////////////////////////////////////////////////

MainForm::MainForm( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl ), timer(NULL), prv_wnd(0), is_running(false)
{
    if ( !name )
	setName( "MainForm" );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setGeometry( QRect( 505, 390, 195, 26 ) );

	buttonRun = new QPushButton( this, "buttonRun" );
	buttonRun->setGeometry( QRect( 305, 390, 195, 26 ) );

	listBox = new QListBox( this, "listBox" );
	listBox->setGeometry( QRect( 10, 10, 220, 300 ) );

	buttonAdd= new QPushButton( this, "buttonAdd" );
	buttonAdd->setGeometry( QRect( 10, 320, 220, 26 ) );

	buttonReset = new QPushButton( this, "buttonReset" );
	buttonReset->setGeometry( QRect( 10, 350, 220, 26 ) );

	groupMod = new QGroupBox( this, "groupMod" );
	groupMod->setGeometry( QRect( 240, 10, 460, 370 ) );
	groupMod->setFrameStyle( QFrame::Panel | QFrame::Sunken );

	connect( buttonOk, SIGNAL(clicked()), this, SLOT(close_app()) );
	connect( buttonRun, SIGNAL(clicked()), this, SLOT(run()) );
	connect( buttonAdd, SIGNAL(clicked()), this, SLOT(add_module()) );
	connect( buttonReset, SIGNAL(clicked()), this, SLOT(remove_path()) );
	connect( listBox, SIGNAL(selected(QListBoxItem*)), this, SLOT(lb_selected(QListBoxItem*)) );

    languageChange();
    resize( QSize(710, 425).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::remove_path()
{
	if( is_running )
	{
		LOG( "ERROR: Processing is still running!\n" );
		return;
	}

	for( int i=0; i<(int)mod_widget.size(); ++i )
	{
		mod_widget[i]->close();
		delete mod_widget[i];
	}
	mod_widget.clear();
}

//////////////////////////////////////////////////////////////////////////

void MainForm::close_app()
{
	remove_path();
	close();
}

//////////////////////////////////////////////////////////////////////////

MainForm::~MainForm()
{
	mgr.free();
}

//////////////////////////////////////////////////////////////////////////

void MainForm::languageChange()
{
    setCaption( tr( "SI Module List" ) );
    buttonOk->setText( tr( "Close" ) );
	buttonRun->setText( tr( "Run!" ) );
	buttonAdd->setText( tr( "Add Module" ) );
	buttonReset->setText( tr( "Clear Path" ) );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::add_module()
{
	if( mod_widget.size() == 9 )
	{
		LOG( "ERROR: Maximum modules count is 9!\n" );
		return;
	}

	if( is_running )
	{
		LOG( "ERROR: Processing is still running!\n" );
		return;
	}

	LOG( "adding module %d <%s>\n", listBox->currentItem(), mod_list[listBox->currentItem()]->get_module_description() );

	long id = listBox->currentItem();
	moduleBase * module = mod_list[id];
	modWidget * wdg, * prev;

	if( mod_widget.empty() )
	{
		if( module->input_type() != MT_NONE )
		{
			LOG( "ERROR: This module cannot be used as first processing module!\n" );
			return;
		}
	}
	else
	{
		if( mod_widget[mod_widget.size()-1]->getModule()->output_type() != module->input_type() )
		{
			LOG( "ERROR: Module mismatch error!\n" );
			return;
		}
	}

	prev = mod_widget.size()>0?mod_widget[mod_widget.size()-1]:NULL;
	int wd_no = (int)mod_widget.size();

	wdg = new modWidget( id, module, prev, groupMod, "modWidget" );
	wdg->setGeometry( QRect( poss1[wd_no*2]-230, poss1[wd_no*2+1], 140, 110 ) );

	wdg->show();

	mod_widget.push_back( wdg );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::loadModules( const char * directory )
{
	mgr.read_module_directory( directory );

	for( int i=0; i<mgr.count(); ++i )
	{
		mp_dll_module * mod = mgr.get_module_info( i );
		if( mod )
		{
			mod_list.push_back( mgr.load_module( mod ) );
			listBox->insertItem( tr( mod->description.c_str() ) );
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void MainForm::lb_selected( QListBoxItem * )
{
	add_module();
}

//////////////////////////////////////////////////////////////////////////

void MainForm::process_frame()
{
	int result;
	moduleBase * mod;
	proc_data * arg = NULL, * res = NULL;

	try 
	{
		for( int i=0; i<(int)mod_widget.size(); ++i )
		{
			mod = mod_widget[i]->getModule();
			if( !mod ) throw -1;
			res = mod->process_frame( arg, &result );

			if( result != ST_OK ) 
			{
				stop();
				return;
			}

			if( mod_widget[i]->has_preview() )
			{
				mod_widget[i]->get_preview()->render_frame( res->frame );
			}

			arg = res;
		}
	}
	catch( int err )
	{
		LOG( "ERROR: Internal error <%d>\n", err );
	}
	catch( ... )
	{
		LOG( "ERROR: frame processing exception.\n" );
		release_proc_data();
	}
}

//////////////////////////////////////////////////////////////////////////

void MainForm::run()
{
	int result;
	PrevForm * previous = NULL;

	moduleBase * mod;
	modWidget * wdg;

	property_mgr.release();

	for( int i=0; i<(int)mod_widget.size(); ++i )
	{
		wdg = mod_widget[i];
		mod = wdg->getModule();
		if( !mod ) return;

		result = mod->init( &property_mgr );

		if( result != ST_OK )
		{
			LOG( "ERROR: Initialization module error <%d>!\n", i );
			return;
		}

		if( wdg->has_preview() )
		{
			PrevForm * pf;
			pf = new PrevForm( mod, previous );
			wdg->set_preview( pf );
			pf->move( QPoint( poss2[prv_wnd*2], poss2[prv_wnd*2+1] ) );
			pf->show();
			prv_wnd++;
			previous = pf;
		}
	}

	timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()), this, SLOT(process_frame()));

	is_running = true;
	timer->start( FPS( 25 ) );

	connect( buttonRun, SIGNAL(clicked()), this, SLOT(stop()) );
	disconnect( buttonRun, SIGNAL(clicked()), this, SLOT(run()) );
	buttonRun->setText( "Stop!" );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::stop()
{
	release_proc_data();
}

//////////////////////////////////////////////////////////////////////////

void MainForm::release_proc_data()
{
	if( timer )
	{
		timer->stop();
		delete timer;
		timer = NULL;
	}

	is_running = false;

	prv_wnd = 0;

	modWidget * wdg;

	for( int i=0; i<(int)mod_widget.size(); ++i )
	{
		wdg = mod_widget[i];
		if( wdg->has_preview() )
		{
			wdg->get_preview()->close();
			delete wdg->get_preview();
			wdg->set_preview( NULL );
		}
		wdg->getModule()->free();
	}

	connect( buttonRun, SIGNAL(clicked()), this, SLOT(run()) );
	disconnect( buttonRun, SIGNAL(clicked()), this, SLOT(stop()) );
	buttonRun->setText( "Run!" );
}

//////////////////////////////////////////////////////////////////////////

