#include "modwidget.h"

#include <qpushbutton.h>
#include <qlineedit.h>
#include <qcheckbox.h>
#include <qapp.h>

#include "optform.h"
#include "mp_logger.h"

#include "main_buttons.h"

//////////////////////////////////////////////////////////////////////////

modWidget::modWidget( long new_id, moduleBase * mod, OptionsBox * opt_f, 
					 QWidget * parent, const char * name ) : 
	id(new_id), module(mod), QGroupBox( parent, name ), opt_form(opt_f),
	del_btn( (const char**) btn2_data ), cfg_btn((const char**) btn0_data),
	prv_btn( (const char**) btn5_data )
{
	edit_name = new QLineEdit( this, "editname" );
	edit_name->setGeometry( QRect( 10, 10, 180, 25 ) );

	check_prev = new QPushButton( this, "checkPrev" );
	check_prev->setGeometry( QRect( 205, 10, 30, 25 ) );
	check_prev->setPixmap( prv_btn );
	check_prev->setToggleButton( true );

	button_conf = new QPushButton( this, "buttonConf" );
	button_conf->setGeometry( QRect( 245, 10, 25, 25 ) );
	button_conf->setPixmap( cfg_btn );

	button_del = new QPushButton( this, "buttonDel" );
	button_del->setGeometry( QRect( 275, 10, 25, 25 ) );
	button_del->setPixmap( del_btn );

	connect( button_conf, SIGNAL(clicked()), this, SLOT(configure_mod()) );
	connect( button_del, SIGNAL(clicked()), this, SLOT(rm_mod()) );
	connect( check_prev, SIGNAL(clicked()), this, SLOT(preview_changed()) );

	int check;
	if( module->get_param( "preview_param", &check ) == 0 && check == 1 )
	{
		//check_prev->setChecked( true );
		check_prev->setOn( true );
		setPaletteBackgroundColor( QColor( 220, 255, 220 ) );
	}
	else
	{
		//check_prev->setChecked( false );
		check_prev->setOn( false );
		setPaletteBackgroundColor( QColor( 255, 220, 220 ) );
	}

	language_changed();
	resize( QSize( 310, 40 ) );
}

//////////////////////////////////////////////////////////////////////////

modWidget::~modWidget()
{
}

//////////////////////////////////////////////////////////////////////////

void modWidget::language_changed()
{
//	button_conf->setText( tr("Cfg") );
//	button_del->setText( tr("Del") );
//	check_prev->setText( tr("Prv") );
	edit_name->setText( tr( module->get_module_description() ) );
}

//////////////////////////////////////////////////////////////////////////

void modWidget::preview_changed()
{
	mb_param * par;

	par = module->find_param( "preview_param" );
	if( !par ) return;

	//if( check_prev->isChecked() )
	if( check_prev->isOn() )
	{
		//*((int*)(par->data)) = 1;
		module->set_param( "preview_param", 1 );
		setPaletteBackgroundColor( QColor( 220, 255, 220 ) );
	}
	else
	{
		//*((int*)(par->data)) = 0;
		module->set_param( "preview_param", 0 );
		setPaletteBackgroundColor( QColor( 255, 220, 220 ) );
	}
}

//////////////////////////////////////////////////////////////////////////

void modWidget::rm_mod()
{
	LOG( "Unable to remove this module!\n" );
}

//////////////////////////////////////////////////////////////////////////

void modWidget::configure_mod()
{
	OptForm * optForm;
	opt_form->remove_last_cfg_form();
//	optForm = new OptForm( module, opt_form );
	optForm = new OptForm( module, opt_form->viewport() );
	opt_form->set_current_cfg_form( optForm );
//	optForm->setGeometry( QRect( 5, 15, 250, 320 ) );
//	sview->addChild( optForm );
	opt_form->addChild( optForm );
	optForm->show();
	qApp->processEvents();
}

//////////////////////////////////////////////////////////////////////////

bool modWidget::has_preview()
{
	if( check_prev != NULL )
	{
		return( check_prev->isOn() );
		//return( check_prev->isChecked() );
	}

	return( false );
}

//////////////////////////////////////////////////////////////////////////
