#include "preview_mgr.h"
#include "mp_logger.h"

//////////////////////////////////////////////////////////////////////////

static int poss2[] = 
{
	0,     0,   330,   0,   660,     0,   990,   0,  0,   280,   330, 280,
	660, 280,   990, 280,   0,     560,   330, 560,  660, 560,   990, 560
};

//////////////////////////////////////////////////////////////////////////

static PreviewMgr prev_single;

//////////////////////////////////////////////////////////////////////////

PreviewMgr * PreviewMgr::singleton()
{
	return( &prev_single );
}

//////////////////////////////////////////////////////////////////////////

PreviewMgr::PreviewMgr()
{
}

//////////////////////////////////////////////////////////////////////////

PreviewMgr::~PreviewMgr()
{
	close_all();
}

//////////////////////////////////////////////////////////////////////////

int PreviewMgr::register_preview()
{
	PrevForm * form;
	int prv_wnd = (int)prev_list.size();

	form = new PrevForm( prv_wnd );
	form->move( QPoint( poss2[prv_wnd*2], poss2[prv_wnd*2+1] ) );
	form->show();

	connect( form, SIGNAL(mouse_select(int,int,int,int)), this, SLOT(in_mouse_select(int,int,int,int)) );

	prev_list.push_back( form );

	return( prv_wnd );
}

//////////////////////////////////////////////////////////////////////////

int PreviewMgr::render_frame( int preview, frame_data * frame )
{
	if( preview < 0 || preview >= (int)prev_list.size() )
	{
		return( ST_OUT_OF_RANGE );
	}

	PrevForm * form = prev_list[preview];
	if( !form )
	{
		return( ST_WINDOW_CLOSED );
	}

	form->render_frame( frame );

	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

int PreviewMgr::close_preview( int preview )
{
	if( preview < 0 || preview >= (int)prev_list.size() )
	{
		return( ST_OUT_OF_RANGE );
	}

	PrevForm * form = prev_list[preview];

	if( form != NULL )
	{
		disconnect( form, SIGNAL(mouse_select(int,int,int,int)), this, SLOT(in_mouse_select(int,int,int,int)) );
		form->close();
//		delete form;
		prev_list[preview] = NULL;
	}

	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

int PreviewMgr::close_all()
{
	int size = (int)prev_list.size();

	for( int i=0; i<size; ++i )
	{
		close_preview( i );
	}
	prev_list.clear();

	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void PreviewMgr::in_mouse_select( int sx, int sy, int sw, int sh )
{
	emit mouse_select( sx, sy, sw, sh );
}

//////////////////////////////////////////////////////////////////////////

void PreviewMgr::preview_closed( int id )
{
	if( id < 0 || id >= (int)prev_list.size() )
	{
		return;
	}

	PrevForm * form = prev_list[id];

	if( form != NULL )
	{
		disconnect( form, SIGNAL(mouse_select(int,int,int,int)), this, SLOT(in_mouse_select(int,int,int,int)) );
		prev_list[id] = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
