#ifndef __PREV_FORM_H__
#define __PREV_FORM_H__

#include <qvariant.h>
#include <qdialog.h>

#include <windows.h>

/// preview form
class PrevForm : public QDialog
{
	Q_OBJECT

public:
	PrevForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
	~PrevForm();

	HWND get_handle() { return( this->QWidget::winId() ); }

protected slots:
	virtual void languageChange();
};

#endif // __PREV_FORM_H__
