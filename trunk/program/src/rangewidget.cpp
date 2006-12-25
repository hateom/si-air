#include "rangewidget.h"

#include <qlineedit.h>
#include <qslider.h>

//////////////////////////////////////////////////////////////////////////

rangeWidget::rangeWidget( int t, QWidget* parent, const char* name, WFlags f ) : 
	QWidget( parent, name, f ), type(t), slider_lock(0)
{
	edit = new QLineEdit( this, tr("editBox") );
	edit->setGeometry( QRect( 0, 0, 60, 24 ) );

	slider = new QSlider( this, tr("slider") );
	slider->setGeometry( QRect( 65, 0, 160, 24 ) );
	slider->setOrientation( Horizontal );
	slider->setMaxValue( 100 );
	slider->setMinValue( 0 );

	connect( slider, SIGNAL(sliderMoved(int)), this, SLOT(slider_changed(int)) );
	connect( edit, SIGNAL(textChanged()), this, SLOT(edit_changed()) );
}

//////////////////////////////////////////////////////////////////////////

rangeWidget::~rangeWidget()
{
}

//////////////////////////////////////////////////////////////////////////

void rangeWidget::setup( int min, int max, int current )
{
	min_value = min;
	max_value = max;
	value = current;

	edit->setText( QString().number(current) );
	edit_changed();
}

//////////////////////////////////////////////////////////////////////////

void rangeWidget::setup( float min, float max, float current )
{
	min_valuef = min;
	max_valuef = max;
	valuef = current;

	edit->setText( QString().number(current) );
	edit_changed();
}

//////////////////////////////////////////////////////////////////////////

void rangeWidget::set_minmax( int min, int max )
{
	min_value = min;
	max_value = max;

	edit_changed();
}

//////////////////////////////////////////////////////////////////////////

void rangeWidget::set_minmax( float min, float max )
{
	min_valuef = min;
	max_valuef = max;

	edit_changed();
}

//////////////////////////////////////////////////////////////////////////

void rangeWidget::set_value( int val )
{
	value = val;

	edit->setText( QString().number(val) );
	edit_changed();
}

//////////////////////////////////////////////////////////////////////////

void rangeWidget::set_value( float val )
{
	valuef = val;

	edit->setText( QString().number(val) );
	edit_changed();
}

//////////////////////////////////////////////////////////////////////////

int rangeWidget::get_value()
{
	return( value );
}

//////////////////////////////////////////////////////////////////////////

float rangeWidget::get_valuef()
{
	return( valuef );
}

//////////////////////////////////////////////////////////////////////////

int rangeWidget::get_min()
{
	return( min_value );
}

//////////////////////////////////////////////////////////////////////////

float rangeWidget::get_minf()
{
	return( min_valuef );
}

//////////////////////////////////////////////////////////////////////////

int rangeWidget::get_max()
{
	return( max_value );
}

//////////////////////////////////////////////////////////////////////////

float rangeWidget::get_maxf()
{
	return( max_valuef );
}

//////////////////////////////////////////////////////////////////////////

void rangeWidget::slider_changed( int sv )
{
	slider_lock = 1;

	if( type == RT_INT )
	{
		float perc = ((float)sv)*0.01f;
		value = min_value + (int)(((float)(max_value-min_value))*perc);
		edit->setText( QString().number(value) );
	}
	else
	{
		float perc = ((float)sv)*0.01f;
		valuef = min_valuef + (((float)(max_valuef-min_valuef))*perc);
		edit->setText( QString().number(valuef) );
	}

	slider_lock = 0;
}

//////////////////////////////////////////////////////////////////////////

void rangeWidget::edit_changed()
{
	QString str = edit->text();

	if( type == RT_INT )
	{
		value = str.toInt();
		float perc = (float)(min_value+value)/(float)(max_value-min_value);

		if( !slider_lock ) slider->setValue( (int)(perc*100.0f) );
	}
	else
	{
		valuef = str.toFloat();
		float perc = (min_valuef+valuef)/(max_valuef-min_valuef);
		if( !slider_lock ) slider->setValue( (int)(perc*100.0f) );
	}
}

//////////////////////////////////////////////////////////////////////////
