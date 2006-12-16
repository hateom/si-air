#include <qapplication.h>

/// QT form header
#include "mainform.h"
#include "mp_path.h"

#include "mp_logger.h"

#include "../../modules/module_base/src/exceptions.h"

#pragma comment(lib,"qtmain.lib")
#pragma comment(lib,"qt-mt3.lib")

//////////////////////////////////////////////////////////////////////////

int main( int argc, char * argv[] )
{
/*
	try
	{
		MB_ASSERT( "TEST", 1 == 0 );
	}
	catch( mbException & e )
	{
		printf( "!!! %s\n", e.show() );
	}

*/
	mpLogger::set_output( OT_CONSOLE );
	LOG( "initializing application...\n" );

	QApplication a( argc, argv );
	MainForm form;

	mpPath::Single()->Init( GetModuleHandle(NULL) );

	LOG( "creating main window...\n" );

	a.setMainWidget( &form );
	form.show();

	LOG( "loading modules...\n" );
	form.loadModules( GETPATH("modules") );

	return( a.exec() );
}

//////////////////////////////////////////////////////////////////////////
