#define MOD_CPP
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
	REG_PARAM( PT_INT, or_mask_size,  "Size of the orientation mask", 4 );
	REG_PARAM( PT_INT, angle_max,	  "Kat graniczny", 45 );

	REG_PARAM( PT_PREVIEW, angle_prv, "Angle", preview( PT_FLOAT, 200, &angle ) );
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

	float M00;
	float M10;
	float M01;
	float M20;
	float M02;
	float M11;
	static float tan_fi;
	int InitialValue = 1;
	int offs1, offs2;

	int width, height;
	float maxVal;
	float * piTable;

	width = prev_frame->frame->width;
	height = prev_frame->frame->height;
	//maxVal = 1.0f;
	piTable = prev_frame->prob;
	
	static int xs = 0, xk = width, ys = 0, yk = height, ObjHeight=0, ObjWidth=0, s = 0;
	float xc = 0.0f, yc = 0.0f;
	maxVal = prev_frame->max_prob;
	bool retry=0;
	for( int k=0; k<2; k++ )
	{
		if( k )
		{
			xs=(int)xc;
			ys=(int)yc;
			xk=(int)xc;
			yk=(int)yc;
			xs -= s;
			xk += s;
			ys -= (int)( 1.2f*(float)s );
			yk += (int)( 1.2f*(float)s );

			if( xs < 0 ) xs = 0;
			if( xk > height ) xk = height;
			if( ys < 0 ) ys=0;
			if( yk > height ) yk = height;
		}
		
		M00 = 0.0f;
		M10 = 0.0f;
		M01 = 0.0f;
		M20 = 0.0f;
		M02 = 0.0f;
		M11 = 0.0f;
		
		for (int y=ys; y<yk; y++ )
		{
			offs1 = y*width;
			for (int x=xs; x<xk; x++ )
			{
				offs2 = (x+offs1);
				M00 += piTable[offs2];
				M10 += piTable[offs2]*(float)x;
				M01 += piTable[offs2]*(float)y;
				M20 += piTable[offs2]*(float)x*(float)x;
				M02 += piTable[offs2]*(float)y*(float)y;
				M11 += piTable[offs2]*(float)x*(float)y;
			}
		}
		if( M00 > 20)
		{
			xc = M10/M00;
			yc = M01/M00;

			if( k )
			{
				float a,b,c, sqtmp, lptmp;
				a = (M20/M00) - (xc*xc);
				b = 2*((M11/M00) - (xc*yc));
				c = (M02/M00) - (yc*yc);
				//lptmp = (b*b)+((a-c)*(a-c));
				lptmp = (b*b)-((a-c)*(a-c));
				if(lptmp > 0) sqtmp = sqrt(lptmp);
				if(lptmp <= 0) sqtmp = 0;
				//if(a+c+sqtmp > 0) ObjHeight = sqrt((a+c+sqtmp)/2);
				if( a+c+sqtmp > 0.0f ) ObjHeight = (int)sqrtf((a+c+sqtmp));
				//if(a+c-sqtmp > 0) ObjWidth = sqrt((a+c-sqtmp)/2);
				if( a+c-sqtmp > 0.0f ) ObjWidth = (int)sqrtf((a+c-sqtmp));
				///////////////////////////////////////////////////////////////////////
			}
		}
		else if (!retry)
		{
			xs=0;
			ys=0;
			xk=width;
			yk=height;
			retry=1;
			k=-1;
		}
		if( maxVal ) s = (int)sqrtf( M00/maxVal );
	}
	// kod z poprzedniego roq.

	int MinX = width,                              // Zmienne sluzace do zapisania krancowych punktow objektu
		MinY = height,
		MaxX = 0,
		MaxY = 0,
		_Xp = xs,             // Wartosci graniczne przeszukiwania petli
		_Xk = xk,
		_Yp = ys,
		_Yk = yk,
		Dx,                                        // Do wyznaczenie tangensa kata
		Dy;
	float sum = 0.0;                               // Aktualna suma w masce
	bool min_coord = false;                        // True - znaleziono juz MinX i MinY
	bool max_coord = false;                        // True - znaleziono juz MaxX i MaxY
	int X1 = 0, X2 = 0, Y1 = 0, Y2 = 0;

	for( int y=_Yp;y<_Yk;y++)
	{
		min_coord = false;
		for( int x=_Xp;x<_Xk;x+=(or_mask_size-(int)sum))
		{
			sum = 0.0;
			if((x < 0) || (y < 0) || (x+or_mask_size > width) || (y+or_mask_size > height))
				continue;

			for(int i=0;i<or_mask_size;i++)
				sum += piTable[x+i+(y+i)*width];

			// Gdy elemet obiektu
			if((sum >= (float)or_mask_size) || ((!InitialValue) && (sum >= (float)or_mask_size-1)))
			{
				if(!min_coord)
				{
					//MinX = x;
					//MinY = y;
					X1 = x;
					Y1 = y;
					min_coord = true;
					//x = _Xk;
					//y = _Yk;
					//break;
				}
				X2 = x;
				Y2 = y;
			}

			// Jezeli wyjdzie ze bedziemy musieli sie przesunac o zero lub mniej
			if((or_mask_size-(int)sum) <= 0)
				sum = 0.0;
		}

		if(X2 != X1)
			break;
	}
	MinX = (int)(0.5f*((float)X2+(float)X1));
	MinY = (int)(0.5f*((float)Y2+(float)Y1));

	X1 = 0;
	X2 = 0;
	Y1 = 0;
	Y2 = 0;
	sum = 0.0;
	for( int y=_Yk-1;y>=_Yp;y--)
	{
		max_coord = false;
		for( int x=_Xk-1;x>=_Xp;x-=(or_mask_size-(int)sum))
		{
			sum = 0.0;
			if((x < 0) || (y < 0) || (x+or_mask_size > width) || (y+or_mask_size > height))
				continue;
			for(int i=0;i<or_mask_size;i++)
				sum +=piTable[x+i+(y+i)*width];

			// Gdy elemet obiektu
			if((sum >= (float)or_mask_size) || ((!InitialValue) && (sum >= (float)or_mask_size-1)))
			{
				if(!max_coord)
				{
					//MaxX = x;
					//MaxY = y;
					X1 = x;
					Y1 = y;
					max_coord = true;
					//x = _Xp;
					//y = _Yp;
					//break;
				}
				X2 = x;
				Y2 = y;
			}

			if((or_mask_size-(int)sum) <= 0)
				sum = 0.0;
		}
		if(X2 != X1)
			break;
	}
	MaxX = (int)(0.5f*((float)X2+(float)X1));
	MaxY = (int)(0.5f*((float)Y2+(float)Y1));

	Dx = MaxX-MinX;
	Dy = MaxY-MinY;
	/*
	if(!Dx)
		tan_fi = 100.0;
	if(Dx)
		tan_fi =((float)Dy)/((float)Dx);
	*/	
	if (M00) tan_fi=(2*(M11/M00)-xc*yc)/(((M20/M00)-xc*xc)-((M02/M00)-yc*yc));
	//pos.gesture=GESTURE_NULL;
	float u = atan(tan_fi)/2;
	if ((int)(u*57)>angle_max) 
	{
		pos.gesture=GESTURE_RMBDOWN;
	}
	else pos.gesture=GESTURE_NULL;
	pos.angle=atan(tan_fi)/2;
	pos.x = (int)xc;
	pos.y = (int)yc;
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
				if (angle*57>angle_max) frame->bits[offs1+2] = 100;
				if (angle*57<-angle_max) frame->bits[offs1+2] = 200;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////

int cPosdetect::init( PropertyMgr * pm )
{
	USE_PROPERTY_MGR( pm );
	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void cPosdetect::free()
{
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