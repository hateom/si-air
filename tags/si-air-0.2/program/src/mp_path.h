/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:51
	plik:    	mp_path
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __MP_PATH_H__
#define __MP_PATH_H__

//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <iostream>

//////////////////////////////////////////////////////////////////////////

/// makro ulatwiajace korzystanie z obiektu globalnego
#define GETPATH( NFILE ) mpPath::Single()->GetFullPath( NFILE )

//////////////////////////////////////////////////////////////////////////

/// Klasa przechowujaca katalog w ktorym znajduje sie program glowny
class mpPath
{
public:
	mpPath();
	virtual ~mpPath();

	/// inicjalizacja obiektu
	bool Init( HINSTANCE hInst );

	/// metoda zwraca pelna sciezke dostepu do programu glownego
	char * GetFullPath( char * file );

	/// metoda zwraca wskaznik do obiektu globalnego
	static mpPath * Single()
	{
		static mpPath singleton;
		return( &singleton );
	}

private:
	std::string dir;
	bool created;
	char separator;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MP_PATH_H__
