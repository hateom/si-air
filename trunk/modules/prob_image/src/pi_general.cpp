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


//////////////////////////////////////////////////////////////////////////

pi_struct * piGeneral::process_frame( frame_data * inFrame, int * status )
{
	int R, G, B;
	int i=0;
	float H, S, V;
//	pi_struct * pImage;
	//frame_data * temp_frame;
	
	if( !inFrame )
	{
		return NULL;
	}

	unsigned int height=inFrame->height, width=inFrame->width, depth = inFrame->depth;
//	if (!(pImage = new pi_struct())) return NULL;

//	if (!(temp_piTable = new float[height*width])) return NULL;
/*
	if (!(temp_frame = new frame_data())) return NULL;
	temp_frame->bits = new unsigned char[width*height*depth];
	temp_frame->depth = inFrame->depth;
	temp_frame->height = inFrame->height;
	temp_frame->width = inFrame->width;
*/

	static frame_data static_frame = { 0, 0, 0, 0 };
	static pi_struct pImage = { 0, 0 };
	static float * piTable = NULL;

	static_frame.depth = 4;
	static_frame.width = inFrame->width;
	static_frame.height = inFrame->height;

	if( alloc_mem == 0 )
	{
		alloc_mem = static_frame.depth*static_frame.height*static_frame.width;
		static_frame.bits = new unsigned char[alloc_mem];
		
		/*
		if (!(piTable = new float[height*width]))		<-- to sprawdzanie nie ma sensu, gdyz w c++
		{													w razie braku pamieci zostanie rzucony wyjatek
			*status  = ST_ALLOC_ERROR;						i sprawdzenie i tak sie nie wykona
			return NULL;
		}
		*/

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
			/*														<-- j/w
			if (!(piTable = new float[height*width])) 
			{
				*status = ST_ALLOC_ERROR;
				return NULL;
			}
			*/
			piTable = new float[height*width];
		}
	}

// petla po wszystkich pikselach, tablica wygl¹da nastêpuj¹co
	//for( unsigned int x=0; x<width*height*depth; i++ )
	for( int x=0; x<(int)width; ++x )
	{
		for( int y=0; y<(int)height; ++y )
		{
			//B=inFrame->bits[x++];
			//G=inFrame->bits[x++];
			//R=inFrame->bits[x++];
			//x++;

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
	pImage.prob_table = piTable;
	pImage.frame = &static_frame;
	*status = ST_OK;
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