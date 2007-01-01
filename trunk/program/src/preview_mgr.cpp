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

PreviewMgr::PreviewMgr() : visible(0)
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
//	form->move( QPoint( poss2[prv_wnd*2], poss2[prv_wnd*2+1] ) );
//	form->show();

	connect( form, SIGNAL(mouse_select(int,int,int,int)), this, SLOT(in_mouse_select(int,int,int,int)) );

	prev_list.push_back( form );

	return( prv_wnd );
}

//////////////////////////////////////////////////////////////////////////

void PreviewMgr::set_win_pos( PrevForm * prv )
{
	if( !prv ) return;
	prv->move( QPoint( poss2[(visible-1)*2], poss2[(visible-1)*2+1] ) );

	LOG( ">-> set_win_pos() for %d\n", visible-1 );
}

//////////////////////////////////////////////////////////////////////////

void PreviewMgr::reset_positions()
{
	int size = (int)prev_list.size();
	int ink = 0;

	for( int i=0; i<size; ++i )
	{
		if( prev_list[i]->isVisible() )
		{
			prev_list[i]->move( QPoint( poss2[ink*2], poss2[ink*2+1] ) );
			ink++;
		}
	}

	visible = ink;

	LOG( ">-> reset_positions()\n" );
}

//////////////////////////////////////////////////////////////////////////

void PreviewMgr::show_window( int window, bool on_off )
{
	if( window < 0 || window >= (int)prev_list.size() ) return;

	LOG( ">-> show_window %d %d\n", on_off, window );

	if( on_off )
	{
		if( prev_list[window]->isVisible() ) return;
		visible++;
		prev_list[window]->show();
		set_win_pos( prev_list[window] );
	}
	else
	{
		if( !prev_list[window]->isVisible() ) return;
		visible--;
		prev_list[window]->close( false );
		reset_positions();
	}
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
//		disconnect( form, SIGNAL(mouse_select(int,int,int,int)), this, SLOT(in_mouse_select(int,int,int,int)) );
		form->close( false );
//		delete form;
//		prev_list[preview] = NULL;
	}

	reset_positions();

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

	visible = 0;

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

//	PrevForm * form = prev_list[id];

//	if( form != NULL )
//	{
//		disconnect( form, SIGNAL(mouse_select(int,int,int,int)), this, SLOT(in_mouse_select(int,int,int,int)) );
//		prev_list[id] = NULL;
//	}

//	visible--;
	reset_positions();
	emit preview_closed();
}

//////////////////////////////////////////////////////////////////////////
