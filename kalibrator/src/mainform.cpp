/****************************************************************************
** Form implementation generated from reading ui file 'mainform.ui'
**
** Created: N 7. sty 15:56:06 2007
**      by: The User Interface Compiler ($Id: main.cpp,v 1.1.1.16 2006/05/05 18:20:12 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#include "mainform.h"

#include <qvariant.h>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>

//#include "mainform.ui.h"
/*
 *  Constructs a MainForm as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 *
 *  The dialog will by default be modeless, unless you set 'modal' to
 *  TRUE to construct a modal dialog.
 */
MainForm::MainForm( QWidget* parent, const char* name, bool modal, WFlags fl )
    : QDialog( parent, name, modal, fl )
{
    if ( !name )
	setName( "MainForm" );

    textLabel1 = new QLabel( this, "textLabel1" );
    textLabel1->setGeometry( QRect( 10, 40, 280, 120 ) );

    btn2 = new QPushButton( this, "btn2" );
    btn2->setEnabled( FALSE );
    btn2->setGeometry( QRect( 310, 0, 120, 120 ) );

    btn3 = new QPushButton( this, "btn3" );
    btn3->setEnabled( FALSE );
    btn3->setGeometry( QRect( 20, 260, 60, 60 ) );

    textLabel3 = new QLabel( this, "textLabel3" );
    textLabel3->setGeometry( QRect( 30, 540, 131, 46 ) );

    textLabel2_2_3 = new QLabel( this, "textLabel2_2_3" );
    textLabel2_2_3->setGeometry( QRect( 381, 471, 79, 24 ) );

    textLabel2_5 = new QLabel( this, "textLabel2_5" );
    textLabel2_5->setGeometry( QRect( 381, 441, 79, 24 ) );

    a_edit = new QLineEdit( this, "a_edit" );
    a_edit->setGeometry( QRect( 451, 441, 178, 22 ) );
    a_edit->setFrameShape( QLineEdit::LineEditPanel );
    a_edit->setFrameShadow( QLineEdit::Sunken );

    b_edit = new QLineEdit( this, "b_edit" );
    b_edit->setGeometry( QRect( 450, 470, 178, 22 ) );

    textLabel2_4 = new QLabel( this, "textLabel2_4" );
    textLabel2_4->setGeometry( QRect( 50, 440, 79, 14 ) );

    time_1 = new QLabel( this, "time_1" );
    time_1->setGeometry( QRect( 140, 460, 158, 14 ) );

    textLabel2_3_2 = new QLabel( this, "textLabel2_3_2" );
    textLabel2_3_2->setGeometry( QRect( 50, 480, 79, 14 ) );

    textLabel2_2_2 = new QLabel( this, "textLabel2_2_2" );
    textLabel2_2_2->setGeometry( QRect( 50, 460, 79, 14 ) );

    time_0 = new QLabel( this, "time_0" );
    time_0->setGeometry( QRect( 140, 440, 158, 14 ) );

    time_2 = new QLabel( this, "time_2" );
    time_2->setGeometry( QRect( 140, 480, 158, 14 ) );

    startBtn = new QPushButton( this, "startBtn" );
    startBtn->setGeometry( QRect( 320, 240, 100, 100 ) );

    btn1 = new QPushButton( this, "btn1" );
    btn1->setEnabled( FALSE );
    btn1->setGeometry( QRect( 480, 170, 240, 240 ) );
    btn1->setOn( FALSE );
    btn1->setFlat( FALSE );

    end_btn = new QPushButton( this, "end_btn" );
    end_btn->setGeometry( QRect( 500, 530, 221, 81 ) );
    languageChange();
    resize( QSize(748, 627).expandedTo(minimumSizeHint()) );
    clearWState( WState_Polished );

    // signals and slots connections
    connect( startBtn, SIGNAL( released() ), this, SLOT( btn0_func() ) );
    connect( btn1, SIGNAL( released() ), this, SLOT( btn1_func() ) );
    connect( btn2, SIGNAL( released() ), this, SLOT( btn2_func() ) );
    connect( btn3, SIGNAL( released() ), this, SLOT( btn3_func() ) );
    connect( end_btn, SIGNAL( clicked() ), this, SLOT( close() ) );

    // tab order
    setTabOrder( startBtn, btn1 );
    setTabOrder( btn1, btn3 );
    setTabOrder( btn3, btn2 );
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
    setCaption( tr( "Anus" ) );
    textLabel1->setText( trUtf8( "\x3c\x74\x74\x3e\x4b\x41\x4c\x49\x42\x52\x41\x54\x4f\x52\x3c\x2f\x74\x74\x3e\x3c\x62"
    "\x72\x3e\xa\x4b\x6c\x69\x6b\x6e\x69\x6a\x20\x6e\x61\x20\x70\x72\x7a\x79\x63"
    "\x69\x73\x6b\x75\x20\x73\x74\x61\x72\x74\x2c\x20\x61\x62\x79\x20\x72\x6f\x7a\x70"
    "\x6f\x63\x7a\x61\x63\x20\x73\x7a\x79\x62\x6b\x61\x20\x6b\x61\x6c\x69\x62\x72\x61"
    "\x63\x6a\x65\x2e\xa\x4b\x6f\x6c\x65\x6a\x6e\x65\x20\x70\x72\x7a\x79\x63\x6b"
    "\x69\x73\x6b\x69\x20\x62\x65\x64\x61\x20\x73\x69\x65\x20\x61\x6b\x74\x79\x77\x6f"
    "\x77\x61\x6c\x79\x2c\x20\xa\x54\x77\x6f\x69\x6d\x20\x7a\x61\x64\x61\x6e\x69"
    "\x65\x6d\x20\x6a\x65\x73\x74\x20\x6b\x6c\x69\x6b\x6e\x61\x63\x20\x6b\x6f\x6c\x65"
    "\x6a\x6e\x6f\x20\x6e\x61\x20\x70\x72\x7a\x79\x63\x69\x73\x6b\x20\x22\x53\x74\x61"
    "\x72\x74\x22\x2c\xa\x20\x61\x20\x6e\x61\x73\x74\x65\x70\x6e\x69\x65\x20\x61"
    "\x6b\x74\x79\x77\x6e\x79\x20\x70\x72\x7a\x79\x63\x69\x73\x6b\x20\x69\x20\x70\x6f"
    "\x77\x72\x6f\x63\x69\x63\x20\x6e\x61\x20\x73\x74\x61\x72\x74\x20\x69\x20\x6b\x6c"
    "\x69\x6e\x6b\xc4\x85\xc4\x87\x2e\x20\xa\x50\x72\x6f\x63\x65\x64\x75\x72\xc4"
    "\x99\x20\x74\xc4\x99\x20\x70\x6f\x77\x74\xc3\xb3\x72\x7a\x20\x74\x72\x7a\x79\x20"
    "\x72\x61\x7a\x79\x2e\x20\x4d\x69\x65\x72\x7a\x6f\x6e\x65\x20\x62\xc4\x99\x64\xc4"
    "\x85\x20\x63\x7a\x61\x73\x75\x20\xa\x70\x6f\x6d\x69\xc4\x99\x64\x7a\x79\x20"
    "\x6b\x6c\x69\x6b\x6e\x69\xc4\x99\x63\x69\x65\x6d\x20\x53\x74\x61\x72\x74\x20\x61"
    "\x20\x61\x6b\x74\x79\x77\x6e\x79\x6d\x20\x70\x72\x7a\x79\x63\x69\x73\x6b\x69\x65"
    "\x6d\x2e" ) );
    btn2->setText( tr( "BTN2" ) );
    btn3->setText( tr( "BT3" ) );
    textLabel3->setText( tr( "BTN1 - W 240 D=60 (+50)\n"
"BTN2 - W 120 D=120 (+50)\n"
"BTN3 - W 60  D=240 (+50)" ) );
    textLabel2_2_3->setText( tr( "Obliczone b" ) );
    textLabel2_5->setText( tr( "Obliczone a" ) );
    textLabel2_4->setText( tr( "Czas Start - Btn1" ) );
    time_1->setText( tr( "N/A" ) );
    textLabel2_3_2->setText( tr( "Czas Start - Btn3" ) );
    textLabel2_2_2->setText( tr( "Czas Start - Btn2" ) );
    time_0->setText( tr( "N/A" ) );
    time_2->setText( tr( "N/A" ) );
    startBtn->setText( tr( "Start" ) );
    btn1->setText( tr( "BTN1" ) );
    end_btn->setText( tr( "Zamknij" ) );
}


int MainForm::btn1_func()
{
	return 0;
}


int MainForm::btn2_func()
{
	return 0;
}


int MainForm::btn3_func()
{
	return 0;
}


int MainForm::btn0_func()
{
	btn1->setEnabled(true);
	btn2->setEnabled(true);
	return 0;
}

void MainForm::init ()
{
}
