#include "posdetect.h"
#include "../../module_base/src/types.h"
#include "../../module_base/src/status_codes.h"

#include <cv.h>
#include <highgui.h>
#include <cvcam.h>
#include <math.h>

#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cxcore")
#pragma comment(lib,"cvaux")
#pragma comment(lib,"cv")
#pragma comment(lib,"ml")
#pragma comment(lib,"highgui")

#pragma warning ( disable: 4244 )	// convertion

//////////////////////////////////////////////////////////////////////////

#define MARKER_W 9
#define MARKER_H 9

static unsigned char marker[] = {
	  0,   0,   0,    0,   0,   0,    0,   0,   0,  255,   0,   0,  255, 255, 255,  255,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,
	  0,   0,   0,    0,   0,   0,    0,   0,   0,  255,   0,   0,  255, 255, 255,  255,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,
	  0,   0,   0,    0,   0,   0,    0,   0,   0,  255,   0,   0,  255, 255, 255,  255,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,
	255,   0,   0,  255,   0,   0,  255,   0,   0,  255,   0,   0,  255, 255, 255,  255,   0,   0,  255,   0,   0,  255,   0,   0,  255,   0,   0,
	255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255,  255, 255, 255,
	255,   0,   0,  255,   0,   0,  255,   0,   0,  255,   0,   0,  255, 255, 255,  255,   0,   0,  255,   0,   0,  255,   0,   0,  255,   0,   0,
	  0,   0,   0,    0,   0,   0,    0,   0,   0,  255,   0,   0,  255, 255, 255,  255,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,
	  0,   0,   0,    0,   0,   0,    0,   0,   0,  255,   0,   0,  255, 255, 255,  255,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0,
	  0,   0,   0,    0,   0,   0,    0,   0,   0,  255,   0,   0,  255, 255, 255,  255,   0,   0,    0,   0,   0,    0,   0,   0,    0,   0,   0
};

//////////////////////////////////////////////////////////////////////////

