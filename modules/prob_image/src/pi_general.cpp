#define MOD_CPP
#define MOMENTS_SIZE 6
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

piGeneral::piGeneral() : alloc_mem(0), selected_region(NULL), histogram(NULL),
	hist_probability(NULL)
{
//	REG_PARAM( PT_INT, Hmax,			"Wart. maxymalna H", 35 );
//	REG_PARAM( PT_INT, Hmin,			"Wart. minimalna H", 10 );
//	REG_PARAM( PT_INT, Vmax,			"Wart. maxymalna V", 255 );
//	REG_PARAM( PT_INT, Vmin,			"Wart. minimalna V", 20 );
//	REG_PARAM( PT_INT, Smin,			"5. Wart. minimalna S", 0 );

	REG_PARAM(PT_BOOL, initVal, "Add 1 to probability", 1);
	REG_PARAM( PT_INT_RANGE, Hmax, "Maximum H value", int_range(  35, 0, 360 ) );
	REG_PARAM( PT_INT_RANGE, Hmin, "Minimum H value", int_range(  10, 0, 360 ) );
	REG_PARAM( PT_INT_RANGE, Vmax, "Maximum V value", int_range( 255, 0, 255 ) );
	REG_PARAM( PT_INT_RANGE, Vmin, "Minimum V value", int_range(  20, 0, 255 ) );
	REG_PARAM( PT_INT_RANGE, Smin, "Minimum S value", int_range(   0, 0, 200 ) );
	moments_local = NULL;
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
	static proc_data p_data = { 0, 0, 0, 0, 0 };
	static float * piTable = NULL;
	float maxVal = 0.0f;
//	float inv_maxVal;
	static int offs1, offs2, offs3;
	static unsigned int xs = 0, xk = width, ys = 0, yk = height, s = 0;
	
	retry = false;
	static_frame.depth = 4;
	static_frame.width = inFrame->width;
	static_frame.height = inFrame->height;

	if( alloc_mem == 0 )
	{
		alloc_mem = static_frame.depth*static_frame.height*static_frame.width;
		static_frame.bits = new unsigned char[alloc_mem];
		if (p_data.moments) 
		{
			delete [] p_data.moments;
		}
		p_data.moments = new float[MOMENTS_SIZE];
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

	for( int k=0; k<2; k++ )
	{
		if( k )
		{
			xs=(int)xc;
			ys=(int)yc;
			xk=(int)xc;
			yk=(int)yc;
			xs -= (int)( 1.2f*(float)s );
			xk += (int)( 1.2f*(float)s );
			ys -= (int)( 1.2f*(float)s );
			yk += (int)( 1.2f*(float)s );

			if( xs < 0 ) xs = 0;
			if( xk > width ) xk = width;
			if( ys < 0 ) ys=0;
			if( yk > height ) yk = height;
		}

		M00 = 0.0f;
		M10 = 0.0f;
		M01 = 0.0f;
		M20 = 0.0f;
		M02 = 0.0f;
		M11 = 0.0f;
		if (!k) 
			{
				memset(piTable,0,width*height);
				memset(static_frame.bits,0,alloc_mem);
			}
		for (unsigned int y=ys; y<yk; y++ )
		{
			offs1 = y*width;
			for (unsigned int x=xs; x<xk; x++ )
			{
				if (!k)
				{
					offs2 = (x+offs1)*4;
					B = inFrame->bits[offs2+0];
					G = inFrame->bits[offs2+1];
					R = inFrame->bits[offs2+2];
	
					RGBtoHSV( R, G, B, H, S, V );
	
					piTable[x+offs1] = 0.0;
	
					if( ( H >= Hmin ) && ( H < Hmax ) && ( V >= Vmin ) && ( V < Vmax ) && ( Smin < S ) )
					{
						if (initVal) piTable[x+offs1] = 1.0;
					}
					if( ( V >= Vmin ) && ( V < Vmax ) && ( Smin < S ) )
					{
						if ( histogram->histMaxVal )
						{
							piTable[x+offs1] += hist_probability[ int(H)];
							//(float)histogram->hist_vals[ int(H)]*inv_maxVal;
						}
					}
					if( preview_param )
					{
						float chVal = piTable[x+offs1]*255.0f;
						chVal = (chVal > 255.0f) ? 255.0f : chVal;

						static_frame.bits[offs2+0] = (unsigned char)chVal;
						static_frame.bits[offs2+1] = (unsigned char)chVal;
						static_frame.bits[offs2+2] = (unsigned char)chVal;
						//static_frame.bits[offs2+3] = 0;
					}
				}
				if (piTable[x+offs1] > maxVal) maxVal = piTable[x+offs1];
				offs3 = (x+offs1);
				M00 += piTable[offs3];
				M10 += piTable[offs3]*(float)x;
				M01 += piTable[offs3]*(float)y;
				M20 += piTable[offs3]*(float)x*(float)x;
				M02 += piTable[offs3]*(float)y*(float)y;
				M11 += piTable[offs3]*(float)x*(float)y;
			}
		}
		if( M00 > 20.0f)
		{
			float inv_M00 = 1.0f/M00;
			xc = M10*inv_M00;
			yc = M01*inv_M00;
		}
		//rozciagamy okno poszukiwan na cala klatke i jedziemy!
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
	// kopiowanie do struktury i zwrocenie
	p_data.input_frame = prev_frame->input_frame;
	p_data.frame =  &static_frame;
	p_data.prob = piTable;

	p_data.moments[0]=M00;
	p_data.moments[1]=M10;
	p_data.moments[2]=M01;
	p_data.moments[3]=M20;
	p_data.moments[4]=M02;
	p_data.moments[5]=M11;

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
		memcpy( selected_region->bits+i*sw*depth,
				inFrame->bits + ( (i+sy)*inFrame->width + sx )*depth ,sw*depth );
	}

	hist();
}
//////////////////////////////////////////////////////////////////////////

/// Funkcja oblicza histogram zaznaczonego obszaru.
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
	int offs1, offs2;

	width = selected_region->width;
	height = selected_region->height;
	depth = selected_region->depth;
	size =  width*height*depth;

//	for (int i=0;i<360;i++) histogram->hist_vals[i]=0;
	memset( histogram->hist_vals, 0, 360*sizeof(int) );

	for( int y=0; y<(int)height; ++y )
	{
		offs1 = y*width;
		for( int x=0; x<(int)width; ++x )
		{
			offs2 = (x+offs1)*4;
			B = selected_region->bits[offs2+0];
			G = selected_region->bits[offs2+1];
			R = selected_region->bits[offs2+2];
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
	if (HHistMaxValue) inv_maxVal = (float)1/(float)HHistMaxValue;
	for (int i=0; i<histogram->h_size;i++) 
	{
		hist_probability[i]=histogram->hist_vals[i]*inv_maxVal;
	}

}

//////////////////////////////////////////////////////////////////////////

int piGeneral::init( PropertyMgr * pm )
{
	USE_PROPERTY_MGR( pm );

	histogram = new hist_data();
	histogram->hist_vals = new int[360];
	hist_probability = new float[360];
	inv_maxVal = 0.0f;
	if (moments_local)
	{
		delete [] moments_local;
	}
	moments_local = new float[MOMENTS_SIZE];
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

	if (hist_probability)
	{
		delete [] hist_probability;
		hist_probability = NULL;
	}
	if (moments_local) 
	{
		delete [] moments_local;
		moments_local = NULL;
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