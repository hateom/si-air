/****************************************************************************
** Form interface generated from reading ui file 'mainform.ui'
**
** Created: Wt 21. lis 13:12:53 2006
**      by: The User Interface Compiler ($Id: main.cpp,v 1.1.1.16 2006/05/05 18:20:12 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MAINFORM_H
#define MAINFORM_H

#include <qvariant.h>
#include <qdialog.h>

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

#include "mp_dllmgr.h"

#include "../../modules/video_acq_base/src/va_base.h"
#include "../../modules/prob_image_base/src/pi_base.h"
#include "../../modules/posdetect_base/src/posdetect_base.h"

#include "prevform.h"

struct processing_data
{
	vaBase			* va_base;
	piBase			* pi_base;
	cPosdetectBase	* pd_base;
	PrevForm		* prevForm1;
	PrevForm		* prevForm2;
};

class MainForm : public QDialog
{
    Q_OBJECT

public:
    MainForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~MainForm();

    QGroupBox * groupBox1;	// module list
	QGroupBox * groupBoxVI;	// module path
	QGroupBox * groupBoxPI;	// module path
	QGroupBox * groupBoxPD;  // position detection

	QComboBox * comboVI;
	QComboBox * comboPI;
	QComboBox * comboPD;

	QCheckBox * checkVI;
	QCheckBox * checkPI;
	QCheckBox * checkPD;

    QTextEdit   * textModule;
    QListBox    * listModule;
    QPushButton * buttonOk;
	QPushButton * buttonRun;

    virtual void loadModules( const char * directory );

public slots:
	virtual void selection_changed( QListBoxItem * );
	virtual void selected( int item );
	virtual void run();
	virtual void stop();
	virtual void process_frame();
	virtual void close_app();

protected slots:
    virtual void languageChange();

private:
	mpdllMgr mgr;
	processing_data p_data;

	std::vector<mp_dll_module*>	va_list;
	std::vector<mp_dll_module*>	pi_list;
	std::vector<mp_dll_module*>	pd_list;

	void release_proc_data( processing_data * data );

	QTimer * timer;

};

#endif // MAINFORM_H
