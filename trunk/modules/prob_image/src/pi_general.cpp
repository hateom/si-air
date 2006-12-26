#define MOD_CPP
#include "pi_general.h"
#include "../../module_base/src/types.h"
#include "../../module_base/src/status_codes.h"

//////////////////////////////////////////////////////////////////////////

#include <cv.h>
#include <highgui.h>
#include <cvcam.h>

#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cxcore")
#pragma comment(lib,"cvaux")
#pragma comment(lib,"cv")
#pragma comment(lib,"ml")
#pragma comment(lib,"highgui")

//////////////////////////////////////////////////////////////////////////

piGeneral::piGeneral() : alloc_mem(0), selected_region(NULL), histogram(NULL)
{
//	REG_PARAM( PT_INT, Hmax,			"Wart. maxymalna H", 35 );
//	REG_PARAM( PT_INT, Hmin,			"Wart. minimalna H", 10 );
//	REG_PARAM( PT_INT, Vmax,			"Wart. maxymalna V", 255 );
//	REG_PARAM( PT_INT, Vmin,			"Wart. minimalna V", 20 );
//	REG_PARAM( PT_INT, Smin,			"5. Wart. minimalna S", 0 );

	REG_PARAM( PT_INT_RANGE, Hmax, "Wart. maxymalna H", int_range(  35, 0, 360 ) );
	REG_PARAM( PT_INT_RANGE, Hmin, "Wart. minimalna H", int_range(  10, 0, 360 ) );
	REG_PARAM( PT_INT_RANGE, Vmax, "Wart. maxymalna V", int_range( 255, 0, 255 ) );
	REG_PARAM( PT_INT_RANGE, Vmin, "Wart. minimalna V", int_range(  20, 0, 255 ) );
	REG_PARAM( PT_INT_RANGE, Smin, "Wart. minimalna S", int_range(   0, 0, 200 ) );
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

//	int Smin = Smin_r.value;

	inFrame = prev_frame->frame;

	if( !inFrame )
	{
		return NULL;
	}

	unsigned int height=inFrame->height, width=inFrame->width, depth = inFrame->depth;

	static frame_data static_frame = { 0, 0, 0, 0 };
	static proc_data p_data = { 0, 0, 0, 0 };
	static float * piTable = NULL;
	float maxVal = 0.0f; 

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

			if( ( H >= Hmin ) && ( H < Hmax ) && ( V >= Vmin ) && ( V < Vmax ) && ( Smin < S ) )
			{
				piTable[x+y*width] = 1.0;
			}
			if( ( V >= Vmin ) && ( V < Vmax ) && ( Smin < S ) )
				if (histogram->histMaxVal) piTable[x+y*width] += (float)histogram->hist_vals[ int(H)]/histogram->histMaxVal;
			if( preview_param )
			{
				float chVal = piTable[x+y*width]*255.0f;
				chVal = (chVal > 255.0f) ? 255.0f : chVal;

				static_frame.bits[(x+y*width)*4+0] = (unsigned char)chVal;
				static_frame.bits[(x+y*width)*4+1] = (unsigned char)chVal;
				static_frame.bits[(x+y*width)*4+2] = (unsigned char)chVal;
				static_frame.bits[(x+y*width)*4+3] = 0;
			}
			if (piTable[x+y*width] > maxVal) maxVal = piTable[x+y*width];
		}
	}

	// kopiowanie do struktury i zwrocenie
	p_data.input_frame = prev_frame->input_frame;
	p_data.frame =  &static_frame;
	p_data.prob = piTable;
	p_data.max_prob = maxVal;

	*status = ST_OK;
	return ( &p_data );
}

//////////////////////////////////////////////////////////////////////////

