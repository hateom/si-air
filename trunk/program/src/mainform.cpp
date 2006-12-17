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

#include "mp_path.h"
#include "optform.h"
#include "prevform.h"
#include "mp_path.h"
#include "mp_logger.h"
#include "module_mgr.h"
#include "../../modules/module_base/src/status_codes.h"

//////////////////////////////////////////////////////////////////////////

static int poss1[] = 
{
	240, 10,   240+150,  10,   240+300,   10,   240, 130,  240+150,  130,  240+300,  130,  
	240, 250,  240+150,  250,  240+300,  250,   240, 370,  240+150,  370,  240+300,  370
};

//////////////////////////////////////////////////////////////////////////

MainForm::MainForm( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "MainForm" );

    buttonOk = new QPushButton( this, "buttonOk" );
    buttonOk->setGeometry( QRect( 505, 390, 195, 26 ) );

	buttonRun = new QPushButton( this, "buttonRun" );
	buttonRun->setGeometry( QRect( 305, 390, 195, 26 ) );

	listBox = new QListBox( this, "listBox" );
	listBox->setGeometry( QRect( 10, 10, 220, 300 ) );

	buttonLoad= new QPushButton( this, "buttonLoad" );
	buttonLoad->setGeometry( QRect( 10, 320, 220, 26 ) );

	buttonAdd= new QPushButton( this, "buttonAdd" );
	buttonAdd->setGeometry( QRect( 10, 350, 220, 26 ) );

	buttonReset = new QPushButton( this, "buttonReset" );
	buttonReset->setGeometry( QRect( 10, 380, 220, 26 ) );

	groupMod = new QGroupBox( this, "groupMod" );
	groupMod->setGeometry( QRect( 240, 10, 460, 370 ) );
	groupMod->setFrameStyle( QFrame::Panel | QFrame::Sunken );

	connect( buttonLoad, SIGNAL(clicked()), this, SLOT(load_modules()) );
	connect( buttonOk, SIGNAL(clicked()), this, SLOT(close()) );
	connect( buttonRun, SIGNAL(clicked()), this, SLOT(run()) );
	connect( listBox, SIGNAL(selected(QListBoxItem*)), this, SLOT(lb_selected(QListBoxItem*)) );
	connect( buttonReset, SIGNAL(clicked()), sModuleMgr, SLOT(clear_path()) );
	connect( buttonAdd, SIGNAL(clicked()), this, SLOT(add_module()) );
	connect( sModuleMgr, SIGNAL(module_loaded(moduleBase*,int)), this, SLOT(module_loaded(moduleBase*,int)) );
	connect( sModuleMgr, SIGNAL(module_unload(moduleBase*,int)), this, SLOT(module_unload(moduleBase*,int)) );
	connect( sModuleMgr, SIGNAL(added_to_path(moduleBase*,int)), this, SLOT(added_to_path(moduleBase*,int)) );
	connect( sModuleMgr, SIGNAL(path_cleared()), this, SLOT(path_cleared()) );
	connect( sModuleMgr, SIGNAL(processing_started()), this, SLOT(processing_started()) );
	connect( sModuleMgr, SIGNAL(processing_finished()), this, SLOT(processing_finished()) );

	QTimer * load_timer = new QTimer( this );
	connect( load_timer, SIGNAL(timeout()), this, SLOT(load_modules()) );
	load_timer->start( 500, TRUE );

    languageChange();
    resize( QSize(710, 425).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::close_app()
{
	
}

//////////////////////////////////////////////////////////////////////////

MainForm::~MainForm()
{
}

//////////////////////////////////////////////////////////////////////////

void MainForm::languageChange()
{
    setCaption( tr( "SI Module List" ) );
    buttonOk->setText( tr( "Close" ) );
	buttonRun->setText( tr( "Run!" ) );
	buttonAdd->setText( tr( "Add Module" ) );
	buttonReset->setText( tr( "Clear Path" ) );
	buttonLoad->setText( tr( "Load Modules" ) );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::add_module()
{
	int item = listBox->currentItem();
	sModuleMgr->add_to_path( item );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::lb_selected( QListBoxItem * )
{
	int item = listBox->currentItem();
	sModuleMgr->add_to_path( item );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::stop()
{
	sModuleMgr->stop_processing(); 

	connect( buttonRun, SIGNAL(clicked()), this, SLOT(run()) );
	disconnect( buttonRun, SIGNAL(clicked()), this, SLOT(stop()) );
	buttonRun->setText( "Run!" );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::run()
{
	connect( buttonRun, SIGNAL(clicked()), this, SLOT(stop()) );
	disconnect( buttonRun, SIGNAL(clicked()), this, SLOT(run()) );
	buttonRun->setText( "Stop!" );

	sModuleMgr->start_processing();
}

//////////////////////////////////////////////////////////////////////////

void MainForm::module_loaded( moduleBase * base, int no )
{
	listBox->insertItem( tr( base->get_module_description() ) );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::module_unload( moduleBase * base, int no )
{
}

//////////////////////////////////////////////////////////////////////////

void MainForm::added_to_path( moduleBase * base, int no )
{
	LOG( ">>> inserting module widget <%d>\n", no );

	modWidget * wdg;
	int w_no = (int)mod_widget.size();

	wdg = new modWidget( no, base, /*prev,*/ groupMod, "modWidget" );
	wdg->setGeometry( QRect( poss1[w_no*2]-230, poss1[w_no*2+1], 140, 110 ) );

	wdg->show();

	mod_widget.push_back( wdg );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::path_cleared()
{
	LOG( ">>> clearing path\n" );

	modWidget * wdg;
	int size = (int)mod_widget.size();

	for( int i=0; i<size; ++i )
	{
		wdg = mod_widget[i];
		wdg->close();
		delete wdg;
	}

	mod_widget.clear();
}

//////////////////////////////////////////////////////////////////////////

void MainForm::processing_started()
{
}

//////////////////////////////////////////////////////////////////////////

void MainForm::processing_finished()
{
}

//////////////////////////////////////////////////////////////////////////

void MainForm::closeEvent( QCloseEvent * ce )
{
	if( buttonRun->text() != tr("Stop!") )
	{
		ce->accept();
		close_app();
	}
	else
	{
		LOG( ">>> Processing is still running!\n" );
	}
}	

//////////////////////////////////////////////////////////////////////////

void MainForm::load_modules()
{
	listBox->clear();
	sModuleMgr->unload_modules();
	sModuleMgr->load_modules( GETPATH("modules") );
}

//////////////////////////////////////////////////////////////////////////
