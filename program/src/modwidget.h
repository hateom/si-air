#ifndef __MODWIDGET_H__
#define __MODWIDGET_H__

//////////////////////////////////////////////////////////////////////////

#include <qgroupbox.h>
#include "prevform.h"
#include "../../modules/module_base/src/module_base.h"

//////////////////////////////////////////////////////////////////////////

class QPushButton;
class QCheckBox;
class QTextEdit;

//////////////////////////////////////////////////////////////////////////

class modWidget: public QGroupBox
{
	Q_OBJECT

public:
	modWidget( long id, moduleBase * mod, QWidget * parent = 0, const char * name = 0 );
	virtual ~modWidget();

	int getID() { return( id ); }
	moduleBase * getModule() const { return( module ); }

public:
	bool has_preview();
	void language_changed();

public slots:
	void configure_mod();
	void rm_mod();
	void preview_changed();

private:
	QPushButton * button_conf;
	QPushButton * button_del;
	QTextEdit   * edit_name;
	QCheckBox   * check_prev;

	long id;
	moduleBase * module;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MODWIDGET_H__
