#include "va_opencv.h"
#include "../../include/types.h"

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

vaOpenCV::vaOpenCV() : /*capture(NULL),*/ alloc_mem(0)/*, cam_count(0)*/
{
	REG_PARAM( PT_INT,   param1, "1. parametr testowy", 13 );
	REG_PARAM( PT_FLOAT, param2, "2. parametr testowy", 3.1415f );
	REG_PARAM( PT_LONG,  hwnd,   "uchwyt okna prev", 0 );
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

int vaOpenCV::get_module_type()
{
	return( MT_VIDEO_ACQ );
}

//////////////////////////////////////////////////////////////////////////

static IplImage * current_frame;

static void cvcam_callback( IplImage * image )
{
	current_frame = image;
}

//////////////////////////////////////////////////////////////////////////

int vaOpenCV::init( int device, char * filename )
{
	/// load AVI from file
	if( filename != NULL )
	{
		cvcamPlayAVI( 0, 0, 0, 0, 0 );
	}
	/// capture video from camera
	else
	{
//		int ncams = cvcamGetCamerascount();
		cvcamSetProperty( 0, CVCAM_PROP_ENABLE, CVCAMTRUE );
		cvcamSetProperty( 0, CVCAM_PROP_RENDER, CVCAMTRUE );
		if( hwnd )
		{
			printf( "window found" );
			cvcamSetProperty( 0, CVCAM_PROP_WINDOW, (void*)(hwnd) );
		}
		else
		{
			printf( "window not found" );
		}
		cvcamSetProperty( 0, CVCAM_PROP_CALLBACK, cvcam_callback );

		cvcamInit();
		cvcamStart();
	}


//	if( capture != NULL ) free();
//	capture = ( filename != NULL ) ? cvCaptureFromFile( filename ) : cvCaptureFromCAM( device );
//	if( !capture ) return -1;

	return( 0 );
}

//////////////////////////////////////////////////////////////////////////

frame_data * vaOpenCV::process_frame( int * result )
{
	/*
	if( !capture ) 
	{
		*result = -1;
		return( NULL );
	}


	IplImage * frame = cvQueryFrame( capture );
	if( !frame )
	{
		*result = -2;
		return( NULL );
	}
*/

	if( !current_frame )
	{
		*result = -1;
		return( NULL );
	}

	IplImage * frame = current_frame;

	static frame_data static_frame;

	static_frame.depth = (3*frame->depth)/8;
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
			alloc_mem = frame->depth*frame->height*frame->width;
			static_frame.bits = new unsigned char[alloc_mem];
		}
	}

	memcpy( static_frame.bits, frame->imageData, alloc_mem );
/*	for( int i=0; i<alloc_mem; ++i ) 
	{
		static_frame.bits[i] = frame->imageData[i];
	}	
*/
	*result = 0;

	return( &static_frame );
}

//////////////////////////////////////////////////////////////////////////

void vaOpenCV::free()
{
	cvcamStop();
	cvcamExit();

	/*
	if( capture != NULL )
	{
		cvReleaseCapture( &capture );
		capture = NULL;
	}*/
}

//////////////////////////////////////////////////////////////////////////
/// export funkcji exportujacej

#ifdef __cplusplus
extern "C" {
#endif

	//////////////////////////////////////////////////////////////////////////

__declspec(dllexport) vaOpenCV * export_module()
{
	return( new vaOpenCV );
}

//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////
