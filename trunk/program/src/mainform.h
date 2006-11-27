#ifndef MAINFORM_H
#define MAINFORM_H

//////////////////////////////////////////////////////////////////////////

#include <qvariant.h>
#include <qdialog.h>

#include "mp_dllmgr.h"
#include "prevform.h"

#include "../../modules/video_acq_base/src/va_base.h"
#include "../../modules/prob_image_base/src/pi_base.h"
#include "../../modules/posdetect_base/src/pd_base.h"

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

struct processing_data
{
	vaBase		* va_base;
	piBase		* pi_base;
	pdBase		* pd_base;
	PrevForm	* prevForm1;
	PrevForm	* prevForm2;
};

//////////////////////////////////////////////////////////////////////////

class MainForm : public QDialog
{
    Q_OBJECT

public:
    MainForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~MainForm();

	QGroupBox * groupBoxVI;	// module path
	QGroupBox * groupBoxPI;	// module path
	QGroupBox * groupBoxPD;  // position detection

	QComboBox * comboVI;
	QComboBox * comboPI;
	QComboBox * comboPD;

	QCheckBox * checkVI;
	QCheckBox * checkPI;
	QCheckBox * checkPD;

	QCheckBox * checkAvi;

	QPushButton * buttonVIcfg;
	QPushButton * buttonPIcfg;
	QPushButton * buttonPDcfg;

    QPushButton * buttonOk;
	QPushButton * buttonRun;

    virtual void loadModules( const char * directory );

public slots:
	virtual void run();
	virtual void stop();
	virtual void process_frame();
	virtual void close_app();
	virtual void configure_va_mod();
	virtual void configure_pi_mod();
	virtual void configure_pd_mod();

protected slots:
    virtual void languageChange();

private:
	mpdllMgr mgr;
	processing_data p_data;

	std::vector<vaBase*>	va_list;
	std::vector<piBase*>	pi_list;
	std::vector<pdBase*>	pd_list;

	void release_proc_data( processing_data * data );

	QTimer * timer;

};

//////////////////////////////////////////////////////////////////////////

#endif // MAINFORM_H
