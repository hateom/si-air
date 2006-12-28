#ifndef __PREVIEW_WIDGET_H__
#define __PREVIEW_WIDGET_H__

//////////////////////////////////////////////////////////////////////////

#include <qwidget.h>
#include "../../modules/module_base/src/mb_param.h"

//////////////////////////////////////////////////////////////////////////

class QTimer;
class QLabel;

//////////////////////////////////////////////////////////////////////////

class previewWidget: public QWidget
{
	Q_OBJECT
public:
	previewWidget( preview * prv, QWidget* parent=0, const char* name=0, WFlags f=0 );
	~previewWidget();

	QLabel * label;

private slots:
	void on_timer();

private:
	preview * prv;
	QTimer  * update_timer;
};

//////////////////////////////////////////////////////////////////////////

#endif // __PREVIEW_WIDGET_H__
