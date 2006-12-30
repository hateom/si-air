#define MOD_CPP
/// 2/SQRT(2) - w celu unikniecia dzielenia
#define TWO_BY_SQRT_TWO 1.41421356237310f
#include "posdetect.h"
#include "../../module_base/src/types.h"
#include "../../module_base/src/status_codes.h"

//////////////////////////////////////////////////////////////////////////

#include <cv.h>
#include <highgui.h>
#include <cvcam.h>
#include <math.h>

//////////////////////////////////////////////////////////////////////////


#include "marker_data.h" /// marker zapisany jako tablica pixeli

//////////////////////////////////////////////////////////////////////////

cPosdetect::cPosdetect() : alloc_mem(0), angle(0.0f)
{
//	REG_PARAM( PT_INT, or_mask_size,  "Size of the orientation mask", 4 );
	REG_PARAM( PT_FLOAT_RANGE, angle_max, "Rotation treated as Click (in radianz)!",
				float_range(0.65f, 0.0f, 1.5f) );
	REG_PARAM( PT_FLOAT_RANGE, treshold, "Angle treshold",
		float_range(0.1f, 0.0f, 0.2f) );
	//REG_PARAM( PT_INT_RANGE, buff_size, "Buffer size",
		//int_range(5, 1, 15) );
	REG_PARAM(PT_FLOAT_RANGE, ratio, "Stosunek hakt/hpocz do 3 klaw.", float_range(0.75f, 0.2f, 0.95f));
	REG_PARAM(PT_BOOL,thirdBtn,"Third Button Emulation",0);
	REG_PARAM(PT_BOOL, correctPlacement, "Move center", 0);
	REG_PARAM( PT_PREVIEW, angle_prv, "Angle", preview( PT_FLOAT, 200, &angle ) );

	buffer = NULL;
}

//////////////////////////////////////////////////////////////////////////

cPosdetect::~cPosdetect()
{
}

//////////////////////////////////////////////////////////////////////////

const char * cPosdetect::get_module_description()
{
	static char descritpion[] = "Position, Rotation and Gesture Detection Module : Simple Implementation";
	return( descritpion );
}

//////////////////////////////////////////////////////////////////////////

int cPosdetect::input_type()
{
	return( MT_PROBDATA );
}

//////////////////////////////////////////////////////////////////////////

int cPosdetect::output_type()
{
	return( MT_POSGEST );
}

//////////////////////////////////////////////////////////////////////////

proc_data * cPosdetect::process_frame( proc_data * prev_frame, int * result )
{
	static pd_data pos;
	static proc_data p_data = { 0, 0, 0, 0 };
	static float tan_fi;
	static int width, height;
	static int ObjHeight=0, ObjWidth=0;
	static int initialLenght;
	static float dx, dy;
	static float sign;

//	maxVal = prev_frame->max_prob;
	width = prev_frame->frame->width;
	height = prev_frame->frame->height;
	//piTable = prev_frame->prob;
	xc=0.0f, yc=0.0f;
	M00 = prev_frame->moments[0];
	M10 = prev_frame->moments[1];
	M01 = prev_frame->moments[2];
	M20 = prev_frame->moments[3];
	M02 = prev_frame->moments[4];
	M11 = prev_frame->moments[5];
		
		if( M00 > 0.0f)
		{
			float inv_M00 = 1.0f/M00;
			xc = M10*inv_M00;
			yc = M01*inv_M00;
			float a,b,c, sqtmp, lptmp;
			a = (M20*inv_M00) - (xc*xc);
			b = 2*((M11*inv_M00) - (xc*yc));
			c = (M02*inv_M00) - (yc*yc);
			lptmp = (b*b)+((a-c)*(a-c));
			//lptmp = (b*b)-((a-c)*(a-c));
			if(lptmp > 0) sqtmp = sqrt(lptmp);
			if(lptmp <= 0) sqtmp = 0;
			//if(a+c+sqtmp > 0) ObjHeight = sqrt((a+c+sqtmp)/2);
			if( a+c+sqtmp > 0.0f ) ObjHeight = (int)(TWO_BY_SQRT_TWO*sqrtf((a+c+sqtmp)));
			if (isFirst) {initialLenght = ObjHeight; isFirst=false;}
			//if(a+c-sqtmp > 0) ObjWidth = sqrt((a+c-sqtmp)/2);
			if( a+c-sqtmp > 0.0f ) ObjWidth = (int)(TWO_BY_SQRT_TWO*sqrtf((a+c-sqtmp)));
			///////////////////////////////////////////////////////////////////////
		}
	float licz=0.0f, mian=1.0f;
	if (M00) {
		float inv_M00 = 1.0f/M00;
		licz=(2*((M11*inv_M00)-xc*yc));
		mian=(((M20*inv_M00)-xc*xc)-((M02*inv_M00)-yc*yc));
	}
	//pos.gesture=GESTURE_NULL;
	tan_fi = licz/mian;
	u = atan2(licz,mian)/2.0f;

	if (thirdBtn && ratio*initialLenght>ObjHeight) 
	{
		pos.gesture = GESTURE_MIDDLEBTNDOWN;
		last_gesture = GESTURE_MIDDLEBTNDOWN;
	}
	else if ((!thirdBtn || ObjHeight>ratio*initialLenght) && u<angle_max && u>0.0f) 
	{
		pos.gesture = GESTURE_LMBDOWN;
		last_gesture = GESTURE_LMBDOWN;
	}
	else if((!thirdBtn || ObjHeight>ratio*initialLenght) && u>-angle_max && u<-0.0f)
	{
		pos.gesture = GESTURE_RMBDOWN;
		last_gesture = GESTURE_RMBDOWN;
	}
	else if((u>angle_max+treshold && u<=1.5f) || (u<-angle_max-treshold && u>=-1.5f))
	{
		pos.gesture = GESTURE_NULL;
		last_gesture = GESTURE_NULL;
	}
	else pos.gesture = last_gesture;
	//pos.angle=atan(tan_fi)/2;
	pos.angle=u;
	if (correctPlacement && ObjHeight>ratio*initialLenght){
		if (u>0) sign=1.0f; else sign = -1.0f;
		dy = abs(sinf(u)*0.5f*ObjHeight);
		dx = sign*cosf(u)*0.5f*ObjHeight;
	} else {dx=0; dy=0;}
	pos.x = (int)(xc+dx);
	pos.y = (int)(yc+dy);
	*result = ST_OK;

	/// dilz add

	static frame_data frame = { 0, 0, 0, 0 };

	if( preview_param )
	{

		frame.depth = 4; //(3*frame->depth)/8;
		frame.width = prev_frame->input_frame->width;
		frame.height = prev_frame->input_frame->height;

		if( alloc_mem == 0 )
		{
			alloc_mem = frame.depth*frame.height*frame.width;
			frame.bits = new unsigned char[alloc_mem];
		}
		else
		{
			if( alloc_mem != frame.depth*frame.height*frame.width )
			{
				delete [] frame.bits;
				alloc_mem = frame.depth*frame.height*frame.width;
				frame.bits = new unsigned char[alloc_mem];
			}
		}

		memcpy( frame.bits, prev_frame->input_frame->bits, frame.width*frame.height*frame.depth );

		draw_frame_marker( &frame, pos.x, pos.y, pos.angle );
	}

	/// ---

	p_data.input_frame = prev_frame->input_frame;
	p_data.frame = &frame;
	p_data.position = &pos;

	angle = pos.angle;

	return ( &p_data );
}

