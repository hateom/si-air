/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:50
	plik:    	exceptions
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

//////////////////////////////////////////////////////////////////////////

#include <string>

//////////////////////////////////////////////////////////////////////////

/// makro assert implementowane tylko w wersji DEBUG projektu

#ifdef _DEBUG
#define MB_ASSERT( MSG, EXP ) if( !(EXP) ) { throw mbException( MSG, #EXP, __FILE__, __LINE__ ); }
#else
#define MB_ASSERT( MSG, EXP )
#endif

//////////////////////////////////////////////////////////////////////////

/// klasa reprezentujaca wyjatek
class __declspec(dllexport) mbException
{
public:
	/// konstruktor zbierajacy mozliwie jak najwiecej informacji o wyjatku
	mbException( const char * ms, const char * ex, const char * fil, int lin ) : 
		line( lin ), msg( ms ), exp( ex ), file( fil ) {}
	~mbException() {}

	/// metoda zwracajaca opis wyjatku w sformatowanej formie
	const char * show()
	{
		static char buffer[256] = "";
		sprintf( buffer, "%s at %d> `%s` : %s", file.c_str(), line, exp.c_str(), msg.c_str() );
		return( buffer );
	}

private:
	int line;
	std::string msg, exp, file;
};

//////////////////////////////////////////////////////////////////////////

#endif // __EXCEPTIONS_H__
