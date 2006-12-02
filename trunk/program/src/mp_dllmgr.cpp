#include "mp_dllmgr.h"
#include "../../modules/module_base/src/module_base.h"
#include <windows.h>
#include "mp_logger.h"

//////////////////////////////////////////////////////////////////////////

typedef moduleBase *	(*t_export_func)();
typedef vaBase *		(*t_export_va_func)();
typedef piBase *		(*t_export_pi_func)();
typedef pdBase *		(*t_export_pd_func)();

//////////////////////////////////////////////////////////////////////////

mpdllMgr::mpdllMgr()
{

}

//////////////////////////////////////////////////////////////////////////

mpdllMgr::~mpdllMgr()
{
	free();
}

//////////////////////////////////////////////////////////////////////////

int mpdllMgr::read_module_directory( std::string directory )
{
	WIN32_FIND_DATA find_data;
	HANDLE			hfind;
	int				err_no;

	std::string dir_ext;
	dir_ext = directory + std::string("\\*.dll");

	hfind = FindFirstFile( dir_ext.c_str(), &find_data );

	do 
	{
		if( hfind == INVALID_HANDLE_VALUE )
		{
			LOG( "Invalid File Handle. GetLastError reports %d\n", GetLastError() );
			break;
		} 
		else 
		{
			LOG( "* found: %s ", find_data.cFileName );
			mp_dll_module * item = new mp_dll_module;
			item->filename = directory + std::string("\\") + std::string(find_data.cFileName);
			if( ( err_no = get_module_information( item ) ) == 0 )
			{
				list.push_back( item );
				LOG( "OK\n", item->description.c_str(), mt_description[item->type] );
			}
			else
			{
				delete item;
				LOG( "Failed! (errno: %d)\n", err_no );
			}
		}
	} while( FindNextFile( hfind, &find_data ));

	FindClose( hfind );

	return( 0 );
}

//////////////////////////////////////////////////////////////////////////

int mpdllMgr::get_module_information( mp_dll_module * item )
{
	if( !item ) return( -1 );

	t_export_func export_func;
	moduleBase * base;

	HMODULE hdll;

	hdll = LoadLibrary( item->filename.c_str() );

	if( !hdll && GetLastError() == 112 )
	{
		// missing static linked dll
		return( -4 );
	}

	export_func = (t_export_func)GetProcAddress( hdll, "export_module" );
	if( !export_func )
	{
		FreeLibrary( hdll );
		return( -2 );
	}

	base = export_func();
	if( base )
	{
		item->description = std::string( base->get_module_description() );
		item->type = base->get_module_type();
	}
	else
	{
		FreeLibrary( hdll );
		return( -3 );
	}

	FreeLibrary( hdll );
	return( 0 );
}

//////////////////////////////////////////////////////////////////////////

pdBase * mpdllMgr::load_pd_module( mp_dll_module * item )
{
	if( !item ) return( NULL );

	t_export_pd_func export_func;
	pdBase * base;

	HMODULE hdll;

	hdll = LoadLibrary( item->filename.c_str() );

	export_func = (t_export_pd_func)GetProcAddress( hdll, "export_module" );
	if( !export_func )
	{
		FreeLibrary( hdll );
		return( NULL );
	}

	base = export_func();
	if( base )
	{
		base->assign_library_handle( hdll );
		return( base );
	}
	else
	{
		FreeLibrary( hdll );
		return( NULL );
	}

	return( NULL );
}

//////////////////////////////////////////////////////////////////////////

piBase * mpdllMgr::load_pi_module( mp_dll_module * item )
{
	if( !item ) return( NULL );

	t_export_pi_func export_func;
	piBase * base;

	HMODULE hdll;

	hdll = LoadLibrary( item->filename.c_str() );

	export_func = (t_export_pi_func)GetProcAddress( hdll, "export_module" );
	if( !export_func )
	{
		FreeLibrary( hdll );
		return( NULL );
	}

	base = export_func();
	if( base )
	{
		base->assign_library_handle( hdll );
		return( base );
	}
	else
	{
		FreeLibrary( hdll );
		return( NULL );
	}

	return( NULL );
}

//////////////////////////////////////////////////////////////////////////

vaBase * mpdllMgr::load_va_module( mp_dll_module * item )
{
	if( !item ) return( NULL );

	t_export_va_func export_func;
	vaBase * base;

	HMODULE hdll;

	hdll = LoadLibrary( item->filename.c_str() );

	export_func = (t_export_va_func)GetProcAddress( hdll, "export_module" );
	if( !export_func )
	{
		FreeLibrary( hdll );
		return( NULL );
	}

	base = export_func();
	if( base )
	{
		base->assign_library_handle( hdll );
		return( base );
	}
	else
	{
		FreeLibrary( hdll );
		return( NULL );
	}

	return( NULL );
}

//////////////////////////////////////////////////////////////////////////

void mpdllMgr::free()
{
	for( int i=0; i<(int)list.size(); ++i )
	{
		delete list[i];
	}
	list.clear();
}

//////////////////////////////////////////////////////////////////////////

int mpdllMgr::count()
{
	return( (int)list.size() );
}

//////////////////////////////////////////////////////////////////////////

mp_dll_module * mpdllMgr::get_module_info( int item_no )
{
	if( item_no < 0 || item_no >= count() ) return( NULL );
	return( list[item_no] );
}

//////////////////////////////////////////////////////////////////////////
