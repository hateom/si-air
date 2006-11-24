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

#include "mp_dllmgr.h"

class MainForm : public QDialog
{
    Q_OBJECT

public:
    MainForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~MainForm();

    QGroupBox* groupBox1;	// module list
	QGroupBox* groupBoxVI;	// module path
	QGroupBox* groupBoxPI;	// module path

	QComboBox * comboVI;
	QComboBox * comboPI;

    QTextEdit* textModule;
    QListBox* listModule;
    QPushButton* buttonOk;

    virtual void loadModules( const char * directory );

public slots:
	virtual void selection_changed( QListBoxItem * );
	virtual void selected( int item );

protected slots:
    virtual void languageChange();

private:
	mpdllMgr mgr;

};

#endif // MAINFORM_H
