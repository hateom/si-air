#ifndef __MODWIDGET_H__
#define __MODWIDGET_H__

//////////////////////////////////////////////////////////////////////////

#include <qgroupbox.h>
#include "../../modules/module_base/src/module_base.h"
#include "prevform.h"

//////////////////////////////////////////////////////////////////////////

class QPushButton;
class QCheckBox;
class QTextEdit;

//////////////////////////////////////////////////////////////////////////

class modWidget: public QGroupBox
{
	Q_OBJECT

public:
	modWidget( long id, moduleBase * mod, modWidget * prv, QWidget * parent = 0, const char * name = 0 );
	virtual ~modWidget();

	int getID() { return( id ); }
	moduleBase * getModule() const { return( module ); }
	void set_next_widget( modWidget * w ) { next = w; }

	void set_preview( PrevForm * pf ) { preview = pf; }
	PrevForm * get_preview() { return( preview ); }

public:
	bool has_preview();
	void language_changed();

public slots:
	void configure_mod();
	void rm_mod();

private:
	QPushButton * button_conf;
	QPushButton * button_del;
	QTextEdit   * edit_name;
	QCheckBox   * check_prev;

	PrevForm * preview;

	long id;
	moduleBase * module;
	modWidget * prev, * next;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MODWIDGET_H__
