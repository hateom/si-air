#ifndef __PROCESSING_PANEL_H__
#define __PROCESSING_PANEL_H__

//////////////////////////////////////////////////////////////////////////

#include <qframe.h>
#include <vector>
#include "../../modules/module_base/src/module_base.h"

//////////////////////////////////////////////////////////////////////////

class QPopupMenu;

//////////////////////////////////////////////////////////////////////////

class procFrame: public QFrame
{
	Q_OBJECT

public:
	procFrame( QWidget* parent=0, const char* name=0, WFlags f=0 );
	~procFrame();

	void send_popups( std::vector<moduleBase*> & list );

signals:
	void popup_exe( moduleBase * mod );

private slots:
	void in_popup( int id );

protected:
	QPopupMenu * popup;
	void mousePressEvent ( QMouseEvent * e );

	std::vector<moduleBase*> mod_list;
};

//////////////////////////////////////////////////////////////////////////

#endif // __PROCESSING_PANEL_H__