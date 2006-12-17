/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:52
	plik:    	optform
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __OPT_FORM_H__
#define __OPT_FORM_H__

//////////////////////////////////////////////////////////////////////////

#include <qvariant.h>
#include <qdialog.h>
#include <vector>
#include "../../modules/module_base/src/module_base.h"
#include "../../modules/module_base/src/mb_param.h"

//////////////////////////////////////////////////////////////////////////

class QTextEdit;
class QGroupBox;
class QLabel;

//////////////////////////////////////////////////////////////////////////

struct wdg_info
{
	QWidget * wdg;			/// kontrolka przechowujaca informacje o parametrze
	int		  value_type;	/// typ parametru
};

//////////////////////////////////////////////////////////////////////////

/// okno edycji parametrow modulu
class OptForm : public QDialog
{
	Q_OBJECT

public:
	OptForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0, moduleBase * mod = NULL );
	~OptForm();

private:
	QGroupBox   *  groupBox;
	QLabel	    ** label;
	QPushButton *  btn_ok;
	QPushButton *  btn_cancel;

protected slots:
	virtual void save_conf();
	virtual void languageChange();

private:
	moduleBase * module;
	std::vector<wdg_info*> wdg_list;
};

//////////////////////////////////////////////////////////////////////////

#endif // __OPT_FORM_H__
