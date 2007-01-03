#ifndef __MY_BUTTON_H__
#define __MY_BUTTON_H__

//////////////////////////////////////////////////////////////////////////

#include <qpushbutton.h>

//////////////////////////////////////////////////////////////////////////

class myButton: public QPushButton
{
	Q_OBJECT

public:
	myButton( int id, QWidget * parent = NULL, const char * name = 0 );
	~myButton();

	int get_id();

signals:
	void clicked( int id );

private slots:
	void on_click();

protected:
	int id;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MY_BUTTON_H__
