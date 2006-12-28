/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:50
	plik:    	mb_param
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __MB_PARAM_H__
#define __MB_PARAM_H__

//////////////////////////////////////////////////////////////////////////

/// mb_param::type - typy parametrow ktore moga byc 
/// zarejestrowane przez moduly

//#define PT_UNDEFINED	0x00	<- depreciated
#define PT_INT			0x01
#define PT_LONG			0x02
#define PT_BOOL			0x03
#define PT_FLOAT		0x04
#define PT_DOUBLE		0x05
#define PT_STRING		0x06
#define PT_FILENAME		0x07
#define PT_INT_RANGE	0x08
#define PT_FLOAT_RANGE	0x09
#define PT_PREVIEW		0x0A

//////////////////////////////////////////////////////////////////////////

class preview
{
public:
	preview() {}

	template<typename T>
	preview( int type_, long update_rat, T * data ) : type(type_), update_rate(update_rat)
	{ ptr = (void *)data; }

	template<typename T>
	T get_data() { return( *(T*)ptr ); }

	int		type;
	void *	ptr;
	long	update_rate;
};

class int_range
{
public:
	int_range() {}
	int_range( int val, int mn, int mx ) : value(val), minv(mn), maxv(mx) {}
	int value, maxv, minv;

	operator int() { return( value ); }
	int operator =( int val ) { return( value = val ); }
};

class float_range
{
public:
	float_range() {}
	float_range( float val, float mn, float mx ) : value(val), maxv(mx), minv(mn)  {}
	float value, maxv, minv;

	operator float() { return( value ); }
	float operator =( float val ) { return( value = val ); }
};

/// struktura przechowujaca informacje o parametrze modulu
struct mb_param
{
	int		type;			/// typ parametru (definicje powyzej)
	void *	data;			/// wskaznik do parametru
	char *  name;			/// nazwa parametru
	char *  description;	/// opis parametru
	int		visible;		/// czy parametr ma byc widoczny w opcjach programu
};

//////////////////////////////////////////////////////////////////////////

#endif // __MB_PARAM_H__