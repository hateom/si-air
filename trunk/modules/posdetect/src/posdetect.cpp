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

cPosdetect::cPosdetect()
{
//	REG_PARAM( PT_INT, Smin, "5. Wart. minimalna H", 15 );
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


//////////////////////////////////////////////////////////////////////////

Tpos * cPosdetect::calc_position( float * piTable , float maxVal, int width, int height, int * status )
{
	static Tpos pos;
	float M00;
	float M10;
	float M01;
	float M20;
	float M02;
	float M11;
	int xs=0, xk=width, ys=0, yk=height, ObjHeight, ObjWidth,s=0;
	float xc, yc;
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
	pos.gesture=GESTURE_NULL;
	pos.angle=0.0;
	pos.x=xc;
	pos.y=yc;
	*status = ST_OK;
	return ( &pos );
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