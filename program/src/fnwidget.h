/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:52
	plik:    	fnwidget
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __FNWIDGET_H__
#define __FNWIDGET_H__

//////////////////////////////////////////////////////////////////////////

#include <qwidget.h>

//////////////////////////////////////////////////////////////////////////

class QPushButton;
class QLineEdit;
class QString;

//////////////////////////////////////////////////////////////////////////

/// kotrolka wyboru pliku z dysku, skladajaca sie z pola edycji, 
/// oraz przycisku, po ktoergo wcisnieciu pokazuje sie dialog z 
/// wyborem pliku
class fnWidget: public QWidget
{
	Q_OBJECT
public:
	fnWidget( QWidget* parent=0, const char* name=0, WFlags f=0 );
	virtual ~fnWidget();

public:
	/// \return nazwa pliku
	QString get_filename();

	/// metoda ustawia wartos pola edycji
	void setText( QString txt );

signals:
	void textChanged();

protected slots:
	void select_file();
	void inTextChanged( const QString & );

private:
	QPushButton * btn_browse;
	QLineEdit   * edt_filename;
};

//////////////////////////////////////////////////////////////////////////

#endif // __FNWIDGET_H__
