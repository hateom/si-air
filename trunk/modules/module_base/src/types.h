/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:51
	plik:    	types
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
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

#define GESTURE_NULL		0x00
#define GESTURE_LMBCLICK	0x01
#define GESTURE_RMBCLICK	0x02
#define GESTURE_LMBDBCLICK	0x03

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
	unsigned int  width;		/// szerokosc obrazu w pixelach
	unsigned int  height;		/// wysokosc obrazu w pixelach
	unsigned int  depth;		/// Ilosc bajtow na pixel - dla RGB 3
	/** Tablica wartosci pikseli, jedno wymiarowowa o dlugosci width*height*depth
	    Jeden piksel to 4 kolejne elementy w kolejnoœci G B R 0
	    P1          |P2         |P3         .....
	    [0][1][2][3][4][5][6][7][8][0][A][B]..... itd
	    |G  B  R  0 |G  B  R  0 |G  B  R  0|
	*/

	unsigned char * bits;		/// wskaznik do pixeli obrazu
};

//////////////////////////////////////////////////////////////////////////

/// Struktura do opisu po³ozenia obiektu int x,y; float angle;
struct pd_data
{
	int x,y;		/// pozycja myszy
	int gesture;	/// gest (definicje powyzej)
	float angle;	/// kat
};

//////////////////////////////////////////////////////////////////////////

/// Struktura opisuje dane ktore sa zwracane przez moduly, lub 
/// przekazywane na wejscie modulom
struct proc_data
{
	frame_data  *	input_frame;	/// ramka obrazu z modulu wejsciowego
	frame_data	*	frame;			/// ramka obrazu
	pd_data		*	position;		/// informacje o pozycji kursowa, gestach
	float		*	prob;			/// obraz prawdopodobienstwa
	float			max_prob;		/// maksymalna wartosc prawdopodobienstwa
	void		*	user_data0;		/// niezdefiniowane
	void		*	user_data1;		/// j/w
};

//////////////////////////////////////////////////////////////////////////

/// struktura przechowuje informacje o histogramie
struct hist_data
{
	int *	hist_vals;
	int		h_size;
	int		histMaxVal;
	float	maxV, minV, minS;
};
//////////////////////////////////////////////////////////////////////////

#endif // __INCLUDE_H__
