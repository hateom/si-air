#include <qapplication.h>

/// QT form header
#include "mainform.h"
#include "mp_path.h"

#pragma comment(lib,"qtmain.lib")
#pragma comment(lib,"qt-mt3.lib")

//////////////////////////////////////////////////////////////////////////

int main( int argc, char * argv[] )
{
	mpPath::Single()->Init( GetModuleHandle(NULL) );
	QApplication a( argc, argv );
	MainForm form;

	a.setMainWidget( &form );
	form.show();

	form.loadModules( GETPATH("modules") );

	return( a.exec() );
}

//////////////////////////////////////////////////////////////////////////
