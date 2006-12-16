#include "mod_camshift_opencv.h"
#include "../../module_base/src/status_codes.h"

#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cvcam.lib")
#pragma comment(lib,"cxcore.lib")
#pragma comment(lib,"cvaux.lib")
#pragma comment(lib,"ml.lib")
#pragma comment(lib,"highgui.lib")

#ifndef _EiC
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <ctype.h>
#endif

//////////////////////////////////////////////////////////////////////////

//#define MIN( A, B ) (A)<(B)?(A):(B)

//////////////////////////////////////////////////////////////////////////

CvScalar hsv2rgb( float hue )
{
	int rgb[3], p, sector;
	static const int sector_data[][3]=
	{{0,2,1}, {1,2,0}, {1,0,2}, {2,0,1}, {2,1,0}, {0,1,2}};
	hue *= 0.033333333333333333333333333333333f;
	sector = cvFloor(hue);
	p = cvRound(255*(hue - sector));
	p ^= sector & 1 ? 255 : 0;

	rgb[sector_data[sector][0]] = 255;
	rgb[sector_data[sector][1]] = 0;
	rgb[sector_data[sector][2]] = p;

	return cvScalar(rgb[2], rgb[1], rgb[0],0);
}

mod_camshift_opencv::mod_camshift_opencv() : alloc_mem(0L)
{
	REG_PARAM( PT_FLOAT, factor, "zmienna", 1.0f );
}

//////////////////////////////////////////////////////////////////////////

mod_camshift_opencv::~mod_camshift_opencv()
{

}

//////////////////////////////////////////////////////////////////////////

const char * mod_camshift_opencv::get_module_description()
{
	static char descritpion[] = "Object Tracking Module : OpenCV implementation";
	return( descritpion );
}	


//////////////////////////////////////////////////////////////////////////

int mod_camshift_opencv::init( PropertyMgr * pm )
{
	USE_PROPERTY_MGR( pm );

	track_object =1;
	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void mod_camshift_opencv::free()
{

}

//////////////////////////////////////////////////////////////////////////

int mod_camshift_opencv::get_module_type()
{
	return( MT_POSGEST );
}

//////////////////////////////////////////////////////////////////////////

int mod_camshift_opencv::input_type()
{
	return( MT_FRAME );
}

//////////////////////////////////////////////////////////////////////////

int mod_camshift_opencv::output_type()
{
	return( MT_FRAME );
}

//////////////////////////////////////////////////////////////////////////

proc_data * mod_camshift_opencv::process_frame( proc_data * prev_frame, int * result )
{
	static IplImage * frame;
	static IplImage * image;
	static IplImage * mask;
	static IplImage * hue;
	static IplImage * hsv;
	static IplImage * backproject;
	static IplImage * histimg;
	static CvHistogram * hist;
	static int hdims=16;

	static CvPoint origin;
	static CvRect selection;
	static CvRect track_window;
	static CvBox2D track_box;
	static CvConnectedComp track_comp;
	float hranges_arr[] = {0,180};
	float* hranges = hranges_arr;
	int vmin = 10, vmax = 256, smin = 30;

	frame = (IplImage*) prev_frame->user_data0;
	if( !image )
	{
		/* allocate all the buffers */
		image = cvCreateImage( cvGetSize(frame), 8, 3 );
		image->origin = frame->origin;
		hsv = cvCreateImage( cvGetSize(frame), 8, 3 );
		hue = cvCreateImage( cvGetSize(frame), 8, 1 );
		mask = cvCreateImage( cvGetSize(frame), 8, 1 );
		backproject = cvCreateImage( cvGetSize(frame), 8, 1 );
		hist = cvCreateHist( 1, &hdims, CV_HIST_ARRAY, &hranges, 1 );
		histimg = cvCreateImage( cvSize(320,200), 8, 3 );
		cvZero( histimg );
	}

	cvCopy( frame, image, 0 );
	cvCvtColor( image, hsv, CV_BGR2HSV );

	if( 1 )
	{
		int _vmin = vmin, _vmax = vmax;

		cvInRangeS( hsv, cvScalar(0,smin,MIN(_vmin,_vmax),0),
			cvScalar(180,256,MAX(_vmin,_vmax),0), mask );
		cvSplit( hsv, hue, 0, 0, 0 );

		if( track_object < 0 )
		{
			float max_val = 0.f;
			cvSetImageROI( hue, selection );
			cvSetImageROI( mask, selection );
			cvCalcHist( &hue, hist, 0, mask );
			cvGetMinMaxHistValue( hist, 0, &max_val, 0, 0 );
			cvConvertScale( hist->bins, hist->bins, max_val ? 255. / max_val : 0., 0 );
			cvResetImageROI( hue );
			cvResetImageROI( mask );
			track_window = selection;
			track_object = 1;

			cvZero( histimg );
			bin_w = histimg->width / hdims;
			for( int i = 0; i < hdims; i++ )
			{
				int val = cvRound( cvGetReal1D(hist->bins,i)*histimg->height/255 );
				CvScalar color = hsv2rgb(i*180.f/hdims);
				cvRectangle( histimg, cvPoint(i*bin_w,histimg->height),
					cvPoint((i+1)*bin_w,histimg->height - val),
					color, -1, 8, 0 );
			}
		}

		cvCalcBackProject( &hue, backproject, hist );
		cvAnd( backproject, mask, backproject, 0 );
		cvCamShift( backproject, track_window,
			cvTermCriteria( CV_TERMCRIT_EPS | CV_TERMCRIT_ITER, 10, 1 ),
			&track_comp, &track_box );
		track_window = track_comp.rect;

		//if( backproject_mode )
		if (0)
			cvCvtColor( backproject, image, CV_GRAY2BGR );
		if( image->origin )
			track_box.angle = -track_box.angle;
		cvEllipseBox( image, track_box, CV_RGB(255,0,0), 3, CV_AA, 0 );
	}

	if( 1 && selection.width > 0 && selection.height > 0 )
	{
		cvSetImageROI( image, selection );
		cvXorS( image, cvScalarAll(255), image, 0 );
		cvResetImageROI( image );
	}
	return prev_frame;
}

//////////////////////////////////////////////////////////////////////////
/// export funkcji exportujacej

#ifdef __cplusplus
extern "C" {
#endif

	//////////////////////////////////////////////////////////////////////////

	__declspec(dllexport) moduleBase * export_module()
	{
		return( new mod_camshift_opencv );
	}

	//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////