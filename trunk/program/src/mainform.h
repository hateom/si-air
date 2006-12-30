#ifndef MAINFORM_H
#define MAINFORM_H

#include <qvariant.h>
#include <qpixmap.h>
#include <qmainwindow.h>

#include <vector>
#include "../../modules/module_base/src/module_base.h"
#include "modwidget.h"
#include "processing_panel.h"
#include "options_box.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QFrame;
class QLabel;
class QGroupBox;
class QPushButton;
class QTextEdit;
class QToolButton;

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    MainForm( QWidget* parent = 0, const char* name = 0, WFlags fl = WType_TopLevel );
    ~MainForm();

    procFrame* frame3;
    QLabel* processingImg;
	QLabel* headImg;
    OptionsBox* optionsBox;
    QGroupBox* panelGroup;
    QToolButton* startButton;
    QToolButton* reloadButton;
    QTextEdit* textEdit1;
    QMenuBar *MenuBarEditor;
    QPopupMenu *Processing;
    QPopupMenu *About;
    QAction* procExitAction;
	QAction* procStartAction;
	QAction* procClearAction;
	QAction* aboutAction;
	QToolButton	* buttonReset;
	QLabel *labelInfo;

public slots:
	virtual void module_loaded( moduleBase * base, int no );
	virtual void module_unload( moduleBase * base, int no );
	virtual void added_to_path( moduleBase * base, int no );
	virtual void path_cleared();
	virtual void processing_started();
	virtual void processing_finished();
	virtual void add_module( moduleBase * mod );

	virtual void run();
	virtual void stop();

	virtual void close_app();
//	virtual void lb_selected( QListBoxItem * );

	virtual void load_modules();
	virtual void module_removed();

	virtual void showAbout();

protected slots:
	virtual void languageChange();
	virtual void update_popup();

private:
	void closeEvent( QCloseEvent * ce );
	std::vector<modWidget*>		mod_widget;
    QPixmap image0;
	QPixmap image1;

	QPixmap btn_reload;
	QPixmap btn_clear;
	QPixmap btn_start;
};

#endif // MAINFORM_H
