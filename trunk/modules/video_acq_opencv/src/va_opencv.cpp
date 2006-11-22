#include "va_opencv.h"

#include <cv.h>
#include <highgui.h>

#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cxcore.lib")
#pragma comment(lib,"cvaux.lib")
#pragma comment(lib,"ml.lib")
#pragma comment(lib,"highgui.lib")

//////////////////////////////////////////////////////////////////////////

#define MK_PARAM( PP ) ((void*)&PP)
#define REG_PARAM( TYPE, NAME, DESC, DEF_VAL ) register_param( TYPE, MK_PARAM(NAME), #NAME, DESC ); NAME = DEF_VAL;

//////////////////////////////////////////////////////////////////////////

vaOpenCV::vaOpenCV() : capture(NULL), alloc_mem(0)
{
	REG_PARAM( PT_INT,   param1, "1. parametr testowy", 0 );
	REG_PARAM( PT_FLOAT, param2, "2. parametr testowy", 0.0f );
	REG_PARAM( PT_LONG,  param3, "3. parametr testowy", 0L );
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

int vaOpenCV::init( int device, char * filename )
{
	if( capture != NULL ) free();

	capture = ( filename != NULL ) ? cvCaptureFromFile( filename ) : cvCaptureFromCAM( device );
	

	if( !capture ) return -1;

	return( 0 );
}

//////////////////////////////////////////////////////////////////////////

frame_data * vaOpenCV::process_frame( int * result )
{
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

	static frame_data static_frame;

	static_frame.depth = 3;//frame->depth/8;
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
	if( capture != NULL )
	{
		cvReleaseCapture( &capture );
		capture = NULL;
	}
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
