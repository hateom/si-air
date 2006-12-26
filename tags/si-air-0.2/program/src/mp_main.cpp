#include <qapplication.h>

//#include <qthread.h>
#include "mainform.h"
#include "mp_path.h"

#include "mp_logger.h"
#include "module_mgr.h"
#include "../../modules/module_base/src/exceptions.h"

#pragma comment(lib,"qtmain.lib")
#pragma comment(lib,"qt-mt3.lib")

//////////////////////////////////////////////////////////////////////////
/*
class DllLoader: public QThread
{
public:
	DllLoader() {};
	~DllLoader() {};

	virtual void run()
	{
		sModuleMgr->load_modules( GETPATH("modules") );
	}
};
*/
//////////////////////////////////////////////////////////////////////////

int main( int argc, char * argv[] )
{
	mpLogger::set_output( OT_CONSOLE );
	LOG( "initializing application...\n" );

	QApplication a( argc, argv );
	MainForm form;

	mpPath::Single()->Init( GetModuleHandle(NULL) );

	LOG( "creating main window...\n" );

	a.setMainWidget( &form );
	form.show();

//	LOG( "loading modules...\n" );
//	DllLoader load_dll;
//	load_dll.start();
//	sModuleMgr->load_modules( GETPATH("modules") );

	return( a.exec() );
}

//////////////////////////////////////////////////////////////////////////