cPosdetect::cPosdetect() : alloc_mem(0)
{
	REG_PARAM( PT_INT, or_mask_size, "Size of the orientation mask", 4 );
	REG_PARAM( PT_INT, draw_marker,  "Draw marker to the output", 0 );
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

int cPosdetect::get_module_type()
{
	return( MT_GESTURES );
}

//////////////////////////////////////////////////////////////////////////

int cPosdetect::input_type()
{
	return( MT_PROBABILITY );
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
	float tan_fi;
	int InitialValue=1;

	int width, height;
	float maxVal;
	float * piTable;

	width = prev_frame->frame->width;
	height = prev_frame->frame->height;
	maxVal = 1.0f;
	piTable = prev_frame->prob;

	int xs=0, xk=width, ys=0, yk=height, ObjHeight, ObjWidth,s=0;
	float xc=0.0f, yc=0.0f;
	for (int k=0;k<2;k++)
	{
		if(k)
		{
			xs-=s;
			xk+=s;
			ys-=1.2*s;
			yk+=1.2*s;
			if (xs<0) xs=0;
			if (xk>height) xk=height;
			if (ys<0) ys=0;
			if (yk>height) yk=height;
		}
		M00=0.0;
		M10=0.0;
		M01=0.0;
		M20=0.0;
		M02=0.0;
		M11=0.0;
		for (int x=xs; x<xk;x++) 
		{
			for (int y=0;y<yk;y++)
			{
				M00 += piTable[x+y*width];
				M10 += piTable[x+y*width]*(float)x;
				M01 += piTable[x+y*width]*(float)y;
				M20 += piTable[x+y*width]*(float)x*(float)x;
				M02 += piTable[x+y*width]*(float)y*(float)y;
				M11 += piTable[x+y*width]*(float)x*(float)y;
			}
		}
		if (M00)
		{
			xc=M10/M00;
			yc=M01/M00;
			if(k)
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
				if(a+c+sqtmp > 0) ObjHeight = sqrt(2*(a+c+sqtmp));
				//if(a+c-sqtmp > 0) ObjWidth = sqrt((a+c-sqtmp)/2);
				if(a+c+sqtmp > 0) ObjWidth = sqrt((a+c+sqtmp));
				///////////////////////////////////////////////////////////////////////
			}
		}
		if (maxVal) s = sqrt(M00/maxVal);

	}

	// kod z poprzedniego roq.

	register int MinX = width,                              // Zmienne sluzace do zapisania krancowych punktow objektu
		MinY = height,
		MaxX = 0,
		MaxY = 0,
		_Xp = xs,             // Wartosci graniczne przeszukiwania petli
		_Xk = xk,
		_Yp = ys,
		_Yk = yk,
		Dx,                                        // Do wyznaczenie tangensa kata
		Dy;
	register float sum = 0.0;                               // Aktualna suma w masce
	register bool min_coord = false;                        // True - znaleziono juz MinX i MinY
	register bool max_coord = false;                        // True - znaleziono juz MaxX i MaxY
	register int X1 = 0,
		X2 = 0,
		Y1 = 0,
		Y2 = 0;

	for(register int y=_Yp;y<_Yk;y++)
	{
		min_coord = false;
		for(register int x=_Xp;x<_Xk;x+=(or_mask_size-(int)sum))
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
	MinX = 0.5*((float)X2+(float)X1);
	MinY = 0.5*((float)Y2+(float)Y1);

	X1 = 0;
	X2 = 0;
	Y1 = 0;
	Y2 = 0;
	sum = 0.0;
	for(register int y=_Yk-1;y>=_Yp;y--)
	{
		max_coord = false;
		for(register int x=_Xk-1;x>=_Xp;x-=(or_mask_size-(int)sum))
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
	MaxX = 0.5*((float)X2+(float)X1);
	MaxY = 0.5*((float)Y2+(float)Y1);

	Dx = MaxX-MinX;
	Dy = MaxY-MinY;
	if(!Dx)
		tan_fi = 100.0;
	if(Dx)
		tan_fi =((float)Dy)/((float)Dx);

	pos.gesture=GESTURE_NULL;
	pos.angle=0.0f;
	pos.x=xc;
	pos.y=yc;
	*result = ST_OK;

	/// dilz add

	static frame_data frame = { 0, 0, 0, 0 };

	if( draw_marker )
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

		draw_frame_marker( &frame, pos.x, pos.y );
	}

	/// ---

	p_data.input_frame = prev_frame->input_frame;
	p_data.frame = &frame;
	p_data.position = &pos;

	return ( &p_data );
}

//////////////////////////////////////////////////////////////////////////

void cPosdetect::draw_frame_marker( frame_data * frame, int posx, int posy )
{
	if( posx < 0 ) posx = 0;
	if( posy < 0 ) posy = 0;

	if( posx > (int)frame->width-MARKER_W-1 ) posx = frame->width-MARKER_W-1;
	if( posy > (int)frame->height-MARKER_H-1 ) posy = frame->height-MARKER_H-1;


	for( int x=0; x<MARKER_W; ++x )
	{
		for( int y=0; y<MARKER_H; ++y )
		{
			if( marker[(x+y*MARKER_W)*3+0] != 0 )
			{
				frame->bits[(posx+x+(posy+y)*frame->width)*4+0] = marker[(x+y*MARKER_W)*3+0];
				frame->bits[(posx+x+(posy+y)*frame->width)*4+1] = marker[(x+y*MARKER_W)*3+1];
				frame->bits[(posx+x+(posy+y)*frame->width)*4+2] = marker[(x+y*MARKER_W)*3+2];
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////

int cPosdetect::init()
{
	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void cPosdetect::free()
{
	
}

//////////////////////////////////////////////////////////////////////////
/// export funkcji exportujacej

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////

__declspec(dllexport) cPosdetect * export_module()
{
	return( new cPosdetect );
}

//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////