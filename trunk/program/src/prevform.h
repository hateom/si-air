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
	PrevForm( moduleBase * base, PrevForm * pr, QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
	~PrevForm();

	HWND get_handle() { return( this->QWidget::winId() ); }
//	void set_video_module( moduleBase * base );

	void render_frame( frame_data * frame );

	void set_prev( PrevForm * p ) { prev = p; }
	void set_next( PrevForm * n ) { next = n; }

protected slots:
	virtual void languageChange();
	virtual void anim();

protected:
	virtual void mousePressEvent( QMouseEvent * e );
	virtual void mouseReleaseEvent( QMouseEvent * e );

	void select_left( int sx, int sy, int sw, int sh );
	void select_right( int sx, int sy, int sw, int sh );

private:
	moduleBase * base;
	QTimer * timer;

	int sx, sy;
	int sw, sh;
	long select_time;

	PrevForm * prev;
	PrevForm * next;
};

//////////////////////////////////////////////////////////////////////////

#endif // __PREV_FORM_H__

