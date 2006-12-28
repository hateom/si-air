#include "previewwidget.h"
#include <qtimer.h>
#include <qlabel.h>

//////////////////////////////////////////////////////////////////////////

previewWidget::previewWidget( preview * p, QWidget* parent, const char* name, WFlags f ) :
	prv(p), QWidget(parent, name, f )
{
	update_timer = new QTimer();
	connect( update_timer, SIGNAL(timeout()), this, SLOT(on_timer()) );
	update_timer->start( p->update_rate );

	label = new QLabel( this, "label" );
	label->setGeometry( QRect( 0, 0, 180, 24 ) );
}

//////////////////////////////////////////////////////////////////////////

previewWidget::~previewWidget()
{
	update_timer->stop();
	delete update_timer;
	update_timer = NULL;
}

//////////////////////////////////////////////////////////////////////////

void previewWidget::on_timer()
{
	static char buffer[256];
	switch( prv->type )
	{
	case PT_INT:
	case PT_BOOL:
		sprintf( buffer, "%d", *(int*)prv->ptr );
		break;
	case PT_LONG:
		sprintf( buffer, "%ld", *(long*)prv->ptr );
		break;
	case PT_FLOAT:
	case PT_DOUBLE:
		sprintf( buffer, "%3.2f", *(float*)prv->ptr );
		break;
	}
	label->setText( tr(buffer) );
}

//////////////////////////////////////////////////////////////////////////
