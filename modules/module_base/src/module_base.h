/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:50
	plik:    	module_base
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __MODULE_BASE_H__
#define __MODULE_BASE_H__

//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <vector>
#include "mb_param.h"
#include "types.h"
#include "property_mgr.h"

//////////////////////////////////////////////////////////////////////////

#pragma warning ( disable: 4275 )	// templates & dll
#pragma warning ( disable: 4786 )	// exporting STL object
#pragma warning ( disable: 4231 )	// should work :)
#pragma warning ( disable: 4251 )	// std::string & dll

//////////////////////////////////////////////////////////////////////////

/// makro tworzace wskaŸnik typu void
#define MK_PARAM( PP ) ((void*)&PP)

/// makro u³atwiaj¹ce rejestracje parametrów modu³u
#define REG_PARAM( TYPE, NAME, DESC, DEF_VAL ) \
	register_param( TYPE, MK_PARAM(NAME), #NAME, DESC ); NAME = DEF_VAL;

#define REG_PARAM_UNVISIBLE( TYPE, NAME, DESC, DEF_VAL ) \
	register_param( TYPE, MK_PARAM(NAME), #NAME, DESC, 0 ); NAME = DEF_VAL;

/// modu³ korzystaj¹cy z propertyManager-a powinien wywo³aæ to makro 
/// w metodzie inicjalizacyjnej
#define USE_PROPERTY_MGR( MGR ) property_mgr = MGR

//////////////////////////////////////////////////////////////////////////

/// typy modu³ów - wartosci zwracane prze input_type() oraz output_type()
#define MT_NONE				0x00
#define MT_FRAME			0x01
#define MT_PROBDATA			0x02
#define MT_POSGEST			0x03

//////////////////////////////////////////////////////////////////////////

/// tablica opisujaca kazdy z typow modulow 
/// zadeklarowanych powyzej
static char * mt_description[] = { 
	"undefined", 
	"Video Acquisiton Type", 
	"Probability Image Module", 
	"Getures and Position Detection Module", 
	"Input Handler Module",
	0
};

//////////////////////////////////////////////////////////////////////////

/// klasa bazowa dla wszystkich modulow
class __declspec(dllexport) moduleBase
{
public:
	moduleBase() : lib_handle(NULL) { REG_PARAM_UNVISIBLE( PT_INT, preview_param, "Preview", 0 ); }
	virtual ~moduleBase() { free_params(); }

	/// metoda zwracajaca opis danego modulu
	/// \return opis danego modulu jako tablice znakow
	virtual const char * get_module_description() = 0;

	/// metoda inicjalizacyjna, wywolywana tuz przed rozpoczeciem 
	/// przetwarzania obrazu
	/// \param pm	wskaznik do PropertyMgr, inicjalizowany powinien byc
	///				makrem USE_PROPERTY_MGR
	/// \return ST_OK jesli wszystko ok
	virtual int  init( PropertyMgr * pm = NULL ) = 0;

	/// metoda, ktora powinna zwalniac zasoby - wywolywana jest po 
	/// zakonczeniu przetwarzania obrazu
	virtual void free() = 0;

	///zwraca informacje o typie wejsciowym
	/// \return typ wejscia zadeklarowany jako MT_*
	virtual int input_type() = 0;

	/// zwraca informacje o typie wyjsciowym
	/// \return typ wyjscia zadeklarowany jako MT_*
	virtual int output_type() = 0;

	/// metoda jest wywolywana w momencie zaznaczenia fragmentu na oknie podgladu
	/// \param sx wspolrzedna x zaznaczenia
	/// \param sy wspolrzedna y zaznaczenia
	/// \param sw szerokosc zaznaczenia
	/// \param sh wysokosc zaznaczenia
	virtual void mouse_select( int sx, int sy, int sw, int sh ) {}

	/// metoda wywolywana w kazdej ramce przetwarzania obrazu - kluczowa
	/// \param prev_frame informacje pozyskane z poprzedniego modulu
	/// \param result wartosc int zwracajaca status wykonania przetwarzania
	///			      powinna zwracac ST_OK jesli wszystko w porzadku
	/// \return wyjsciowe informacje po przetworzeniu ramki
	virtual proc_data * process_frame( proc_data * prev_frame, int * result ) = 0;

	/// zapisz uchwyt biblioteki DLL danego modulu, by mozliwe bylo bezpieczne
	/// zwolnienie zasobow
	virtual void assign_library_handle( HMODULE hlib ) { lib_handle = hlib; }

	/// metoda zwraca uchwyt biblioteki dll
	virtual HMODULE get_library_handle() { return( lib_handle ); }

public:
	/// zwraca liczbe parametrow modulu
	virtual int param_count() { return( (int)param_list.size() ); }

	/// pobiera parametr o indeksie `no`
	virtual mb_param * get_param( int no ) { if( no >= 0 && no < param_count() ) return( param_list[no] ); else return( NULL ); }

	/// metoda wyszukuje parametru o podanej nazwie
	/// \return strukture przechowujacas informacje o parametrze, lub NULL w 
	///         przypadku nie znalezienia parametru
	virtual mb_param * find_param( const char * param )
	{
		mb_param * par = NULL;
		for( int i=0; i<param_count(); ++i )
		{
			par = get_param( i );
			if( strcmp( par->name, param ) == 0 )
			{
				return( par );
			}
		}
		return( NULL );
	}

	/// metoda rejestruje nowy parametr modulu
	virtual int register_param( int type, void * value, char * name, char * description, int visible = 1 )
	{
		if( find_param( name ) != NULL ) return( ST_ALREADY_EXISTS );
		mb_param * n_param = new mb_param;
		n_param->data = value;
		n_param->type = type;
		n_param->description = strdup( description );
		n_param->name = strdup( name );
		n_param->visible = visible;
		param_list.push_back( n_param );
		return( 0 );
	}

	/// metoda zwalnia zasoby przechowujace informacje o parametrach modulu
	virtual void free_params()
	{
		for( int j=0; j<param_count(); ++j )
		{
			delete [] param_list[j]->name;
			delete [] param_list[j]->description;
			delete param_list[j];
		}
		param_list.clear();
	}

	/// metoda ustawia wartosc istniejacego parametru
	template<typename T> int set_param( const char * name, T value )
	{
		mb_param * par;
		par = find_param( name );
		if( !par ) return( -1 );
		*((T*)(par->data)) = value;
		return( ST_OK );
	}

	/// metoda pobiera wartosc istniejacego parametru
	/// w przypadku gdy parametr nie zostanie znaleziony zwracana jest wartosc -1
	template<typename T> int get_param( const char * name, T * result )
	{
		mb_param * par;
		par = find_param( name );
		if( !par ) return( -1 );
		*result =  *((T*)(par->data));
		return( ST_OK );
	}

protected:
	int preview_param;						/// parametr podgladu
	HMODULE lib_handle;						/// uchwyt biblioteki dll modulu
	std::vector<mb_param*> param_list;		/// wektor parametrow modulu
	PropertyMgr * property_mgr;				/// wskaznik do PropertyMgr
};

//////////////////////////////////////////////////////////////////////////

#endif // __MODULE_BASE_H__
