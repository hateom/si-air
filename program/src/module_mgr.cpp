#include "module_mgr.h"
#include "mp_logger.h"
#include "../../modules/module_base/src/status_codes.h"

//////////////////////////////////////////////////////////////////////////

typedef moduleBase * (*t_export_func)();

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
			LOG( "Invalid File Handle. GetLastError reports %d\n", GetLastError() );
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

	for( int i=0; i<size; ++i )
	{
		mod = module_list[i];
		emit module_unload( mod, i );
		hdll = mod->get_library_handle();
		mod->free();
		delete mod;
		if( !FreeLibrary( hdll ) )
		{
			LOG( "!!! `LoadLibrary` failed\n");
		}
	}

	module_list.clear();

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

	emit path_cleared();
	path_list.clear();
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
	if( path_list.size() == 9 )
	{
		LOG( "!!! Module path limit is 9!\n" );
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

	emit added_to_path( module_list[module], module );
	path_list.push_back( module );
}

//////////////////////////////////////////////////////////////////////////

void ModuleMgr::start_processing()
{
	moduleBase * mod;
	int size = (int)path_list.size();
	int result;

	for( int i=0; i<size; ++i )
	{
		mod = module_list[path_list[i]];
		if( !mod ) return;

		result = mod->init( /*&property_mgr*/ );

		if( result != ST_OK )
		{
			LOG( "!!! Initialization module error <%d>!\n", i );
			return;
		}
/*
		if( wdg->has_preview() )
		{
			PrevForm * pf;
			pf = new PrevForm( mod, previous );
			wdg->set_preview( pf );
			pf->move( QPoint( poss2[prv_wnd*2], poss2[prv_wnd*2+1] ) );
			pf->show();
			prv_wnd++;
			previous = pf;
		}
*/
	}

	timer = new QTimer( this );
	connect( timer, SIGNAL(timeout()), this, SLOT(process_frame()));
	
	emit processing_started();

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

	emit processing_finished();
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
/*
			if( mod_widget[i]->has_preview() )
			{
				mod_widget[i]->get_preview()->render_frame( res->frame );
			}
*/
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

