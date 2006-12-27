#include "mainform.h"

#include <qscrollview.h>
#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qgroupbox.h>
#include <qpushbutton.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qtoolbutton.h>
#include <qimage.h>
#include <qwmatrix.h>

#include "mp_path.h"
#include "module_mgr.h"
#include "mp_logger.h"
#include "main_head.h"
#include "main_arrow.h"
#include "main_buttons.h"

/*
 *  Constructs a MainForm as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
MainForm::MainForm( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl ),
      image0( (const char **) image0_data ), image1((const char **) image1_data),
	  btn_start( (const char **)btn6_data ), btn_reload( (const char **)btn7_data ), 
	  btn_clear( (const char **)btn8_data )
{
//    (void)statusBar();
    if ( !name )
	setName( "MainForm" );
    setCentralWidget( new QWidget( this, "qt_central_widget" ) );

    frame3 = new procFrame( centralWidget(), "frame3" );
    frame3->setGeometry( QRect( 11, 11, 678, 360 ) );
    frame3->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
    frame3->setFrameShape( QFrame::GroupBoxPanel );
    frame3->setFrameShadow( QFrame::Sunken );

    processingImg = new QLabel( frame3, "processingImg" );
    processingImg->setGeometry( QRect( 10, 10, 63, 344 ) );
    processingImg->setPixmap( image0 );
    processingImg->setScaledContents( TRUE );

	headImg = new QLabel( frame3, "headImg" );
	headImg->setGeometry( QRect( 70, 12, 311, 31 ) );
	headImg->setPixmap( image1 );
	headImg->setScaledContents( TRUE );

	labelInfo = new QLabel( frame3, "labelInfo" );
	labelInfo->setGeometry( QRect( 90, 330, 200, 24 ) );
	labelInfo->setText( tr(">> Hint: Right click, and select module") );
	labelInfo->setPaletteForegroundColor( QColor( 120, 120, 120 ) );

	optionsBox = new OptionsBox( frame3, "optionsBox" );
	optionsBox->setGeometry( QRect( 390, 24+8, 270, 341-24 ) );
//	optionsBox->setPaletteBackgroundColor( QColor( 240, 240, 255 ) );
	optionsBox->viewport()->setPaletteBackgroundColor( QColor( 240, 240, 255 ) );

	QFont font( tr("Arial") );
	font.setBold( true );
	QLabel * optLabel = new QLabel( frame3, "optLabel" );
	optLabel->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );
	optLabel->setFont( font );
	optLabel->setGeometry( QRect( 400, 8, 120, 24 ) );
	optLabel->setText( tr( "Module options" ) );

	//optionsBox->addChild( optLabel, 10, 10 );

    panelGroup = new QGroupBox( centralWidget(), "panelGroup" );
    panelGroup->setGeometry( QRect( 10, 380, 681, 40 ) );
	panelGroup->setPaletteBackgroundColor( QColor( 255, 255, 255 ) );

    startButton = new QToolButton( panelGroup, "startButton" );
    startButton->setGeometry( QRect( 590, 10, 80, 24 ) );
	startButton->setIconSet( QIconSet( btn_start ) );
	startButton->setUsesTextLabel( TRUE );
	startButton->setTextPosition( QToolButton::BesideIcon );
	startButton->setBackgroundColor( QColor( 244, 244, 244 ) );

    reloadButton = new QToolButton( panelGroup, "reloadButton" );
    reloadButton->setGeometry( QRect( 10, 9, 80, 24 ) );
	reloadButton->setIconSet( QIconSet( btn_reload ) );
	reloadButton->setUsesTextLabel( TRUE );
	reloadButton->setTextPosition( QToolButton::BesideIcon );
	reloadButton->setBackgroundColor( QColor( 244, 244, 244 ) );

	buttonReset = new QToolButton( panelGroup, "buttonReset" );
	buttonReset->setGeometry( QRect( 100, 9, 80, 24 ) );
	buttonReset->setIconSet( QIconSet( btn_clear ) );
	buttonReset->setUsesTextLabel( TRUE );
	buttonReset->setTextPosition( QToolButton::BesideIcon );
	buttonReset->setBackgroundColor( QColor( 244, 244, 244 ) );

    textEdit1 = new QTextEdit( centralWidget(), "textEdit1" );
    textEdit1->setGeometry( QRect( 10, 430, 678, 70 ) );

	mpLogger::set_output( OT_WINDOW, textEdit1 );

    // actions

	QWMatrix m;
	m.scale( 12.0/20.0, 12.0/20.0 );

    procExitAction = new QAction( this, "procExitAction" );
	procStartAction = new QAction( this, "procStartAction" );
	procStartAction->setIconSet( QIconSet(btn_start.xForm(m)) );
	procClearAction = new QAction( this, "procClearAction" );
	procClearAction->setIconSet( QIconSet(btn_clear.xForm(m)) );
	aboutAction = new QAction( this, "aboutAction" );

//	connect( frame3, SIGNAL(right_click()), popup, SLOT(exec()) );

    // toolbars


    // menubar
    MenuBarEditor = new QMenuBar( this, "MenuBarEditor" );


    Processing = new QPopupMenu( this );
	procStartAction->addTo( Processing );
	procClearAction->addTo( Processing );
    procExitAction->addTo( Processing );

    MenuBarEditor->insertItem( QString(""), Processing, 1 );

	connect( procExitAction, SIGNAL( activated() ) , this, SLOT( close() ) );

    About = new QPopupMenu( this );
	aboutAction->addTo( About );
    MenuBarEditor->insertItem( QString(""), About, 2 );


	connect( buttonReset, SIGNAL(clicked()), sModuleMgr, SLOT(clear_path()) );
	connect( reloadButton, SIGNAL(clicked()), this, SLOT(load_modules()) );
//	connect( buttonOk, SIGNAL(clicked()), this, SLOT(close()) );
	connect( startButton, SIGNAL(clicked()), this, SLOT(run()) );
//	connect( listBox, SIGNAL(selected(QListBoxItem*)), this, SLOT(lb_selected(QListBoxItem*)) );
//	connect( buttonReset, SIGNAL(clicked()), sModuleMgr, SLOT(clear_path()) );
//	connect( buttonAdd, SIGNAL(clicked()), this, SLOT(add_module()) );
	connect( sModuleMgr, SIGNAL(module_loaded(moduleBase*,int)), this, SLOT(module_loaded(moduleBase*,int)) );
	connect( sModuleMgr, SIGNAL(module_unload(moduleBase*,int)), this, SLOT(module_unload(moduleBase*,int)) );
	connect( sModuleMgr, SIGNAL(added_to_path(moduleBase*,int)), this, SLOT(added_to_path(moduleBase*,int)) );
	connect( sModuleMgr, SIGNAL(path_cleared()), this, SLOT(path_cleared()) );
	connect( sModuleMgr, SIGNAL(processing_started()), this, SLOT(processing_started()) );
	connect( sModuleMgr, SIGNAL(processing_finished()), this, SLOT(processing_finished()) );
	connect( frame3, SIGNAL(popup_exe(moduleBase*)), this, SLOT(add_module(moduleBase*)) );

	QTimer * load_timer = new QTimer( this );
	connect( load_timer, SIGNAL(timeout()), this, SLOT(load_modules()) );
	load_timer->start( 500, TRUE );

	setBackgroundColor( QColor( 244, 244, 244 ) );

    languageChange();
    resize( QSize(700, 530).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
MainForm::~MainForm()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MainForm::languageChange()
{
    setCaption( tr( "SI Project :: Tomasz Huczek & Andrzej Jasinski :: AiR 2006 (R) (C)" ) );
//    optionsBox->setTitle( tr( "Module Options" ) );
    panelGroup->setTitle( QString::null );
/*
	startButton->setText( tr( "Start" ) );
    reloadButton->setText( tr( "Reload" ) );
	buttonReset->setText( tr( "Clear path" ) );
*/
	startButton->setText( QString::null );
	startButton->setTextLabel( tr( "Start" ) );
	reloadButton->setText( QString::null );
	reloadButton->setTextLabel( tr( "Reload" ) );
	buttonReset->setText( QString::null );
	buttonReset->setTextLabel( tr( "Clear path" ) );

    procExitAction->setText( tr( "&Exit" ) );
    procExitAction->setMenuText( tr( "&Exit" ) );

	procStartAction->setText( tr( "&Start" ) );
	procStartAction->setMenuText( tr( "&Start" ) );

	procClearAction->setText( tr( "&Clear Path" ) );
	procClearAction->setMenuText( tr( "&Clear Path" ) );

	aboutAction->setText( tr( "&Us" ) );
	aboutAction->setMenuText( tr( "&Us" ) );

    if (MenuBarEditor->findItem(1))
        MenuBarEditor->findItem(1)->setText( tr( "&Processing" ) );
    if (MenuBarEditor->findItem(2))
        MenuBarEditor->findItem(2)->setText( tr( "&About" ) );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::add_module( moduleBase * base )
{
	sModuleMgr->add_to_path( base );
}

