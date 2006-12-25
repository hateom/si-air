/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:51
	plik:    	mp_logger
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __MP_LOGGER_H__
#define __MP_LOGGER_H__

//////////////////////////////////////////////////////////////////////////

#include <string>

//////////////////////////////////////////////////////////////////////////

/// typ logowania
#define OT_NONE    0x00		/// brak logowania
#define OT_CONSOLE 0x01		/// loguj do konsoli
#define OT_WINDOW  0x02		/// loguj do okienka

//////////////////////////////////////////////////////////////////////////

/// makra ulatwiajace wywolanie loggera
#define LOGF( ARG ) mpLogger::log( "%s [%d]: %s", __FILE__, __LINE__, ARG )
#define LOG mpLogger::log

//////////////////////////////////////////////////////////////////////////

class QTextEdit;

//////////////////////////////////////////////////////////////////////////

class mpLogger
{
public:
	mpLogger();
	virtual ~mpLogger();

	/// ustawia typ wyjscia
	static void set_output( int output_type, QTextEdit * ctrl = NULL );

	/// loguj
	static void log( std::string text );
	static void log( const char * text, ... );

private:
	static int output_type;
	static QTextEdit * te;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MP_LOGGER_H__