//////////////////////////////////////////////////////////////////////////

void cPosdetect::draw_frame_marker( frame_data * frame, int posx, int posy, float angle )
{
	static long yoffs1, yoffs2, offs1, offs2;

	if( posx < 0 ) posx = 0;
	if( posy < 0 ) posy = 0;

	if( posx > (int)frame->width-MARKER_W-1 ) posx = frame->width-MARKER_W-1;
	if( posy > (int)frame->height-MARKER_H-1 ) posy = frame->height-MARKER_H-1;

	for( int y=0; y<MARKER_H; ++y )
	{
		yoffs1 = (posy+y)*frame->width;
		yoffs2 = y*MARKER_W;

		for( int x=0; x<MARKER_W; ++x )	
		{
			if( marker[(x+y*MARKER_W)*3+0] != 0 )
			{
				offs1 = (posx+x+yoffs1)*4;
				offs2 = (x+yoffs2)*3;

				frame->bits[offs1+0] = marker[offs2+0];
				frame->bits[offs1+1] = marker[offs2+1];
				frame->bits[offs1+2] = marker[offs2+2];
				//if (angle<angle_max && angle>0.0f) frame->bits[offs1+2] = 100;
				//if (angle>-angle_max && angle<0.0f) frame->bits[offs1+1] = 150;
				if (last_gesture == GESTURE_LMBDOWN) frame->bits[offs1+2] = 100;
				if (last_gesture == GESTURE_RMBDOWN) frame->bits[offs1+1] = 150;
				if (last_gesture == GESTURE_MIDDLEBTNDOWN) frame->bits[offs1+0] = 150;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////

int cPosdetect::init( PropertyMgr * pm )
{
	USE_PROPERTY_MGR( pm );
	xc=0.0f, yc=0.0f;
	buff_size=3;
	if (buffer)
	{
		delete [] buffer;
		buffer = NULL;
	}
	buffer = new float[buff_size];
	last_gesture = GESTURE_NULL;
	isFirst = true;
	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void cPosdetect::free()
{
	if (buffer) 
	{
		delete [] buffer;
	}
	buffer = NULL;
}

//////////////////////////////////////////////////////////////////////////

void cPosdetect::mouse_select(int sx, int sy, int sw, int sh )
{
	isFirst = true;
}
//////////////////////////////////////////////////////////////////////////

/// export funkcji exportujacej

extern "C" {

__declspec(dllexport) cPosdetect * export_module()
{
	return( new cPosdetect );
}

};

//////////////////////////////////////////////////////////////////////////