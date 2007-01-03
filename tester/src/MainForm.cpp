/****************************************************************************
** Form implementation generated from reading ui file 'MainForm.ui'
**
** Created: Śr 3. sty 22:25:17 2007
**      by: The User Interface Compiler ($Id: main.cpp,v 1.1.1.16 2006/05/05 18:20:12 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "MainForm.h"

#include <qvariant.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qaction.h>
#include <qmenubar.h>
#include <qpopupmenu.h>
#include <qtoolbar.h>
#include <qpushbutton.h>

#include <cmath>

#define Q_PI 3.141592653589f
#define BUTTONS 9

static int path[] = { 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8, 0, 9, 0, -1 };

/*
 *  Constructs a MainForm as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 */
MainForm::MainForm( QWidget* parent, const char* name, WFlags fl )
    : QMainWindow( parent, name, fl ), position(0)
{
    (void)statusBar();
    if ( !name )
	setName( "MainForm" );

	resize( QSize(1000, 650).expandedTo(minimumSizeHint()) );

	myButton * btn;

	float r = QMIN(width(), height() )/2 - 65;
	int x, y;
	int ink = 0;

	btn = new myButton( ink++, this, "circle_btn" );
	btn_list.push_back( btn );
	btn->setGeometry( QRect( width()/2-50, height()/2-30, 100, 60 ));
	btn->setText( tr("START") );
	
	QFont ft( tr("Trebuchet MS"), 14 );
	ft.setBold( true );
	btn->setFont( ft );

	connect( btn, SIGNAL(clicked(int)), this, SLOT(on_click(int)) );

	for( float f=0; f<2*Q_PI; f += 2.0f*Q_PI/(float)BUTTONS )
	{
		x = width()/2  + (int)(cosf( f )*r);
		y = height()/2 + (int)(sinf( f )*r);

		printf( "%d,%d\n", x, y );

		btn = new myButton( ink++, this, "circle_btn" );
		btn_list.push_back( btn );

		btn->setGeometry( QRect( x-50, y-30, 100, 60 ));
		btn->setFont( ft );
		connect( btn, SIGNAL(clicked(int)), this, SLOT(on_click(int)) );

		if( ink == BUTTONS+1 ) break;
	}

    // toolbars

    languageChange();
    //resize( QSize(1000, 650).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );
}

/*
 *  Destroys the object and frees any allocated resources
 */
MainForm::~MainForm()
{
    // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void MainForm::languageChange()
{
    setCaption( tr( "Tester" ) );
}

void MainForm::on_click( int id )
{
	printf( ">>> click for: %d\n", id );
	if( path[position] == id )
	{
		printf( ">>> OK\n" );
		btn_list[path[position]]->setText( tr("") );
		position++;
		if( path[position] == -1 )
		{
			position = 0;
			printf( ">>> TEST FINISHED!\n" );
			btn_list[0]->setText( tr("START") );
			return;
		}
		btn_list[path[position]]->setText( tr("PUSH ME!") );
	}
	else
	{
		printf( "!!! BAD!\n" );
	}
}
