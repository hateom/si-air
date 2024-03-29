#include "my_button.h"

//////////////////////////////////////////////////////////////////////////

myButton::myButton( int nid, QWidget * parent, const char * name ) : QPushButton( parent, name ), id(nid)
{
	connect( this, SIGNAL(clicked()), this, SLOT(on_click()) );
}

//////////////////////////////////////////////////////////////////////////

myButton::~myButton()
{
}

//////////////////////////////////////////////////////////////////////////

int myButton::get_id()
{
	return( id );
}

//////////////////////////////////////////////////////////////////////////

void myButton::on_click()
{
	emit clicked( id );
}

//////////////////////////////////////////////////////////////////////////
