#include "pi_general.h"
#include "../../module_base/src/types.h"
#include "../../module_base/src/status_codes.h"

#include <cv.h>
#include <highgui.h>
#include <cvcam.h>

#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cxcore")
#pragma comment(lib,"cvaux")
#pragma comment(lib,"cv")
#pragma comment(lib,"ml")
#pragma comment(lib,"highgui")

//#pragma warning ( disable: 4244 )	// convertion float->int (RGBtoHSV)

//////////////////////////////////////////////////////////////////////////

piGeneral::piGeneral() : alloc_mem(0)
{
	REG_PARAM( PT_INT, Hmax, "1. Wart. maxymalna H", 35 );
	REG_PARAM( PT_INT, Hmin, "2. Wart. minimalna H", 10 );
	REG_PARAM( PT_INT, Vmax, "3. Wart. maxymalna V", 255 );
	REG_PARAM( PT_INT, Vmin, "4. Wart. minimalna V", 20 );
	REG_PARAM( PT_INT, Smin, "5. Wart. minimalna S", 30 );
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

int piGeneral::input_type()
{
	return( MT_FRAME );
}

//////////////////////////////////////////////////////////////////////////

int piGeneral::output_type()
{
	return( MT_PROBDATA );
}

//////////////////////////////////////////////////////////////////////////

proc_data * piGeneral::process_frame( proc_data * prev_frame, int * status )
{
	int R, G, B;
	int i=0;
	float H, S, V;

	frame_data * inFrame;
	inFrame = prev_frame->frame;

	if( !inFrame )
	{
		return NULL;
	}

	unsigned int height=inFrame->height, width=inFrame->width, depth = inFrame->depth;

	static frame_data static_frame = { 0, 0, 0, 0 };
	static proc_data p_data = { 0, 0, 0 };
	static float * piTable = NULL;

	static_frame.depth = 4;
	static_frame.width = inFrame->width;
	static_frame.height = inFrame->height;

	if( alloc_mem == 0 )
	{
		alloc_mem = static_frame.depth*static_frame.height*static_frame.width;
		static_frame.bits = new unsigned char[alloc_mem];
		piTable = new float[height*width];
	}
	else
	{
		if( alloc_mem != static_frame.depth*static_frame.height*static_frame.width )
		{
			delete [] static_frame.bits;
			delete [] piTable;
			alloc_mem = static_frame.depth*static_frame.height*static_frame.width;
			static_frame.bits = new unsigned char[alloc_mem];
			piTable = new float[height*width];
		}
	}

	// petla po wszystkich pikselach, tablica wygl¹da nastêpuj¹co
	for( int x=0; x<(int)width; ++x )
	{
		for( int y=0; y<(int)height; ++y )
		{
			B = inFrame->bits[(x+y*width)*4+0];
			G = inFrame->bits[(x+y*width)*4+1];
			R = inFrame->bits[(x+y*width)*4+2];

			RGBtoHSV( R, G, B, H, S, V );

			piTable[x+y*width] = 0.0;

			if( ( H >= Hmin ) && ( H < Hmax ) && ( V >= Vmin ) && ( V < Vmax ) /*&& ( Smin < S )*/ )
			{
				piTable[x+y*width] = 1.0;
			}

			if( 1 )
			{
				float chVal = piTable[x+y*width]*255.0f;
				chVal = (chVal > 255.0f) ? 255.0f : chVal;

				static_frame.bits[(x+y*width)*4+0] = (unsigned char)chVal;
				static_frame.bits[(x+y*width)*4+1] = (unsigned char)chVal;
				static_frame.bits[(x+y*width)*4+2] = (unsigned char)chVal;
				static_frame.bits[(x+y*width)*4+3] = 0;
			}
		}
	}

	// kopiowanie do struktury i zwrocenie

	p_data.frame = &static_frame;
	p_data.prob = piTable;

	*status = ST_OK;
	return ( &p_data );
}

//////////////////////////////////////////////////////////////////////////

int piGeneral::init()
{
	return( ST_OK );
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
	min_v = (float)r;
	min_v = min_v < (float)g ? min_v : (float)g;
	min_v = min_v < (float)b ? min_v : (float)b;

	max_v = (float)r;
	max_v = max_v > (float)g ? max_v : (float)g;
	max_v = max_v > (float)b ? max_v : (float)b;
	v = max_v;                              // v

	delta = max_v - min_v;

	if( max_v != 0 )
	{
		s = delta / max_v;		// s
	}
	else 
	{
		// r = g = b = 0		// s = 0, v is undefined
		s = 0;
		h = -1;
		return;
	}
	if( r == max_v )
	{
		h = ( (float)g - (float)b ) / delta;		// between yellow & magenta
	}
	else if( g == max_v )
	{
		h = 2.0f + ( (float)b - (float)r ) / delta;	// between cyan & yellow
	}
	else
	{
		h = 4.0f + ( (float)r - (float)g ) / delta;	// between magenta & cyan
	}

	h *= 60.0f;				// degrees

	if( h < 0.0f )
	{
		h += 360.0f;
	}
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