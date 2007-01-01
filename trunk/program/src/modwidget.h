/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:52
	plik:    	modwidget
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __MODWIDGET_H__
#define __MODWIDGET_H__

//////////////////////////////////////////////////////////////////////////

#include <qgroupbox.h>
#include <qpixmap.h>
#include "prevform.h"
#include "options_box.h"
#include "../../modules/module_base/src/module_base.h"

//////////////////////////////////////////////////////////////////////////

class QPushButton;
class QCheckBox;
class QLineEdit;

//////////////////////////////////////////////////////////////////////////

/// kontrolka reprezentujaca pojedynczy modul na oknie programu glownego
class modWidget: public QGroupBox
{
	Q_OBJECT

public:
	modWidget( long id, moduleBase * mod, OptionsBox * opt_form, QWidget * parent = 0, const char * name = 0 );
	virtual ~modWidget();

	int getID() { return( id ); }
	moduleBase * getModule() const { return( module ); }

public:
	bool has_preview();
	void language_changed();
	void update_prev();

public slots:
	void configure_mod();
	void rm_mod();
	void preview_changed();

private:
	QPushButton * button_conf;
	QPushButton * button_del;
	QLineEdit   * edit_name;
	QPushButton * check_prev;
	OptionsBox	* opt_form;

	QPixmap del_btn;
	QPixmap cfg_btn;
	QPixmap prv_btn;

	long id;
	moduleBase * module;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MODWIDGET_H__
