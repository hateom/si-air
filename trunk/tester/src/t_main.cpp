#include <qapplication.h>
#include "MainForm.h"

#pragma comment(lib,"qtmain.lib")
#pragma comment(lib,"qt-mt3.lib")

int main( int argc, char * argv[] )
{
	QApplication app( argc, argv );
	MainForm mf;

	mf.show();

	return( app.exec() );
}
