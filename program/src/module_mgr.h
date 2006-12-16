#ifndef __MODULE_MGR_H__
#define __MODULE_MGR_H__

//////////////////////////////////////////////////////////////////////////

#include <qobject.h>
#include <qtimer.h>
#include <vector>
#include <string>
#include "../../modules/module_base/src/module_base.h"

//////////////////////////////////////////////////////////////////////////

class ModuleMgr: public QObject
{
	Q_OBJECT

public:
	ModuleMgr();
	~ModuleMgr();

	int load_modules( std::string directory );
	int unload_modules();

private:
	moduleBase * last_on_path();
	void process_frame();

public slots:
	void clear_path();
	void add_to_path( int module );
	void start_processing();
	void stop_processing();

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

	bool is_running;
	QTimer * timer;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MODULE_MGR_H__
