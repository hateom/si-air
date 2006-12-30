//////////////////////////////////////////////////////////////////////////

#include "optform.h"

#include <qgroupbox.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include "fnwidget.h"
#include "rangewidget.h"
#include "previewwidget.h"

//////////////////////////////////////////////////////////////////////////

wdg_info * create_wdg_info( QWidget * wdg, int val_type )
{
	wdg_info * info;
	info = new wdg_info;
	info->wdg = wdg;
	info->value_type = val_type;
	return( info );
}

//////////////////////////////////////////////////////////////////////////

OptForm::OptForm( moduleBase * base, QWidget* parent, const char* name, WFlags fl )
: QWidget( parent, name, fl )
{
	int type;

	if( !name ) setName( "OptForm" );

	module = base;

	int	pcount = base->param_count();
	int	space_height = pcount*30+30;
	wdg_info *	info;

	label = new QLabel*[pcount];

	char temp[128] = "";
	int i=0;
	for( int k=0; k<pcount; ++k )
	{
		if( base->get_param(k)->visible == 0 )
		{
			continue;
		}

		temp[0] = (char)('a'+i);
		temp[1] = '\0';
		
		type = base->get_param(k)->type;
		switch( type )
		{
			case PT_INT:
			case PT_LONG:
				{
					QLineEdit * edt;
					edt = new QLineEdit( this, tr("param_edit_") + tr(temp) );
					sprintf( temp, "%d", (int)(*((int*)base->get_param(k)->data)) );
					edt->setText( tr( temp ) );
					info = create_wdg_info( edt, PT_LONG );
					connect( edt, SIGNAL(textChanged(const QString&)), this, SLOT(save_conf()) );
				}
				break;
			case PT_BOOL:
				{
					QCheckBox * box;
					int on_off;
					box = new QCheckBox( this, tr("param_check_") + tr(temp) );
					box->setText( tr(base->get_param(k)->description) );
					on_off = (int)(*((int*)base->get_param(k)->data));
					box->setChecked( on_off == 1 );
					info = create_wdg_info( box, PT_BOOL );
					connect( box, SIGNAL(clicked()), this, SLOT(save_conf()) );
				}
				break;
			case PT_FLOAT:
				{
					QLineEdit * edt;
					edt = new QLineEdit( this, tr("param_edit_") + tr(temp) );
					sprintf( temp, "%f", (float)(*((float*)base->get_param(k)->data)) );
					edt->setText( tr( temp ) );
					info = create_wdg_info( edt, PT_LONG );
					connect( edt, SIGNAL(textChanged(const QString&)), this, SLOT(save_conf()) );
				}
				break;
			case PT_STRING:
				{
					QLineEdit * edt;
					edt = new QLineEdit( this, tr("param_edit_") + tr(temp) );
					sprintf( temp, "%s", (char*)(*((char**)base->get_param(k)->data)) );
					edt->setText( tr( temp ) );
					info = create_wdg_info( edt, PT_LONG );
					connect( edt, SIGNAL(textChanged(const QString&)), this, SLOT(save_conf()) );
				}
				break;
			case PT_FILENAME:
				{
					fnWidget * fnw;
					fnw = new fnWidget( this, tr("param_fnw_") + tr(temp) );
					fnw->show();
					sprintf( temp, "%s", (char*)(*((char**)base->get_param(k)->data)) );
					fnw->setText( temp );
					info = create_wdg_info( fnw, PT_LONG );
					connect( fnw, SIGNAL(textChanged()), this, SLOT(save_conf()) );
				}
				break;
			case PT_FLOAT_RANGE:
				{
					rangeWidget * rnwf;
					float_range * fr;
					rnwf = new rangeWidget( RT_FLOAT, this, tr("param_rnw_") + tr(temp) );
					rnwf->show();
					fr = (float_range*)(base->get_param(k)->data);
					rnwf->setup( fr->minv, fr->maxv, fr->value );
					info = create_wdg_info( rnwf, PT_FLOAT_RANGE );
					connect( rnwf, SIGNAL(valueChanged()), this, SLOT(save_conf()) );
				}
				break;
			case PT_INT_RANGE:
				{
					rangeWidget * rnw;
					int_range * ir;
					rnw = new rangeWidget( RT_INT, this, tr("param_rnw_") + tr(temp) );
					rnw->show();
					ir = (int_range*)(base->get_param(k)->data);
					rnw->setup( ir->minv, ir->maxv, ir->value );
					info = create_wdg_info( rnw, PT_INT_RANGE );
					connect( rnw, SIGNAL(valueChanged()), this, SLOT(save_conf()) );
				}
				break;
			case PT_PREVIEW:
				{
					previewWidget * pnw;
					preview * prv;
					prv = (preview*)(base->get_param(k)->data);
					pnw = new previewWidget( prv, this, tr("param_prv_") + tr(temp) );
					pnw->show();
					info = create_wdg_info( pnw, PT_PREVIEW );
				}
				break;
			default:
				sprintf( temp, "" );
				break;
		}

		info->wdg->setGeometry( QRect( 10, 25+i*52, 230, 24 ) );
		wdg_list.push_back( info );

		label[i] = new QLabel( this, tr(base->get_param(k)->name) );
		label[i]->setGeometry( QRect( 10, i*52, 230, 24 ) );
		if( type != PT_BOOL )
		{
			label[i]->setText( 
				tr(base->get_param(k)->description) + tr(" ( ") + 
				tr(base->get_param(k)->name) + tr( " )" )
			);
		}
		else 
		{
			label[i]->setText( tr(base->get_param(k)->name) );
		}
		i++;
	}
/*
	btn_ok = new QPushButton( this, tr("btnOK") );
	btn_ok->setGeometry( QRect( 10, 25+i*52, 140, 24 ) );
	btn_ok->setText( tr("&Apply") );

//	btn_cancel = new QPushButton( this, tr("btnCancel") );
//	btn_cancel->setGeometry( QRect( 360, 40, 140, 26 ) );
//	btn_cancel->setText( tr("Cancel") );

	connect( btn_ok, SIGNAL(clicked()), this, SLOT(save_conf()) );
//	connect( btn_cancel, SIGNAL(clicked()), this, SLOT(close()) );
*/
	setPaletteBackgroundColor( QColor( 240, 240, 255 ) );

	languageChange();
	resize( QSize( 248, 25+i*52 + 20 ).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );
}