void piGeneral::mouse_select(int sx, int sy, int sw, int sh )
{
	int depth = inFrame->depth;
	int size = sw*sh*depth;

	if (!selected_region)
	{
		selected_region = new frame_data();
		selected_region->depth=inFrame->depth;
		selected_region->height=sh;
		selected_region->width=sw;
		selected_region->bits=new unsigned char[size];
	}
	if (selected_region->height!=sh || selected_region->width!=sw)
	{
		selected_region->width=sw;
		selected_region->height=sh;
		if (selected_region->bits) delete [] selected_region->bits;
		selected_region->bits = new unsigned char[size];
	}

	for (int i=0;i<sh;i++) 
	{
		memcpy((selected_region->bits+i*sw*depth),(inFrame->bits+((i+sy)*inFrame->width+sx)*depth),sw*depth);
	}

	hist();
}
//////////////////////////////////////////////////////////////////////////
void piGeneral::hist()
{
	int width,height,size,depth; //x, y
	int R,G,B;
	int HHistMaxValue = 0;
	int HHistStartRange = -1;
	int HHistEndRange = -1;
	float H,S,V;
	float MinV = -1,
		MaxV = -1,
		MinS = -1,
		MaxH = -1,
		MinH = -1;
//	int Smin = Smin_r.value;

	width = selected_region->width;
	height = selected_region->height;
	depth = selected_region->depth;
	size =  width*height*depth;

//	for (int i=0;i<360;i++) histogram->hist_vals[i]=0;
	memset( histogram->hist_vals, 0, 360*sizeof(int) );

	for( int x=0; x<(int)width; ++x )
	{
		for( int y=0; y<(int)height; ++y )
		{
			B = selected_region->bits[(x+y*width)*4+0];
			G = selected_region->bits[(x+y*width)*4+1];
			R = selected_region->bits[(x+y*width)*4+2];
			RGBtoHSV( R, G, B, H, S, V );
			
			if(H >= 0)
			{
				if (H>360) H = 360.0; 
				histogram->hist_vals[(int)H]++;
				if(histogram->hist_vals[(int)H] > HHistMaxValue)
					HHistMaxValue = histogram->hist_vals[(int)H];
				if((HHistStartRange == -1) || (HHistStartRange > (int)H))
					HHistStartRange = (int)H;
				if((HHistEndRange == -1) || (HHistEndRange < (int)H))
					HHistEndRange = (int)H;
			}
			// Wyszukiwanie najmniejszej jasnosci piksela
			
			if((MinH == -1) || (MinH > H))
				MinH = H;
			if((MaxH == -1) || (MaxH < H))
				MaxH = H;
			if((MinV == -1) || (MinV > V))
				MinV = V;
			// Wyszukiwanie najwiekszej jasnosci piksela
			if((MaxV == -1) || (MaxV < V))
				MaxV = V;
			// Wyszukiwanie najmniejszego nasycenia piksela
			if((MinS == -1) || (MinS > S))
				MinS = S;

		}
	}

	Hmax = (int)MaxH;
	Hmin = (int)MinH;
	Vmax = (int)MaxV;
	Vmin = (int)MinV;
	Smin = (int)MinS;
	histogram->maxV = MaxV;
	histogram->minS = MinS;
	histogram->minV = MinV;
	histogram->histMaxVal = HHistMaxValue;
	histogram->h_size=360;

}

//////////////////////////////////////////////////////////////////////////

int piGeneral::init( PropertyMgr * pm )
{
	USE_PROPERTY_MGR( pm );

	histogram = new hist_data();
	histogram->hist_vals = new int[360];

	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void piGeneral::free()
{
	if( selected_region != NULL )
	{
		delete selected_region;
		selected_region = NULL;
	}

	if( histogram != NULL )
	{
		if( histogram->hist_vals != NULL )
		{
			delete [] histogram->hist_vals;
		}

		delete histogram;
		histogram = NULL;
	}
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

extern "C" {

__declspec(dllexport) piGeneral * export_module()
{
	return( new piGeneral );
}

};

//////////////////////////////////////////////////////////////////////////