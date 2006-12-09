//////////////////////////////////////////////////////////////////////////

#include "optform.h"

#include <qgroupbox.h>
#include <qtextedit.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include "fnwidget.h"

//////////////////////////////////////////////////////////////////////////

OptForm::OptForm( QWidget* parent, const char* name, bool modal, WFlags fl, moduleBase * base )
: QDialog( parent, name, modal, fl )
{
	if ( !name ) setName( "OptForm" );

	module = base;

	int pcount = base->param_count();
	int space_height = pcount*30+30;

	groupBox = new QGroupBox( this, "paramSpace" );
	groupBox->setGeometry( QRect( 10, 10, 340, space_height ) );

	QLabel ** label;
	QTextEdit * edt;
	fnWidget * fnw;

	label = new QLabel*[pcount];

	char temp[128] = "";
	for( int i=0; i<pcount; ++i )
	{
		temp[0] = (char)('a'+i);
		temp[1] = '\0';
		
		switch( base->get_param(i)->type )
		{
			case PT_INT:
			case PT_LONG:
				edt = new QTextEdit( groupBox, tr("param_edit_") + tr(temp) );
				edt->setGeometry( QRect( 100, 15+i*30, 220, 25 ) );
				wdg_list.push_back( edt );
				sprintf( temp, "%d", (int)(*((int*)base->get_param(i)->data)) );
				edt->setText( tr( temp ) );
				break;
			case PT_FLOAT:
				edt = new QTextEdit( groupBox, tr("param_edit_") + tr(temp) );
				edt->setGeometry( QRect( 100, 15+i*30, 220, 25 ) );
				wdg_list.push_back( edt );
				sprintf( temp, "%f", (float)(*((float*)base->get_param(i)->data)) );
				edt->setText( tr( temp ) );
				break;
			case PT_STRING:
				edt = new QTextEdit( groupBox, tr("param_edit_") + tr(temp) );
				edt->setGeometry( QRect( 100, 15+i*30, 220, 25 ) );
				wdg_list.push_back( edt );
				sprintf( temp, "%s", (char*)(*((char**)base->get_param(i)->data)) );
				edt->setText( tr( temp ) );
				break;
			case PT_FILENAME:
				fnw = new fnWidget( groupBox, tr("param_fnw_") + tr(temp) );
				fnw->setGeometry( QRect( 100, 15+i*30, 220, 25 ) );
				fnw->show();
				wdg_list.push_back( fnw );
				sprintf( temp, "%s", (char*)(*((char**)base->get_param(i)->data)) );
				fnw->setText( temp );
				break;
			default:
				sprintf( temp, "" );
				break;
		}

		

		label[i] = new QLabel( groupBox, tr(base->get_param(i)->name) );
		label[i]->setGeometry( QRect( 10, 15+i*30, 90, 25 ) );
		label[i]->setText( tr(base->get_param(i)->name) );
	}

	QPushButton * btn_ok;

	btn_ok = new QPushButton( this, tr("btnOK") );
	btn_ok->setGeometry( QRect( 360, 10, 140, 26 ) );
	btn_ok->setText( tr("OK") );

	QPushButton * btn_cancel;

	btn_cancel = new QPushButton( this, tr("btnCancel") );
	btn_cancel->setGeometry( QRect( 360, 40, 140, 30 ) );
	btn_cancel->setText( tr("Cancel") );

	connect( btn_ok, SIGNAL(clicked()), this, SLOT(save_conf()) );
	connect( btn_cancel, SIGNAL(clicked()), this, SLOT(close()) );

	languageChange();
	resize( QSize( 525, space_height + 20 ).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );
}

//////////////////////////////////////////////////////////////////////////

void OptForm::save_conf()
{
	int pcount = module->param_count();

	for( int i=0; i<pcount; ++i )
	{
		switch( module->get_param(i)->type )
		{
		case PT_INT:
		case PT_LONG:
			long * ptrl;
			ptrl = ((long*)(module->get_param(i)->data));
			*ptrl = ((QTextEdit*)(wdg_list[i]))->text().toLong();
			break;
		case PT_FLOAT:
			float * ptrf;
			ptrf = ((float*)(module->get_param(i)->data));
			*ptrf = ((QTextEdit*)(wdg_list[i]))->text().toFloat();
			break;
		case PT_STRING:
			char ** ptrc;
			ptrc = ((char**)(module->get_param(i)->data));
			*ptrc = strdup( ((char*)(((QTextEdit*)(wdg_list[i]))->text().ascii())) );
			break;
		case PT_FILENAME:
			char ** ptrfn;
			ptrfn = ((char**)(module->get_param(i)->data));
			*ptrfn = strdup( ((char*)(((fnWidget*)(wdg_list[i]))->get_filename().ascii())) );
			break;
		}
	}
	close();
}

//////////////////////////////////////////////////////////////////////////

OptForm::~OptForm()
{

}

//////////////////////////////////////////////////////////////////////////

void OptForm::languageChange()
{
	setCaption( tr( "SI Module Parameters Editor" ) );
	groupBox->setTitle( tr( "Module Parameters" ) );
}

//////////////////////////////////////////////////////////////////////////
