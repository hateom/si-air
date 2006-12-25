#define MOD_CPP
#include "va_opencv.h"
#include "../../module_base/src/types.h"
#include "../../module_base/src/status_codes.h"
#include "../../module_base/src/property_mgr.h"

//////////////////////////////////////////////////////////////////////////

#include <cv.h>
#include <highgui.h>
#include <cvcam.h>

#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cvcam.lib")
#pragma comment(lib,"cxcore.lib")
#pragma comment(lib,"cvaux.lib")
#pragma comment(lib,"ml.lib")
#pragma comment(lib,"highgui.lib")

//////////////////////////////////////////////////////////////////////////

vaOpenCV::vaOpenCV() : capture(NULL), alloc_mem(0)
{
	REG_PARAM( PT_INT,      device,   "device no", 0 );
	REG_PARAM( PT_FILENAME, filename, "filename", 0 );

	set_param( "preview_param", 1 );
}

//////////////////////////////////////////////////////////////////////////

vaOpenCV::~vaOpenCV()
{
}

//////////////////////////////////////////////////////////////////////////

const char * vaOpenCV::get_module_description()
{
	static char descritpion[] = "OpenCV Acquisition module";
	return( descritpion );
}

//////////////////////////////////////////////////////////////////////////

int vaOpenCV::input_type()
{
	return( MT_NONE );
}

//////////////////////////////////////////////////////////////////////////

int vaOpenCV::output_type()
{
	return( MT_FRAME );
}

//////////////////////////////////////////////////////////////////////////

int vaOpenCV::init( PropertyMgr * pm )
{
	USE_PROPERTY_MGR( pm );

	if( capture != NULL ) free();
	if( ( filename != NULL ) && ( strcmp( filename, "" ) != 0 ) )
	{
		capture = cvCaptureFromFile( filename );
	}
	else
	{
		capture = cvCaptureFromCAM( device );
	}
	
	if( !capture )
	{
		return( ST_DEVICE_NOT_FOUND );
	}

	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

proc_data * vaOpenCV::process_frame( proc_data * prev_frame, int * result )
{
	if( !capture ) 
	{
		*result = ST_DEVICE_NOT_FOUND;
		return( NULL );
	}


	IplImage * frame = cvQueryFrame( capture );
	if( !frame )
	{
		*result = ST_FRAME_ERROR;
		return( NULL );
	}

	static frame_data static_frame;
	static proc_data p_data = { 0, 0, 0, 0 };

	static_frame.depth = 4;
	static_frame.width = frame->width;
	static_frame.height = frame->height;

	if( alloc_mem == 0 )
	{
		alloc_mem = static_frame.depth*static_frame.height*static_frame.width;
		static_frame.bits = new unsigned char[alloc_mem];
	}
	else
	{
		if( alloc_mem != frame->depth*frame->height*frame->width )
		{
			delete [] static_frame.bits;
			alloc_mem = static_frame.depth*static_frame.height*static_frame.width;
			static_frame.bits = new unsigned char[alloc_mem];
		}
	}

	long offs1, offs2, aof1, aof2;

	for( int y=0; y<(int)static_frame.height; ++y )
	{
		aof1 = (static_frame.height-y-1)*static_frame.width;
		aof2 = y*static_frame.width;
		for( int x=0; x<(int)static_frame.width; ++x )
		{
			offs1 = (x+aof1)*4;
			offs2 = (x+aof2)*3;

			static_frame.bits[offs1+0] = frame->imageData[offs2+0];
			static_frame.bits[offs1+1] = frame->imageData[offs2+1];
			static_frame.bits[offs1+2] = frame->imageData[offs2+2];
		}
	}	

	*result = ST_OK;

	p_data.input_frame = &static_frame;
	p_data.frame = &static_frame;
	return( &p_data );
}

//////////////////////////////////////////////////////////////////////////

void vaOpenCV::free()
{
	if( capture != NULL )
	{
		cvReleaseCapture( &capture );
		capture = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////

extern "C" {

__declspec(dllexport) vaOpenCV * export_module()
{
	return( new vaOpenCV );
}

};

//////////////////////////////////////////////////////////////////////////
