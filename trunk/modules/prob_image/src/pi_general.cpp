#include "pi_general.h"
#include "../../include/types.h"
//#include "../../video_acq_base/src/va_base.h"

#include <cv.h>
#include <highgui.h>
#include <cvcam.h>

#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cxcore")
#pragma comment(lib,"cvaux")
#pragma comment(lib,"cv")
#pragma comment(lib,"ml")
#pragma comment(lib,"highgui")

#pragma warning ( disable: 4244 )	// convertion float->int (RGBtoHSV)

//////////////////////////////////////////////////////////////////////////

piGeneral::piGeneral()
{
	REG_PARAM( PT_INT, Hmax, "1. Wart. maxymalna H", 20 );
	REG_PARAM( PT_INT, Hmin, "2. Wart. minimalna H", 30 );
	REG_PARAM( PT_INT, Vmax, "3. Wart. maxymalna V", 10 );
	REG_PARAM( PT_INT, Vmin, "4. Wart. minimalna V", 20 );
	REG_PARAM( PT_INT, Smin, "5. Wart. minimalna H", 15 );
}

//////////////////////////////////////////////////////////////////////////

piGeneral::~piGeneral()
{

}

//////////////////////////////////////////////////////////////////////////

const char * piGeneral::get_module_description()
{
	static char descritpion[] = "Frame to Probability Image Processing Module : General";
	return( descritpion );
}

//////////////////////////////////////////////////////////////////////////

int piGeneral::get_module_type()
{
	return( MT_PROBABILITY );
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

pi_struct * piGeneral::process_frame( frame_data * inFrame )
{
	int R, G, B;
	int i=0;
	float H, S, V;
//	pi_struct * pImage;
	//frame_data * temp_frame;
	
	if(!inFrame)
	{
		return NULL;
	}

	unsigned int height=inFrame->height, width=inFrame->height, depth = inFrame->depth;
//	if (!(pImage = new pi_struct())) return NULL;

//	if (!(temp_piTable = new float[height*width])) return NULL;
/*
	if (!(temp_frame = new frame_data())) return NULL;
	temp_frame->bits = new unsigned char[width*height*depth];
	temp_frame->depth = inFrame->depth;
	temp_frame->height = inFrame->height;
	temp_frame->width = inFrame->width;
*/

	static frame_data static_frame;
	static pi_struct pImage;
	static float * piTable;

	static_frame.depth = 3;
	static_frame.width = inFrame->width;
	static_frame.height = inFrame->height;

	if( alloc_mem == 0 )
	{
		alloc_mem = static_frame.depth*static_frame.height*static_frame.width;
		static_frame.bits = new unsigned char[alloc_mem];
		if (!(piTable = new float[height*width])) return NULL;
	}
	else
	{
		if( alloc_mem != depth*height*width )
		{
			delete [] static_frame.bits;
			delete [] piTable;
			alloc_mem = depth*height*width;
			static_frame.bits = new unsigned char[alloc_mem];
			if (!(piTable = new float[height*width])) return NULL;
		}
	}

// petla po wszystkich pikselach, tablica wygl�da nast�puj�co
	for (unsigned int x=0;x<width*height*depth;i++) 
	{
		B=inFrame->bits[x++];
		G=inFrame->bits[x++];
		R=inFrame->bits[x++];
		RGBtoHSV(R,G,B,H,S,V);
		piTable[i] = 0.0;
		if((H >= Hmin) && (H < Hmax) && (V >= Vmin) && (V < Vmax) && (Smin < S))
			piTable[i]=1.0;
		if(1){
			float chVal = piTable[i]*255;
			chVal = chVal>255?255:chVal;
			static_frame.bits[i] = (unsigned char)chVal;
			static_frame.bits[i+1] = (unsigned char)chVal;
			static_frame.bits[i+2] = (unsigned char)chVal;
		}
	}

// kopiowanie do struktury i zwrocenie
	pImage.prob_table = piTable;
	pImage.frame = &static_frame;
	return ( &pImage );
}

//////////////////////////////////////////////////////////////////////////


void piGeneral::free()
{
	
}
//////////////////////////////////////////////////////////////////////////
// funkcja z poprzedniego projektu, podobna jest w internecie
//////////////////////////////////////////////////////////////////////////

void piGeneral::RGBtoHSV(int& r, int& g, int& b, float& h, float& s, float& v)
{
	float min_v, max_v, delta;
	min_v = r;
	min_v = min_v<g?min_v:g;
	min_v = min_v<b?min_v:b;

	max_v = r;
	max_v = max_v>g?max_v:g;
	max_v = max_v>b?max_v:b;
	v = max_v;                              // v

	delta = max_v - min_v;

	if( max_v != 0 )
		s = delta / max_v;		// s
	else {
		// r = g = b = 0		// s = 0, v is undefined
		s = 0;
		h = -1;
		return;
	}
	if( r == max_v )
		h = ( (float)g - (float)b ) / delta;		// between yellow & magenta
	else if( g == max_v )
		h = 2.0 + ( (float)b - (float)r ) / delta;	// between cyan & yellow
	else
		h = 4.0 + ( (float)r - (float)g ) / delta;	// between magenta & cyan
	h *= 60.0;				// degrees
	if( h < 0.0 )
		h += 360.0;
}

//////////////////////////////////////////////////////////////////////////
/// export funkcji exportujacej

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////

__declspec(dllexport) piGeneral * export_module()
{
	return( new piGeneral );
}

//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////