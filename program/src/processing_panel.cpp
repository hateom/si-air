#include "processing_panel.h"
#include "qpopupmenu.h"
#include "mp_logger.h"

//////////////////////////////////////////////////////////////////////////

procFrame::procFrame( QWidget* parent, const char* name, WFlags f ):
	QFrame( parent, name, f ), popup(NULL)
{
	popup = new QPopupMenu( this, "mainPopup" );
	connect( popup, SIGNAL(activated(int)), this, SLOT(in_popup(int)) );
}

//////////////////////////////////////////////////////////////////////////

procFrame::~procFrame()
{
	delete popup;
	popup = NULL;
}

//////////////////////////////////////////////////////////////////////////

void procFrame::send_popups( std::vector<moduleBase*> & list )
{
	popup->clear();
	int size = (int)list.size();

	mod_list.clear();

	for( int i=0; i<size; ++i )
	{
		mod_list.push_back( list[i] );
		popup->insertItem( tr( list[i]->get_module_description()), i );
	}
}

//////////////////////////////////////////////////////////////////////////

void procFrame::mousePressEvent ( QMouseEvent * e )
{
	if( e->button() != RightButton ) return;
	if( popup->count() == 0 ) return;
	popup->exec( e->globalPos() );
}

//////////////////////////////////////////////////////////////////////////

void procFrame::in_popup( int id )
{
	emit popup_exe( mod_list[id] );
}

//////////////////////////////////////////////////////////////////////////