//////////////////////////////////////////////////////////////////////////

void OptForm::save_conf()
{
	int pcount = module->param_count();

	int i=0;
	for( int k=0; k<pcount; ++k )
	{
		if( module->get_param(k)->visible == 0 )
		{
			continue;
		}

		switch( module->get_param(k)->type )
		{
		case PT_INT:
		case PT_LONG:
			long * ptrl;
			ptrl = ((long*)(module->get_param(k)->data));
			*ptrl = ((QLineEdit*)(wdg_list[i]->wdg))->text().toLong();
			break;
		case PT_BOOL:
			int * ptrb;
			ptrb = ((int*)(module->get_param(k)->data));
			*ptrb = ((QCheckBox*)(wdg_list[i]->wdg))->isChecked();
			break;
		case PT_FLOAT:
			float * ptrf;
			ptrf = ((float*)(module->get_param(k)->data));
			*ptrf = ((QLineEdit*)(wdg_list[i]->wdg))->text().toFloat();
			break;
		case PT_STRING:
			char ** ptrc;
			ptrc = ((char**)(module->get_param(k)->data));
			*ptrc = strdup( ((char*)(((QLineEdit*)(wdg_list[i]->wdg))->text().ascii())) );
			break;
		case PT_FILENAME:
			char ** ptrfn;
			ptrfn = ((char**)(module->get_param(k)->data));
			*ptrfn = strdup( ((char*)(((fnWidget*)(wdg_list[i]->wdg))->get_filename().ascii())) );
			break;
		case PT_FLOAT_RANGE:
			float_range * fr;
			fr = (float_range*)(module->get_param(k)->data);
			fr->value = ((rangeWidget*)(wdg_list[i]->wdg))->get_valuef();
			fr->maxv = ((rangeWidget*)(wdg_list[i]->wdg))->get_maxf();
			fr->minv = ((rangeWidget*)(wdg_list[i]->wdg))->get_minf();
			break;
		case PT_INT_RANGE:
			int_range * ir;
			ir = (int_range*)(module->get_param(k)->data);
			ir->value = ((rangeWidget*)(wdg_list[i]->wdg))->get_value();
			ir->maxv = ((rangeWidget*)(wdg_list[i]->wdg))->get_max();
			ir->minv = ((rangeWidget*)(wdg_list[i]->wdg))->get_min();
			break;
		case PT_PREVIEW:
			// nope :-)
			break;
		}
		i++;
	}
//	close();
}

//////////////////////////////////////////////////////////////////////////

OptForm::~OptForm()
{

}

//////////////////////////////////////////////////////////////////////////

void OptForm::languageChange()
{
//	setCaption( tr( "SI Module Parameters Editor" ) );
//	groupBox->setTitle( tr( "Module Parameters" ) );
}

//////////////////////////////////////////////////////////////////////////
