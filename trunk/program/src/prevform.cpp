#include "prevform.h"

#include <qtimer.h>
#include <qimage.h>
#include <qpainter.h>

PrevForm::PrevForm( QWidget* parent, const char* name, bool modal, WFlags fl )
: QDialog( parent, name, modal, fl ), base(NULL), timer(NULL)
{
	if ( !name ) setName( "PrevForm" );

	languageChange();
	resize( QSize( 350, 260 ).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );
}

PrevForm::~PrevForm()
{

}

void PrevForm::languageChange()
{
	setCaption( tr( "Preview Window" ) );
}

void PrevForm::anim()
{
	int result;
	frame_data * frame;
	
	frame = base->process_frame( &result );

	if( result < 0 )
	{
		timer->stop();
		delete timer;
		timer = NULL;
		return;
	}

	try
	{
		QImage img( (uchar*)frame->bits, frame->width, frame->height, 32, NULL, 256, QImage::LittleEndian );
		QPainter painter( this );
		painter.drawImage( QPoint(0, 0), img );
	}
	catch( ... )
	{
		printf( "fuck :] (%d)\n", result );
	}
}

void PrevForm::set_video_module( vaBase * base )
{
	this->base = base;

	timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()), this, SLOT(anim()));

	printf( "Callback saved. Setting frame capturing...\n" );
	timer->start( 10 );
}
