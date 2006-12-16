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
  prev(pr), next(NULL), moving(false)
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

	if( moving || GetTickCount()-select_time < 2000 )
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

	moving = true;
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

void PrevForm::mouseMoveEvent( QMouseEvent * e )
{
	int nx = e->x(), ny = e->y();

	sw = nx - sx;
	sh = ny - sy;
}

//////////////////////////////////////////////////////////////////////////

void PrevForm::mouseReleaseEvent( QMouseEvent * e )
{
	int nx = e->x(), ny = e->y();

	if( nx < 0 ) nx = 0;
	if( ny < 0 ) ny = 0;

	if( nx > width()) nx = width()-1;
	if( ny > height()) ny = height()-1;

	if( nx < sx ) swap( nx, sx );
	if( ny < sy ) swap( ny, sy );

	sw = abs(sx - nx);
	sh = abs(sy - ny);

	base->mouse_select( sx, sy, sw, sh );

	if( next ) next->select_right( sx, sy, sw, sh );
	if( prev ) prev->select_left( sx, sy, sw, sh );

	moving = false;
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
