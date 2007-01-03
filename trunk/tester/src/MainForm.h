/****************************************************************************
** Form interface generated from reading ui file 'MainForm.ui'
**
** Created: Śr 3. sty 22:25:17 2007
**      by: The User Interface Compiler ($Id: main.cpp,v 1.1.1.16 2006/05/05 18:20:12 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MAINFORM_H
#define MAINFORM_H

#include <qvariant.h>
#include <qmainwindow.h>
#include <vector>
#include "my_button.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QPushButton;

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~MainForm();

protected:

protected slots:
    virtual void languageChange();
	virtual void on_click( int id );

private:
	std::vector<myButton*> btn_list;

	int position;
};

#endif // MAINFORM_H
