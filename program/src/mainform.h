/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:52
	plik:    	mainform
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef MAINFORM_H
#define MAINFORM_H

//////////////////////////////////////////////////////////////////////////

#include <qvariant.h>
#include <qdialog.h>

#include "prevform.h"
#include "modwidget.h"
#include "../../modules/module_base/src/property_mgr.h"

//////////////////////////////////////////////////////////////////////////

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QGroupBox;
class QTextEdit;
class QListBox;
class QListBoxItem;
class QPushButton;
class QComboBox;
class QTimer;
class QCheckBox;

//////////////////////////////////////////////////////////////////////////

/// okno glowne programu
class MainForm : public QDialog
{
    Q_OBJECT

public:
    MainForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~MainForm();

	QPushButton * buttonLoad;
    QPushButton * buttonOk;
	QPushButton * buttonRun;
	QListBox    * listBox;
	QPushButton * buttonAdd;
	QPushButton	* buttonReset;
	QGroupBox   * groupMod;

public slots:
	virtual void module_loaded( moduleBase * base, int no );
	virtual void module_unload( moduleBase * base, int no );
	virtual void added_to_path( moduleBase * base, int no );
	virtual void path_cleared();
	virtual void processing_started();
	virtual void processing_finished();
	virtual void add_module();

	virtual void run();
	virtual void stop();

	virtual void close_app();
	virtual void lb_selected( QListBoxItem * );

	virtual void load_modules();

protected slots:
    virtual void languageChange();

private:
	void closeEvent( QCloseEvent * ce );
	std::vector<modWidget*>		mod_widget;
};

//////////////////////////////////////////////////////////////////////////

#endif // MAINFORM_H
