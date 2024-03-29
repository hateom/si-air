/****************************************************************************
** Form interface generated from reading ui file 'mainform.ui'
**
** Created: N 7. sty 15:56:06 2007
**      by: The User Interface Compiler ($Id: main.cpp,v 1.1.1.16 2006/05/05 18:20:12 chehrlic Exp $)
**
** WARNING! All changes made in this file will be lost!
****************************************************************************/

#ifndef MAINFORM_H
#define MAINFORM_H

#include <qvariant.h>
#include <qdialog.h>

#define BUTTONS_COUNT 3

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QSpacerItem;
class QLabel;
class QPushButton;
class QLineEdit;
class QTime;

class MainForm : public QDialog
{
    Q_OBJECT

public:
    MainForm( QWidget* parent = 0, const char* name = 0, bool modal = FALSE, WFlags fl = 0 );
    ~MainForm();

    QLabel* textLabel1;
    QPushButton* btn2;
    QPushButton* btn3;
    QLabel* textLabel3;
    QLabel* textLabel2_2_3;
    QLabel* textLabel2_5;
    QLineEdit* a_edit;
    QLineEdit* b_edit;
    QLabel* textLabel2_4;
    QLabel* time_1;
    QLabel* textLabel2_3_2;
    QLabel* textLabel2_2_2;
    QLabel* time_0;
    QLabel* time_2;
	QLabel* info_label;
    QPushButton* startBtn;
    QPushButton* btn1;
    QPushButton* end_btn;
	QTime* click_time;

public slots:
    virtual int btn1_func();
    virtual int btn2_func();
    virtual int btn3_func();
    virtual int btn0_func();

protected:

protected slots:
    virtual void languageChange();
	virtual void init ();

private:
	int count;
	bool onMove;
	int time_table[BUTTONS_COUNT];
	float a,b;
	char buff[20];
	/// warn. to sa zmienne ktore trzeba by przeliczyc po zmianie rozmiarow czy polozenie
	/// przyciskow !!!!
	/// xn = log2(2A/W + 1) dla kolejnych przyciskow
	float x[BUTTONS_COUNT];


	void calculate();

};

#endif // MAINFORM_H
