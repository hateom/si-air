#include "fnwidget.h"

#include <qpushbutton.h>
#include <qtextedit.h>
#include <qstring.h>
#include <qfiledialog.h>

//////////////////////////////////////////////////////////////////////////

fnWidget::fnWidget( QWidget* parent, const char* name, WFlags f ) : QWidget( parent, name, f )
{
	btn_browse = new QPushButton( this, "btn_browse" );
	btn_browse->setGeometry( QRect( 190, 0, 30, 25 ) );

	edt_filename = new QTextEdit( this, "edt_filename" );
	edt_filename->setGeometry( QRect( 0, 0, 180, 25 ) );

	btn_browse->setText( tr("...") );

	connect( btn_browse, SIGNAL(clicked()), this, SLOT(select_file()) );
}

//////////////////////////////////////////////////////////////////////////

fnWidget::~fnWidget()
{
}

//////////////////////////////////////////////////////////////////////////

QString fnWidget::get_filename()
{
	return( edt_filename->text().copy() );
}

//////////////////////////////////////////////////////////////////////////

void fnWidget::setText( QString txt )
{
	edt_filename->setText( txt );
}

//////////////////////////////////////////////////////////////////////////

void fnWidget::select_file()
{
	QString s = QFileDialog::getOpenFileName(
		"",
		"Videos (*.avi *.mpg *.mpeg)",
		this,
		"Open file dialog"
		"Choose a file" );	

	if( s != "" ) edt_filename->setText( s );
}

//////////////////////////////////////////////////////////////////////////