//////////////////////////////////////////////////////////////////////////
/*
void MainForm::lb_selected( QListBoxItem * )
{
	int item = listBox->currentItem();
	sModuleMgr->add_to_path( item );
}
*/
//////////////////////////////////////////////////////////////////////////

void MainForm::stop()
{
	sModuleMgr->stop_processing(); 

	connect( startButton, SIGNAL(clicked()), this, SLOT(run()) );
	disconnect( startButton, SIGNAL(clicked()), this, SLOT(stop()) );
	startButton->setTextLabel( tr( "Start" ) );

}

//////////////////////////////////////////////////////////////////////////

void MainForm::run()
{
	connect( startButton, SIGNAL(clicked()), this, SLOT(stop()) );
	disconnect( startButton, SIGNAL(clicked()), this, SLOT(run()) );
	startButton->setTextLabel( tr( "Stop" ) );

	sModuleMgr->start_processing();
}

//////////////////////////////////////////////////////////////////////////

void MainForm::module_loaded( moduleBase * base, int no )
{/*
	listBox->insertItem( tr( base->get_module_description() ) );
	*/
//	textEdit1->insert( tr(">>> ") + tr( base->get_module_description() ) + tr("\n") );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::module_unload( moduleBase * base, int no )
{
}

//////////////////////////////////////////////////////////////////////////

inline const char * shortcut( const char * txt )
{
	static char buffer[34] = "";

	if( strlen( txt ) > 32 )
	{
		memcpy( buffer, txt, 29 );
		buffer[29] = '.';
		buffer[30] = '.';
		buffer[31] = '.';
		buffer[32] = '\0';
	}
	else
	{
		strcpy( buffer, txt );
	}

	return( buffer );
}

//////////////////////////////////////////////////////////////////////////

void MainForm::added_to_path( moduleBase * base, int no )
{
	LOG( ">>> inserting module widget <%s>\n", shortcut( base->get_module_description() ) );

	modWidget * wdg;
	int w_no = (int)mod_widget.size();

	wdg = new modWidget( no, base, optionsBox, frame3, "modWidget" );
	//wdg->setGeometry( QRect( poss1[w_no*2]-230, poss1[w_no*2+1], 140, 110 ) );
	wdg->setGeometry( QRect( 70, w_no*45+50, 310, 40 ) );

	wdg->show();

	mod_widget.push_back( wdg );

	update_popup();
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

	optionsBox->remove_last_cfg_form();

	update_popup();
}

//////////////////////////////////////////////////////////////////////////

void MainForm::update_popup()
{
	std::vector<moduleBase*> list;
	sModuleMgr->get_proper_modules( list );
	frame3->send_popups( list );
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

void MainForm::close_app()
{
	sModuleMgr->unload_modules();
}

//////////////////////////////////////////////////////////////////////////

void MainForm::closeEvent( QCloseEvent * ce )
{
	if( startButton->textLabel() != tr("Stop") )
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
//	listBox->clear();
	sModuleMgr->unload_modules();
	sModuleMgr->load_modules( GETPATH("modules") );

	update_popup();
}

//////////////////////////////////////////////////////////////////////////
