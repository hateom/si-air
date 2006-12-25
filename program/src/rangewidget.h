#ifndef __RANGE_WIDGET_H__
#define __RANGE_WIDGET_H__

//////////////////////////////////////////////////////////////////////////

#include <qwidget.h>

//////////////////////////////////////////////////////////////////////////

class QLineEdit;
class QSlider;

//////////////////////////////////////////////////////////////////////////

#define RT_INT		0x00
#define RT_FLOAT	0x01

//////////////////////////////////////////////////////////////////////////

class rangeWidget: public QWidget
{
	Q_OBJECT

public:
	rangeWidget( int type = RT_INT, QWidget* parent=0, const char* name=0, WFlags f=0 );
	~rangeWidget();

	void setup( int min, int max, int current );
	void set_minmax( int min, int max );
	void set_value( int value );

	void setup( float min, float max, float current );
	void set_minmax( float min, float max );
	void set_value( float value );
	
	int get_value();
	int get_min();
	int get_max();

	float get_valuef();
	float get_minf();
	float get_maxf();

public slots:
	void slider_changed( int sv );
	void edit_changed();

protected:
	QLineEdit * edit;
	QSlider * slider;

	int value;
	int min_value;
	int max_value;

	float valuef;
	float min_valuef;
	float max_valuef;

	int type;
	int slider_lock;
};

//////////////////////////////////////////////////////////////////////////

#endif // __RANGE_WIDGET_H__
