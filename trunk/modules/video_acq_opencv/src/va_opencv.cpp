#include "va_opencv.h"
#include "../../module_base/src/types.h"

#include <cv.h>
#include <highgui.h>
#include <cvcam.h>

#include "../../module_base/src/status_codes.h"

#include "../../module_base/src/property_mgr.h"

#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cvcam.lib")
#pragma comment(lib,"cxcore.lib")
#pragma comment(lib,"cvaux.lib")
#pragma comment(lib,"ml.lib")
#pragma comment(lib,"highgui.lib")

//////////////////////////////////////////////////////////////////////////

vaOpenCV::vaOpenCV() : capture(NULL), alloc_mem(0)/*, cam_count(0)*/
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

int vaOpenCV::get_module_type()
{
	return( MT_VIDEO_ACQ );
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
/*
static IplImage * current_frame;

static void cvcam_callback( IplImage * image )
{
	current_frame = image;
}
*/
//////////////////////////////////////////////////////////////////////////

int vaOpenCV::init()
{
	/*
	/// load AVI from file
	if( filename != NULL )
	{
		cvcamPlayAVI( 0, (void*)hwnd, 0, 0, 0 );
	}
	/// capture video from camera
	else
	{
//		int ncams = cvcamGetCamerascount();
		cvcamSetProperty( 0, CVCAM_PROP_ENABLE, CVCAMTRUE );
		cvcamSetProperty( 0, CVCAM_PROP_RENDER, CVCAMTRUE );
		if( hwnd )
		{
			cvcamSetProperty( 0, CVCAM_PROP_WINDOW, (void*)(hwnd) );
		}

		cvcamSetProperty( 0, CVCAM_PROP_CALLBACK, cvcam_callback );

		cvcamInit();
		cvcamStart();
	}
*/

	if( capture != NULL ) free();
	if( ( filename != NULL ) && ( strcmp( filename, "" ) != 0 ) )
	{
		capture = cvCaptureFromFile( filename );
//		printf( "Capturing from file <%s> [%s]\n", filename, capture!=NULL?"OK":"!!!" );
	}
	else
	{
		capture = cvCaptureFromCAM( device );
//		printf( "Capturing from device <%d> [%s]\n", device, capture!=NULL?"OK":"!!!" );
	}
	
	if( !capture )
	{
		return( ST_DEVICE_NOT_FOUND );
	}
/*
	propertyMgr->register_property( "input_module_cv", this );

	if( propertyMgr->get_property( "input_module_cv" ) == this )
	{
		printf( ">>> property are working!\n" );
	}
	else
	{
		printf( ">>> property sux!\n" );
	}
*/
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

	static_frame.depth = 4; //(3*frame->depth)/8;
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

	//	memcpy( static_frame.bits, frame->imageData, alloc_mem );

	/*	for( int i=0; i<alloc_mem; ++i ) 
	{
	static_frame.bits[i] = frame->imageData[i];
	}	
	*/

/*
	for( int x=0; x<(int)static_frame.width; ++x )
	{
		for( int y=0; y<(int)static_frame.height; ++y )
		{
			static_frame.bits[(x+(static_frame.height-y-1)*static_frame.width)*4+0] = frame->imageData[(x+y*static_frame.width)*3+0];
			static_frame.bits[(x+(static_frame.height-y-1)*static_frame.width)*4+1] = frame->imageData[(x+y*static_frame.width)*3+1];
			static_frame.bits[(x+(static_frame.height-y-1)*static_frame.width)*4+2] = frame->imageData[(x+y*static_frame.width)*3+2];
			static_frame.bits[(x+(static_frame.height-y-1)*static_frame.width)*4+3] = 0;
		}
	}
*/

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
			//static_frame.bits[offs1+3] = 0;
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
/*
	cvcamStop();
	cvcamExit();
*/

	if( capture != NULL )
	{
		cvReleaseCapture( &capture );
		capture = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////
/*
void vaOpenCV::mouse_select(int sx, int sy, int sw, int sh )
{
	printf( "::: cv selected region [%d %d %d %d]\n", sx, sy, sw, sh );
}
*/
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
