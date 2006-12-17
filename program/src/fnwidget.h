/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:52
	plik:    	fnwidget
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __FNWIDGET_H__
#define __FNWIDGET_H__

//////////////////////////////////////////////////////////////////////////

#include <qwidget.h>

//////////////////////////////////////////////////////////////////////////

class QPushButton;
class QTextEdit;
class QString;

//////////////////////////////////////////////////////////////////////////

class fnWidget: public QWidget
{
	Q_OBJECT
public:
	fnWidget( QWidget* parent=0, const char* name=0, WFlags f=0 );
	virtual ~fnWidget();

public:
	QString get_filename();
	void setText( QString txt );

protected slots:
	void select_file();

private:
	QPushButton * btn_browse;
	QTextEdit   * edt_filename;
};

//////////////////////////////////////////////////////////////////////////

#endif // __FNWIDGET_H__
