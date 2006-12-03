#ifndef MAINFORM_H
#define MAINFORM_H

//////////////////////////////////////////////////////////////////////////

#include <qvariant.h>
#include <qdialog.h>

#include "mp_dllmgr.h"
#include "prevform.h"
#include "modwidget.h"

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

class MainForm : public QDialog
{
    Q_OBJECT

public:
    MainForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~MainForm();

    QPushButton * buttonOk;
	QPushButton * buttonRun;
	QListBox    * listBox;
	QPushButton * buttonAdd;
	QPushButton	* buttonReset;

    virtual void loadModules( const char * directory );

public slots:
	virtual void run();
	virtual void stop();
	virtual void process_frame();
	virtual void close_app();
	virtual void add_module();
	virtual void lb_selected( QListBoxItem * );

protected slots:
    virtual void languageChange();
	virtual void remove_path();

private:
	mpdllMgr mgr;
	int prv_wnd;

	std::vector<moduleBase*>	mod_list;
	std::vector<modWidget*>		mod_widget;

	void release_proc_data();

	QTimer * timer;

};

//////////////////////////////////////////////////////////////////////////

#endif // MAINFORM_H
