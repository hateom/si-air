#include "modwidget.h"

#include <qpushbutton.h>
#include <qtextedit.h>
#include <qcheckbox.h>

#include "optform.h"
#include "mp_logger.h"

//////////////////////////////////////////////////////////////////////////

modWidget::modWidget( long new_id, moduleBase * mod, modWidget * prv, QWidget * parent, const char * name ) : 
	id(new_id), module(mod), prev(prv), next(NULL), preview(NULL), QGroupBox( parent, name )
{
	if( prev )
	{
		prev->set_next_widget( this );
	}

	edit_name = new QTextEdit( this, "editname" );
	edit_name->setGeometry( QRect( 10, 10, 120, 25 ) );

	check_prev = new QCheckBox( this, "checkPrev" );
	check_prev->setGeometry( QRect( 10, 40, 120, 25 ) );

	button_conf = new QPushButton( this, "buttonConf" );
	button_conf->setGeometry( QRect( 10, 70, 58, 25 ) );

	button_del = new QPushButton( this, "buttonDel" );
	button_del->setGeometry( QRect( 72, 70, 58, 25 ) );

	connect( button_conf, SIGNAL(clicked()), this, SLOT(configure_mod()) );
	connect( button_del, SIGNAL(clicked()), this, SLOT(rm_mod()) );

	language_changed();
	resize( QSize( 140, 110 ) );
}

//////////////////////////////////////////////////////////////////////////

modWidget::~modWidget()
{
}

//////////////////////////////////////////////////////////////////////////

void modWidget::language_changed()
{
	button_conf->setText( tr("Configure") );
	button_del->setText( tr("Delete") );
	check_prev->setText( tr("Preview") );
	edit_name->setText( tr( module->get_module_description() ) );
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
	optForm = new OptForm( 0, 0, TRUE, 0, module );
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
