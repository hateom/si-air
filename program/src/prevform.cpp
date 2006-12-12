//////////////////////////////////////////////////////////////////////////

#include "prevform.h"
#include "mp_logger.h"

#include <qtimer.h>
#include <qimage.h>
#include <qpainter.h>


//////////////////////////////////////////////////////////////////////////

PrevForm::PrevForm( moduleBase * inbase, QWidget* parent, const char* name, bool modal, WFlags fl )
: QDialog( parent, name, modal, fl ), base(inbase), timer(NULL)
{
	if ( !name ) setName( "PrevForm" );

	languageChange();
	resize( QSize( 350, 260 ).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );

//	connect( this, SIGNAL(mousePressEvent(QMouseEvent*)), this, SLOT(mousePress(QMouseEvent*)) );
//	connect( this, SIGNAL(mouseReleaseEvent(QMouseEvent*)), this, SLOT(mouseRelease(QMouseEvent*)) );
}

//////////////////////////////////////////////////////////////////////////

PrevForm::~PrevForm()
{

}

//////////////////////////////////////////////////////////////////////////

void PrevForm::languageChange()
{
	setCaption( tr( "Preview Window" ) );
}

//////////////////////////////////////////////////////////////////////////

void PrevForm::render_frame( frame_data * frame )
{
	if( !frame || !frame->bits ) return;

	resize( QSize( frame->width, frame->height ).expandedTo(minimumSizeHint()) );
	QImage img( (uchar*)frame->bits, frame->width, frame->height, 32, NULL, 256, QImage::LittleEndian );
	QPainter painter( this );
	painter.setWindow( 0, 0, frame->width, frame->height );
	painter.setBackgroundColor( QColor( 0, 0, 0) );
	painter.drawImage( QPoint(0, 0), img );
}

//////////////////////////////////////////////////////////////////////////

void PrevForm::mousePressEvent( QMouseEvent * e )
{
//	LOG( ">>> mousePress   (%003d,%003d)\n", e->x(), e->y() );

	sx = e->x();
	sy = e->y();
}

//////////////////////////////////////////////////////////////////////////

void PrevForm::mouseReleaseEvent( QMouseEvent * e )
{
//	LOG( ">>> mouseRelease (%003d,%003d)\n", e->x(), e->y() );

	sw = abs(sx - e->x());
	sh = abs(sy - e->y());

	//LOG( ">>> mouseRegion (%d,%d,%d,%d)\n", sx, sy, sw, sh );
	base->mouse_select( sx, sy, sw, sh );
}

//////////////////////////////////////////////////////////////////////////

void PrevForm::anim()
{
/*
	int result;
	frame_data * frame;
	
	frame = base->process_frame( &result );

	if( result < 0 )
	{
		timer->stop();
		delete timer;
		timer = NULL;
		base->free();
		this->close();
		return;
	}

	resize( QSize( frame->width, frame->height ).expandedTo(minimumSizeHint()) );
	QImage img( (uchar*)frame->bits, frame->width, frame->height, 32, NULL, 256, QImage::LittleEndian );
	QPainter painter( this );
	painter.drawImage( QPoint(0, 0), img );
*/
}

//////////////////////////////////////////////////////////////////////////
/*
void PrevForm::set_video_module( moduleBase * base )
{
	this->base = base;

	timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()), this, SLOT(anim()));

	LOG( "Callback saved. Setting frame capturing...\n" );
	timer->start( 10 );
}
*/
//////////////////////////////////////////////////////////////////////////
