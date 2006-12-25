#include "modwidget.h"

#include <qpushbutton.h>
#include <qtextedit.h>
#include <qcheckbox.h>

#include "optform.h"
#include "mp_logger.h"

//////////////////////////////////////////////////////////////////////////

modWidget::modWidget( long new_id, moduleBase * mod, OptionsBox * opt_f, QWidget * parent, const char * name ) : 
	id(new_id), module(mod), QGroupBox( parent, name ), opt_form(opt_f)
{
	edit_name = new QTextEdit( this, "editname" );
	edit_name->setGeometry( QRect( 10, 10, 180, 25 ) );

	check_prev = new QCheckBox( this, "checkPrev" );
	check_prev->setGeometry( QRect( 200, 10, 50, 25 ) );

	button_conf = new QPushButton( this, "buttonConf" );
	button_conf->setGeometry( QRect( 245, 10, 25, 25 ) );

	button_del = new QPushButton( this, "buttonDel" );
	button_del->setGeometry( QRect( 275, 10, 25, 25 ) );

	connect( button_conf, SIGNAL(clicked()), this, SLOT(configure_mod()) );
	connect( button_del, SIGNAL(clicked()), this, SLOT(rm_mod()) );
	connect( check_prev, SIGNAL(clicked()), this, SLOT(preview_changed()) );

	int check;
	if( module->get_param( "preview_param", &check ) == 0 && check == 1 )
	{
		check_prev->setChecked( true );
		setPaletteBackgroundColor( QColor( 220, 255, 220 ) );
	}
	else
	{
		check_prev->setChecked( false );
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
	button_conf->setText( tr("Cfg") );
	button_del->setText( tr("Del") );
	check_prev->setText( tr("Prv") );
	edit_name->setText( tr( module->get_module_description() ) );
}

//////////////////////////////////////////////////////////////////////////

void modWidget::preview_changed()
{
	mb_param * par;

	par = module->find_param( "preview_param" );
	if( !par ) return;

	if( check_prev->isChecked() )
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
	optForm = new OptForm( module, opt_form );
	opt_form->set_current_cfg_form( optForm );
	optForm->setGeometry( QRect( 5, 15, 250, 320 ) );
	optForm->show();
}

//////////////////////////////////////////////////////////////////////////

bool modWidget::has_preview()
{
	if( check_prev != NULL )
	{
		return( check_prev->isChecked() );
	}

	return( false );
}

//////////////////////////////////////////////////////////////////////////
