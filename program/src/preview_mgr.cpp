#include "preview_mgr.h"
#include "mp_logger.h"

//////////////////////////////////////////////////////////////////////////

static int poss2[] = 
{
	50,     100,   50+330, 100,   50+660, 100,   50+990, 100,  50,     380,   50+330, 380,
	50+660, 380,   50+990, 380,   50,     660,   50+330, 660,  50+660, 660,   50+990, 660
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

	form = new PrevForm();
	form->move( QPoint( poss2[prv_wnd*2], poss2[prv_wnd*2+1] ) );
	form->show();

	connect( form, SIGNAL(mouse_select(int,int,int,int)), this, SLOT(in_mouse_select(int,int,int,int)) );

	prev_list.push_back( form );

	return( (int)prev_list.size()-1 );
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
		delete form;
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
