#ifndef __MODULE_BASE_H__
#define __MODULE_BASE_H__

//////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <vector>
#include "mb_param.h"

//////////////////////////////////////////////////////////////////////////

#pragma warning ( disable: 4275 )	// templates & dll
#pragma warning ( disable: 4786 )	// exporting STL object
#pragma warning ( disable: 4231 )	// should work :)
#pragma warning ( disable: 4251 )	// std::string & dll

//////////////////////////////////////////////////////////////////////////

/// Typy modu³ów - wartosci zwracane przez get_module_type

#define MT_VIDEO_ACQ		0x01
#define MT_PROBABILITY		0x02
#define MT_GESTURES			0x03
#define MT_INPUT			0x04

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
	moduleBase() : lib_handle(NULL) {}
	virtual ~moduleBase() { FreeLibrary( lib_handle ); free_params(); }

	/// metoda zwracajaca opis danego modulu
	/// \return opis danego modulu jako tablice znakow
	virtual const char * get_module_description() = 0;

	/// zwraca informacja o typie modulu
	/// \return typ modulu zadeklarowany jako MT_*
	virtual int get_module_type() = 0;

	virtual void assign_library_handle( HMODULE hlib ) { lib_handle = hlib; }

public:
	/// parameter functions
	virtual int param_count() { return( (int)param_list.size() ); }
	virtual mb_param * get_param( int no ) { if( no >= 0 && no < param_count() ) return( param_list[no] ); else return( NULL ); }
	virtual int register_param( int type, void * value, char * name, char * description )
	{
		mb_param * n_param = new mb_param;
		n_param->data = value;
		n_param->type = type;
		n_param->description = strdup( description );
		n_param->name = strdup( name );
		param_list.push_back( n_param );
		return( 0 );
	}
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

protected:
	HMODULE lib_handle;
	std::vector<mb_param*> param_list;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MODULE_BASE_H__
