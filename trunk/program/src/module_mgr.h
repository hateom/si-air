/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:51
	plik:    	module_mgr
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __MODULE_MGR_H__
#define __MODULE_MGR_H__

//////////////////////////////////////////////////////////////////////////

#include <qobject.h>
#include <qtimer.h>
#include <vector>
#include <string>
#include "../../modules/module_base/src/module_base.h"
#include "../../modules/module_base/src/property_mgr.h"

//////////////////////////////////////////////////////////////////////////

#define sModuleMgr ModuleMgr::singleton()

//////////////////////////////////////////////////////////////////////////

class ModuleMgr: public QObject
{
	Q_OBJECT

public:
	ModuleMgr();
	~ModuleMgr();

	int load_modules( std::string directory );
	int unload_modules();

	static ModuleMgr * singleton();

private:
	moduleBase * last_on_path();

public slots:
	void clear_path();
	void add_to_path( int module );
	void start_processing();
	void stop_processing();
	void process_frame();
	void mouse_select( int sx, int sy, int sw, int sh );

	void switch_preview( int module, bool on );

signals:
	void module_loaded( moduleBase * base, int no );
	void module_unload( moduleBase * base, int no );
	void added_to_path( moduleBase * base, int no );
	void path_cleared();
	void processing_started();
	void processing_finished();

private:
	int load_single_module( std::string filename );
	std::vector<moduleBase*> module_list;
	std::vector<int> path_list;
	std::vector<int> prev_list;

	bool is_running;
	QTimer * timer;
	PropertyMgr property_mgr;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MODULE_MGR_H__
