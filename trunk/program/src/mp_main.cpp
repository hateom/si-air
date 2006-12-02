#include <qapplication.h>

/// QT form header
#include "mainform.h"
#include "mp_path.h"

#include "mp_logger.h"

#pragma comment(lib,"qtmain.lib")
#pragma comment(lib,"qt-mt3.lib")

//////////////////////////////////////////////////////////////////////////

int main( int argc, char * argv[] )
{
	mpLogger::set_output( OT_CONSOLE );
	LOG( "initializing application...\n" );

	mpPath::Single()->Init( GetModuleHandle(NULL) );

	LOGF( "creating main window...\n" );

	QApplication a( argc, argv );
	MainForm form;

	a.setMainWidget( &form );
	form.show();

	LOG( "loading modules...\n" );
	form.loadModules( GETPATH("modules") );

	return( a.exec() );
}

//////////////////////////////////////////////////////////////////////////
