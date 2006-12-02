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

#include "optform.h"
#include "prevform.h"
#include "mp_path.h"
#include "mp_logger.h"
#include "../../modules/module_base/src/status_codes.h"

//////////////////////////////////////////////////////////////////////////

MainForm::MainForm( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl ), timer(NULL)
{
    if ( !name )
	setName( "MainForm" );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setGeometry( QRect( 420, 460, 195, 26 ) );

	buttonRun = new QPushButton( this, "buttonRun" );
	buttonRun->setGeometry( QRect( 10, 460, 195, 26 ) );

	listBox = new QListBox( this, "listBox" );
	listBox->setGeometry( QRect( 10, 10, 220, 300 ) );

	buttonAdd= new QPushButton( this, "buttonAdd" );
	buttonAdd->setGeometry( QRect( 10, 320, 220, 26 ) );

	connect( buttonOk, SIGNAL(clicked()), this, SLOT(close_app()) );
	connect( buttonRun, SIGNAL(clicked()), this, SLOT(run()) );
	connect( buttonAdd, SIGNAL(clicked()), this, SLOT(add_module()) );

    languageChange();
    resize( QSize(700, 500).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::close_app()
{
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
    buttonOk->setText( tr( "OK" ) );
	buttonRun->setText( tr( "Run!" ) );
	buttonAdd->setText( tr( "Add Module" ) );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::add_module()
{
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

	int start_x = 240;
	int wd_no = (int)mod_widget.size();

	wdg = new modWidget( id, module, prev, this, "modWidget" );
	wdg->setGeometry( QRect( start_x+wd_no*(140+10), 10, 140, 110 ) );

	wdg->show();

	mod_widget.push_back( wdg );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::loadModules( const char * directory )
{
	bool found[3] = { false, false, false };

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

	moduleBase * mod;
	modWidget * wdg;

	for( int i=0; i<(int)mod_widget.size(); ++i )
	{
		wdg = mod_widget[i];
		mod = wdg->getModule();
		if( !mod ) return;

		result = mod->init();

		if( result != ST_OK )
		{
			LOG( "ERROR: Initialization module error <%d>!\n", i );
			return;
		}

		if( wdg->has_preview() )
		{
			PrevForm * pf;
			pf = new PrevForm();
			wdg->set_preview( pf );
			pf->show();
		}
	}

	timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()), this, SLOT(process_frame()));

	timer->start( 4 );

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

