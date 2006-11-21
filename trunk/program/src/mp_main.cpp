#include <qapplication.h>

/// QT form header
#include "mainform.h"

#pragma comment(lib,"qtmain.lib")
#pragma comment(lib,"qt-mt3.lib")

//////////////////////////////////////////////////////////////////////////

int main( int argc, char * argv[] )
{
	QApplication a( argc, argv );
	MainForm form;

	a.setMainWidget( &form );
	form.show();

	form.loadModules( "G:\\si_svn\\program\\bin\\modules" );

	return( a.exec() );
}

//////////////////////////////////////////////////////////////////////////

/*
mpdllMgr mgr;

mgr.read_module_directory( "G:\\si_project\\modules\\video_acq_opencv\\bin" );
mp_dll_module * mod = mgr.get_module_info( 0 );
if( mod )
{
vaBase * va_mod = mgr.load_va_module( mod );
if( va_mod )
{
printf( "Module %s loaded succefully!\n", mod->description.c_str() );
if( va_mod->init( 0, "G:\\si_project\\program\\bin\\movie.avi" ) == 0 )
{
int result = 0;
frame_data * data;

data = va_mod->process_frame( &result );

if( result == 0 )
{
printf( "Frame processed! [%dx%d in %d bpp]\n", data->width, data->height, 8*data->depth );
}
else
{
printf( "ERROR! Cannot get frame! (%d)\n", result );
}
}
else
{
printf( "ERROR: Cannot init module!\n" );
}

va_mod->free();
}
else
{
printf( "ERROR: Cannot load module!\n" );
}
}
else
{
printf( "ERROR: Cannot find any modules!\n" );
}
mgr.free();


return( 0 );
*/