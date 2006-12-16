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

#define MK_PARAM( PP ) ((void*)&PP)
#define REG_PARAM( TYPE, NAME, DESC, DEF_VAL ) \
	register_param( TYPE, MK_PARAM(NAME), #NAME, DESC ); NAME = DEF_VAL;

#define USE_PROPERTY_MGR( MGR ) property_mgr = MGR

//////////////////////////////////////////////////////////////////////////

/// Typy modu³ów - wartosci zwracane przez get_module_type

#define MT_VIDEO_ACQ		0x01
#define MT_PROBABILITY		0x02
#define MT_GESTURES			0x03
#define MT_INPUT			0x04

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
	moduleBase() : lib_handle(NULL) { REG_PARAM( PT_INT, preview_param, "Preview", 0 ); }
	virtual ~moduleBase() { FreeLibrary( lib_handle ); free_params(); }

	/// metoda zwracajaca opis danego modulu
	/// \return opis danego modulu jako tablice znakow
	virtual const char * get_module_description() = 0;

	virtual int  init( PropertyMgr * pm = NULL ) = 0;
	virtual void free() = 0;

	/// zwraca informacja o typie modulu
	/// \return typ modulu zadeklarowany jako MT_*
//	virtual int get_module_type() = 0; <--  depreciated (nie uzywamy juz typow modulow, ale
//											typ zwracany, i pobierany, wiec to jest niepotrzebne
//											prosze usunac we wszystkich modulach ta metode

	virtual int input_type() = 0;
	virtual int output_type() = 0;

	virtual void mouse_select( int sx, int sz, int sw, int sh ) {}

	virtual proc_data * process_frame( proc_data * prev_frame, int * result ) = 0;

	virtual void assign_library_handle( HMODULE hlib ) { lib_handle = hlib; }

public:
	/// parameter functions
	virtual int param_count() { return( (int)param_list.size() ); }
	virtual mb_param * get_param( int no ) { if( no >= 0 && no < param_count() ) return( param_list[no] ); else return( NULL ); }
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
	virtual int register_param( int type, void * value, char * name, char * description )
	{
		if( find_param( name ) != NULL ) return( ST_ALREADY_EXISTS );
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
	template<typename T> int set_param( const char * name, T value )
	{
		mb_param * par;
		par = find_param( name );
		if( !par ) return( -1 );
		*((T*)(par->data)) = value;
		return( 0 );
	}
	template<typename T> int get_param( const char * name, T * result )
	{
		mb_param * par;
		par = find_param( name );
		if( !par ) return( -1 );
		*result =  *((T*)(par->data));
		return( 0 );
	}

protected:
	int preview_param;

	HMODULE lib_handle;
	std::vector<mb_param*> param_list;
	PropertyMgr * property_mgr;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MODULE_BASE_H__
