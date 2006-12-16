//////////////////////////////////////////////////////////////////////////

#include "prevform.h"
#include "mp_logger.h"

#include <windows.h>

#include <qtimer.h>
#include <qimage.h>
#include <qpainter.h>


//////////////////////////////////////////////////////////////////////////

PrevForm::PrevForm( moduleBase * inbase, PrevForm * pr, QWidget* parent, const char* name, bool modal, WFlags fl )
: QDialog( parent, name, modal, fl ), base(inbase), timer(NULL), sx(0), sy(0), sw(0), sh(0), select_time(0), 
  prev(pr), next(NULL)
{
	if ( !name ) setName( "PrevForm" );

	languageChange();
	resize( QSize( 350, 260 ).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );

	if( pr ) pr->set_next( this );

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
	painter.drawImage( QPoint(0, 0), img );

	if( GetTickCount()-select_time < 2000 )
	{
		painter.setPen( QColor( 255, 0, 0 ) );
		painter.drawRect( QRect( sx, sy, sw, sh ) );
	}
}

//////////////////////////////////////////////////////////////////////////

void PrevForm::mousePressEvent( QMouseEvent * e )
{
//	LOG( ">>> mousePress   (%003d,%003d)\n", e->x(), e->y() );

	sx = e->x();
	sy = e->y();
	sw = sh = 0;
}

//////////////////////////////////////////////////////////////////////////

inline void swap( int & a, int & b )
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

//////////////////////////////////////////////////////////////////////////

void PrevForm::mouseReleaseEvent( QMouseEvent * e )
{
//	LOG( ">>> mouseRelease (%003d,%003d)\n", e->x(), e->y() );

	int nx = e->x(), ny = e->y();

	if( nx < 0 ) nx = 0;
	if( ny < 0 ) ny = 0;

	if( nx > width()) nx = width()-1;
	if( ny > height()) ny = height()-1;

	if( nx < sx ) swap( nx, sx );
	if( ny < sy ) swap( ny, sy );

	sw = abs(sx - nx);
	sh = abs(sy - ny);

//	LOG( ">>> mouseRegion (%d,%d,%d,%d)\n", sx, sy, sw, sh );
	base->mouse_select( sx, sy, sw, sh );

	if( next ) next->select_right( sx, sy, sw, sh );
	if( prev ) prev->select_left( sx, sy, sw, sh );

	select_time = GetTickCount();
}

//////////////////////////////////////////////////////////////////////////

void PrevForm::select_left( int sx, int sy, int sw, int sh )
{
	if( prev ) prev->select_left( sx, sy, sw, sh );
	base->mouse_select( sx, sy, sw, sh );
}

//////////////////////////////////////////////////////////////////////////

void PrevForm::select_right( int sx, int sy, int sw, int sh )
{
	if( next ) next->select_left( sx, sy, sw, sh );
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
