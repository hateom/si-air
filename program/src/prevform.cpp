//////////////////////////////////////////////////////////////////////////

#include "prevform.h"
#include "mp_logger.h"

#include <windows.h>

#include <qtimer.h>
#include <qimage.h>
#include <qpainter.h>


//////////////////////////////////////////////////////////////////////////

PrevForm::PrevForm( QWidget* parent, const char* name, bool modal, WFlags fl )
: QDialog( parent, name, modal, fl ), timer(NULL), sx(0), sy(0), sw(0), sh(0), select_time(0), 
  moving(false)
{
	if ( !name ) setName( "PrevForm" );

	languageChange();
	resize( QSize( 350, 260 ).expandedTo(minimumSizeHint()) );
	clearWState( WState_Polished );
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

	emit mouse_select( sx, sy, sw, sh );

	moving = false;
	select_time = GetTickCount();
}

//////////////////////////////////////////////////////////////////////////
