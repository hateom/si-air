#include "module_mgr.h"
#include "mp_logger.h"
#include "preview_mgr.h"
#include "../../modules/module_base/src/status_codes.h"

//////////////////////////////////////////////////////////////////////////

#define NO_PREVIEW -1

//////////////////////////////////////////////////////////////////////////

typedef moduleBase * (*t_export_func)();

//////////////////////////////////////////////////////////////////////////

static ModuleMgr modmgr_single;

//////////////////////////////////////////////////////////////////////////

ModuleMgr * ModuleMgr::singleton()
{
	return( &modmgr_single );
}

//////////////////////////////////////////////////////////////////////////

int ModuleMgr::remove_module( moduleBase * mod )
{
	if( !mod ) return( -1 );

	int path_size = (int)path_list.size();

	if( module_list[path_list[path_size-1]] == mod )
	{
		path_list.pop_back();
		emit module_removed();
		LOG( ">>> Module <%s> unloaded.\n", mod->get_module_description() );
	}
	else
	{
		LOG( ">>> ERROR: You can delete only the last module.\n" );
		return( -1 );
	}

	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

bool has_preview( moduleBase * mod )
{
	int has_preview = 0;

	if( !mod ) return( false );

	if( mod->get_param( "preview_param", &has_preview ) == ST_OK )
	{
		if( has_preview )
		{
			return( true );
		}
	}

	return( false );
}

//////////////////////////////////////////////////////////////////////////

ModuleMgr::ModuleMgr() : is_running(false), timer(NULL)
{
}

//////////////////////////////////////////////////////////////////////////

ModuleMgr::~ModuleMgr()
{
}

//////////////////////////////////////////////////////////////////////////

int ModuleMgr::load_single_module( std::string filename )
{
	t_export_func export_func;
	moduleBase * base;
	HMODULE hdll;

	hdll = LoadLibrary( filename.c_str() );

	if( !hdll && GetLastError() == 112 )
	{
		// missing static linked dll
		return( ST_MISSING_DLL );
	}

	export_func = (t_export_func)GetProcAddress( hdll, "export_module" );
	if( !export_func )
	{
		FreeLibrary( hdll );
		return( ST_UNKNOWN_MODULE );
	}

	base = export_func();
	if( !base )
	{
		FreeLibrary( hdll );
		return( ST_EXPORT_ERROR );
	}

	base->assign_library_handle( hdll );
	emit module_loaded( base, (int)module_list.size() );
	module_list.push_back( base );

	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

int ModuleMgr::load_modules( std::string directory )
{
	WIN32_FIND_DATA find_data;
	HANDLE			hfind;

	std::string filename;
	std::string dir_ext;

	dir_ext = directory + std::string("\\*.dll");

	hfind = FindFirstFile( dir_ext.c_str(), &find_data );

	do 
	{
		if( hfind == INVALID_HANDLE_VALUE )
		{
			LOG( "Invalid File Handle. GetLastError reports %d (maybe there are no modules? Chckout /modules direcory.)\n", GetLastError() );
			break;
		} 
		else 
		{
			LOG( ">>> found: %s ", find_data.cFileName );
			filename = directory + std::string("\\") + std::string(find_data.cFileName);
			if( load_single_module( filename ) == ST_OK )
			{
				LOG( "[ OK ]\n" );
			}
			else
			{
				LOG( "[ !! ]\n" );
			}
		}
	} while( FindNextFile( hfind, &find_data ));

	FindClose( hfind );

	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

int ModuleMgr::unload_modules()
{
	HMODULE hdll;
	moduleBase * mod;
	int size = (int)module_list.size();

	if( !size ) return( ST_OK );

	LOG( ">>> unloading modules...\n" );

	for( int i=0; i<size; ++i )
	{
		mod = module_list[i];
		LOG( "    >> unloading `%s`\n", mod->get_module_description() );
		emit module_unload( mod, i );
		hdll = mod->get_library_handle();
		mod->free();
		delete mod;
		if( !FreeLibrary( hdll ) )
		{
			LOG( "!!! `FreeLibrary` failed\n");
		}
	}

	module_list.clear();

	LOG( ">>> modules unloaded safely.\n" );

	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void ModuleMgr::clear_path()
{
	if( is_running )
	{
		LOG( "!!! Processing is still running!\n" );
		return;
	}

	path_list.clear();
	emit path_cleared();
}

//////////////////////////////////////////////////////////////////////////

moduleBase * ModuleMgr::last_on_path()
{
	if( path_list.size() == 0 ) return( NULL );
	return( module_list[path_list[path_list.size()-1]] );
}

//////////////////////////////////////////////////////////////////////////

void ModuleMgr::add_to_path( int module )
{
	if( path_list.size() == 6 )
	{
		LOG( "!!! Module path limit is 6!\n" );
		return;
	}

	moduleBase * mod;
	mod = module_list[module];

	if( !last_on_path() )
	{
		if( mod->input_type() != MT_NONE )
		{
			LOG( "!!! First module must have no inputs!\n" );
			return;
		}
	}
	else if(  last_on_path()->output_type() != mod->input_type() )
	{
		LOG( "!!! Module type mismatch!\n" );
		return;
	}

	path_list.push_back( module );
	emit added_to_path( module_list[module], module );
}

//////////////////////////////////////////////////////////////////////////

void ModuleMgr::add_to_path( moduleBase * mod )
{
	int size = (int)module_list.size();
	for( int i=0; i<size; ++i )
	{
		if( module_list[i] == mod ) add_to_path( i );
	}
}

//////////////////////////////////////////////////////////////////////////

void ModuleMgr::start_processing()
{
	moduleBase * mod;
	int size = (int)path_list.size();
	int result;

	property_mgr.release();

	for( int i=0; i<size; ++i )
	{
		mod = module_list[path_list[i]];
		if( !mod ) return;

		result = mod->init( &property_mgr );

		if( result != ST_OK )
		{
			LOG( "!!! Initialization module error <%d>!\n", i );
			return;
		}

		if( has_preview( mod ) )
		{
			prev_list.push_back( sPreviewMgr->register_preview() + (1<<16) );
			sPreviewMgr->show_window( prev_list[i] & 0x0000FFFF, true );
		}
		else
		{
			prev_list.push_back( sPreviewMgr->register_preview() + (NO_PREVIEW<<16) );
		}
	}

	timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()), this, SLOT(process_frame()));
	connect( sPreviewMgr, SIGNAL(mouse_select(int,int,int,int)), this, SLOT(mouse_select(int,int,int,int)) );

	emit processing_started();
	LOG( ">>> processing started...\n" );

	timer->start( 40 );

	is_running = true;
}

//////////////////////////////////////////////////////////////////////////

void ModuleMgr::stop_processing()
{
	if( !is_running ) return;

	if( timer != NULL )
	{
		timer->stop();
		delete timer;
		timer = NULL;
	}

	is_running = false;
	prev_list.clear();

	moduleBase * mod;
	int size = (int)path_list.size();

	for( int i=0; i<size; ++i )
	{
		mod = module_list[path_list[i]];
		mod->free();
	}

	disconnect( sPreviewMgr, SIGNAL(mouse_select(int,int,int,int)), this, SLOT(mouse_select(int,int,int,int)) );

	sPreviewMgr->close_all();

	emit processing_finished();
	LOG( ">>> processing finished.\n" );
}

//////////////////////////////////////////////////////////////////////////

void ModuleMgr::process_frame()
{
	int result;
	int size = (int)path_list.size();
	moduleBase * mod;
	proc_data * arg = NULL, * res = NULL;

	try 
	{
		for( int i=0; i<size; ++i )
		{
			mod = module_list[path_list[i]];
			if( !mod ) throw -1;
			res = mod->process_frame( arg, &result );

			if( result != ST_OK ) 
			{
				stop_processing();
				return;
			}

			if( ( prev_list[i] >> 16 ) != NO_PREVIEW )
			{
//				sPreviewMgr->show_window( prev_list[i] & 0x0000FFFF, true );
				sPreviewMgr->render_frame( prev_list[i] & 0x0000FFFF, res->frame );
			}
			arg = res;
		}
	}
	catch( ... )
	{
		LOG( "!!! frame processing exception.\n" );
		stop_processing();
	}
}

//////////////////////////////////////////////////////////////////////////

void ModuleMgr::mouse_select( int sx, int sy, int sw, int sh )
{
	int size = (int)path_list.size();
	moduleBase * mod;

	for( int i=0; i<size; ++i )
	{
		mod = module_list[path_list[i]];
		if( mod ) mod->mouse_select( sx, sy, sw, sh );
	}
}

//////////////////////////////////////////////////////////////////////////

int ModuleMgr::find_module_preview( moduleBase * mod )
{
	if( !mod ) return( -1 );

	for( int i=0; i<(int)module_list.size(); ++i )
	{
		if( module_list[i] == mod )
		{
			for( int j=0; j<(int)path_list.size(); ++j )
			{
				if( i == path_list[j] )
				{
					return( j );
				}
			}
		}
	}

	return( -1 );
}

//////////////////////////////////////////////////////////////////////////

void ModuleMgr::switch_preview( moduleBase * mod, bool on )
{
	if( !is_running ) return;
	for( int i=0; i<(int)module_list.size(); ++i )
	{
		if( mod == module_list[i] )
		{
			switch_preview( i, on );
			return;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void ModuleMgr::switch_preview( int module, bool on )
{
	if( !is_running ) return;
	if( module < 0 || module >= (int)module_list.size() ) return;

	moduleBase * mod;
	mod = module_list[module];
	if( !mod ) return;

	int prv_wnd;
	if( (prv_wnd = find_module_preview( mod )) < 0 ) return;

	if( on )
	{
		sPreviewMgr->show_window( prev_list[prv_wnd] & 0x0000FFFF, true );
		prev_list[prv_wnd] = prev_list[prv_wnd] & 0x0000FFFF + (1<<16);
	}
	else
	{
		sPreviewMgr->show_window( prev_list[prv_wnd] & 0x0000FFFF, false );
		prev_list[prv_wnd] = prev_list[prv_wnd] & 0x0000FFFF + (NO_PREVIEW<<16);
	}


}

//////////////////////////////////////////////////////////////////////////

int ModuleMgr::get_proper_modules( std::vector<moduleBase*> & list )
{
	moduleBase * mod;
	int size = (int)module_list.size();
	

	for( int i=0; i<size; ++i )
	{
		mod = module_list[i];

		if( !last_on_path() )
		{
			if( mod->input_type() == MT_NONE )
			{
				list.push_back( mod );
			}
		}
		else if( last_on_path()->output_type() == mod->input_type() && 
				 last_on_path()->output_type() != MT_NONE )
		{
			list.push_back( mod );
		}
	}

	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////
