/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:52
	plik:    	prevform
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __PREV_FORM_H__
#define __PREV_FORM_H__

//////////////////////////////////////////////////////////////////////////

#include <qvariant.h>
#include <qdialog.h>
#include <windows.h>

#include "../../modules/module_base/src/module_base.h"

class QMouseEvent;

//////////////////////////////////////////////////////////////////////////

/// preview form
class PrevForm : public QDialog
{
	Q_OBJECT

public:
	PrevForm( int id, QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
	~PrevForm();

//	HWND get_handle() { return( this->QWidget::winId() ); }
	void render_frame( frame_data * frame );
	int get_id() const { return( id ); }

protected slots:
	virtual void languageChange();

protected:
	virtual void mousePressEvent( QMouseEvent * e );
	virtual void mouseReleaseEvent( QMouseEvent * e );
	virtual void mouseMoveEvent( QMouseEvent * e );

signals:
	void mouse_select( int sx, int sy, int sw, int sh );

private:
	void closeEvent( QCloseEvent * ce );

	QTimer * timer;
	bool moving;

	int sx, sy;
	int sw, sh;
	long select_time;
	int id;
};

//////////////////////////////////////////////////////////////////////////

#endif // __PREV_FORM_H__

