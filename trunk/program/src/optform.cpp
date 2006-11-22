#include "optform.h"

#include <qgroupbox.h>
#include <qtextedit.h>
#include <qlabel.h>
#include <qpushbutton.h>

OptForm::OptForm( QWidget* parent, const char* name, bool modal, WFlags fl, moduleBase * base )
: QDialog( parent, name, modal, fl )
{
	if ( !name ) setName( "OptForm" );

	module = base;

	int pcount = base->param_count();
	int space_height = pcount*30+30;

	groupBox = new QGroupBox( this, "paramSpace" );
	groupBox->setGeometry( QRect( 10, 10, 340, space_height ) );

	QTextEdit ** edit;
	QLabel ** label;

	edit = new QTextEdit*[pcount];
	label = new QLabel*[pcount];

	char temp[128] = "";
	for( int i=0; i<pcount; ++i )
	{
		temp[0] = (char)('a'+i);
		temp[1] = '\0';
		edit[i] = new QTextEdit( groupBox, tr("param_edit_") + tr(temp) );
		edit[i]->setGeometry( QRect( 100, 15+i*30, 220, 25 ) );

		switch( base->get_param(i)->type )
		{
			case PT_INT:
			case PT_LONG:
				sprintf( temp, "%d", (int)(*((int*)base->get_param(i)->data)) );
				break;
			case PT_FLOAT:
				sprintf( temp, "%f", (float)(*((float*)base->get_param(i)->data)) );
				break;
		}

		edit[i]->setText( tr( temp ) );

		label[i] = new QLabel( groupBox, tr(base->get_param(i)->name) );
		label[i]->setGeometry( QRect( 10, 15+i*30, 90, 25 ) );
		label[i]->setText( tr(base->get_param(i)->name) );
	}

	QPushButton * btn_ok;

	btn_ok = new QPushButton( this, tr("btnOK") );
	btn_ok->setGeometry( QRect( 360, 10, 140, 30 ) );
	btn_ok->setText( tr("OK") );

	connect( btn_ok, SIGNAL(clicked()), this, SLOT(close()) );

	languageChange();
	resize( QSize( 525, space_height + 20 ).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );
}

OptForm::~OptForm()
{

}

void OptForm::languageChange()
{
	setCaption( tr( "SI Module Parameters Editor" ) );
	groupBox->setTitle( tr( "Module Parameters" ) );
}