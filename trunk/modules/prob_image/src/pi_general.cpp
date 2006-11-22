#include "pi_general.h"

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

piGeneral::piGeneral()
{

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

int piGeneral::process_frame( void * out_frame )
{
	/*
	VLCVideoDataAccess InDataAccess = InBuffer->Data();
	TVLCVideoDataAccess OutDataAccess = OutBuffer->Data();

	IsReady = false;                                                // Bo rozpoczecie obliczen

	register TColor PixelColor;
	register int R, G, B;
	register float H, S, V;

	register int Xs;
	register int Xk;
	register int Ys;
	register int Yk;
	register float M00;
	register float M10;
	register float M01;
	register float M20;
	register float M02;
	register float M11;
	register float Max_Val;
	register float tan_fi;

	for(register int i=0;i<RepositionCount;i++)
	{
		Xs = MSCWindowXc-CWDx;
		Xk = MSCWindowXc+CWDx;
		Ys = MSCWindowYc-CWDy;
		Yk = MSCWindowYc+CWDy;
		M00 = 0.0;
		M10 = 0.0;
		M01 = 0.0;
		M11 = 0.0;
		M02 = 0.0;
		M20 = 0.0;
		Max_Val = 0.0;

		for(register int x=Xs;x<Xk;x++)
		{
			if((x >= 0) && (x < Width))
				for(register int y=Ys;y<Yk;y++)
				{
					if((y < 0) || (y >= Height)) continue;

					PixelColor = InDataAccess.GetPixel(x,y);
					R = PixelColor & 0xFF;
					G = (PixelColor >> 8) & 0xFF;
					B = (PixelColor >> 16) & 0xFF;
					RGBtoHSV(R, G, B, H, S, V);
					PImg[y][x] = 0.0;
					if((InitialValue) && (H >= HMin) && (H < HMax) && (V >= Vmin) && (V < Vmax) && (Smin < S))
						PImg[y][x] = 1;

					if((Calibration) && (V >= Vmin) && (V < Vmax) && (Smin < S))
					{
						if((HHist != NULL) && (Inv_HHistMaxVal)) PImg[y][x] += (float)HHist[int(H)]*Inv_HHistMaxVal;
						if((DHist != NULL) && (Inv_DHistMaxVal)) PImg[y][x] -= (float)DHist[int(H)]*Inv_DHistMaxVal;
						PImg[y][x] = PImg[y][x]<0.?0.:PImg[y][x];
					}


					// Wyszukiwanie max_wartosci prawdopodobienstwa
					if(PImg[y][x] > Max_Val)
						Max_Val = PImg[y][x];

					// Obliczanie momentow
					M00 += PImg[y][x];
					M10 += PImg[y][x]*(float)x;
					M01 += PImg[y][x]*(float)y;
					M20 += PImg[y][x]*(float)x*(float)x;
					M02 += PImg[y][x]*(float)y*(float)y;
					M11 += PImg[y][x]*(float)x*(float)y;

					if(ProbabilityImage)
					{
						register float channelval = PImg[y][x]*255.0;
						channelval = channelval>255?255:channelval;
						OutDataAccess.Pixels[x][y] = (TColor)RGB(channelval, channelval, channelval);
					}
				}
		}
	}
	*/
	return 0;
}

//////////////////////////////////////////////////////////////////////////


void piGeneral::free()
{
	
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