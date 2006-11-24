#include "prevform.h"

PrevForm::PrevForm( QWidget* parent, const char* name, bool modal, WFlags fl )
: QDialog( parent, name, modal, fl )
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