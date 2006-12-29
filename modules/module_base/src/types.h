/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:51
	plik:    	types
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    Plik zawiera potrzebne w programie struktury i definicje
*********************************************************************/

#ifndef __INCLUDE_H__
#define __INCLUDE_H__

//////////////////////////////////////////////////////////////////////////

#define FRAME_OFFSET( X, Y, W ) ((X)+((Y)*(W))
#define FRAME_PIXEL( X, Y, FRAMEDATA ) FRAMEDATA->bits[ FRAME_OFFSET( X, Y, FRAMEDATA->width )]

#define FRAME_PIXEL_B FRAME_PIXEL
#define FRAME_PIXEL_G( X, Y, FRAMEDATA ) FRAMEDATA->bits[ FRAME_OFFSET( X, Y, FRAMEDATA->width )+1]
#define FRAME_PIXEL_R( X, Y, FRAMEDATA ) FRAMEDATA->bits[ FRAME_OFFSET( X, Y, FRAMEDATA->width )+2]

//////////////////////////////////////////////////////////////////////////

#define GESTURE_NULL			0x00
#define GESTURE_LMBDOWN			0x01
#define GESTURE_LMBUP			0x02
#define GESTURE_RMBDOWN			0x04
#define GESTURE_RMBUP			0x08
#define GESTURE_MIDDLEBTNDOWN	0x16

//////////////////////////////////////////////////////////////////////////

#ifdef MOD_CPP
#define EXPORT_MODULE __declspec(dllexport)
#else
#define EXPORT_MODULE
#endif

//////////////////////////////////////////////////////////////////////////

/// struktura przechowujaca informacje o jednej klatce obrazu
struct frame_data
{
	/// szerokosc obrazu w pixelach
	unsigned int  width;
	/// wysokosc obrazu w pixelach
	unsigned int  height;
	/// Ilosc bajtow na pixel - dla RGB 4 (RGB0)
	unsigned int  depth;
	/// wskaznik do pixeli obrazu
	/** Tablica wartosci pikseli, jedno wymiarowowa o dlugosci width*height*depth
	    Jeden piksel to 4 kolejne elementy w kolejnoœci G B R 0
	    P1          |P2         |P3         .....
	    [0][1][2][3][4][5][6][7][8][0][A][B]..... itd
	    |G  B  R  0 |G  B  R  0 |G  B  R  0|
	*/

	unsigned char * bits;
};

//////////////////////////////////////////////////////////////////////////

/// Struktura do opisu po³ozenia obiektu int x,y; float angle;
struct pd_data
{
	/// pozycja myszy
	int x,y;
	/// gest
	int gesture;
	/// kat
	float angle;
};

//////////////////////////////////////////////////////////////////////////

/// Struktura opisuje dane ktore sa zwracane przez moduly, lub 
/// przekazywane na wejscie modulom
struct proc_data
{
	/// ramka obrazu z modulu wejsciowego
	frame_data  *	input_frame;
	/// ramka obrazu
	frame_data	*	frame;
	/// informacje o pozycji kursowa, gestach
	pd_data		*	position;
	/// obraz prawdopodobienstwa
	float		*	prob;
	/// maksymalna wartosc prawdopodobienstwa
	float			max_prob;
	//void		*	user_data0;
	//void		*	user_data1;		/// j/w
};

//////////////////////////////////////////////////////////////////////////

/// struktura przechowuje informacje o histogramie
struct hist_data
{
	/// Histogram
	int *	hist_vals;
	/// Wielkosc histogramu
	int		h_size;
	/// Najwieksza wartosc w histogramie
	int		histMaxVal;
	/// maksymalna i minimalna wartosc jasnosci, oraz minimalna wartosc nasycenia
	float	maxV, minV, minS;
};
//////////////////////////////////////////////////////////////////////////

#endif // __INCLUDE_H__
