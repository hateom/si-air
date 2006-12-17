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

/// mb_param::type

#define PT_UNDEFINED 0x00
#define PT_INT		 0x01
#define PT_LONG		 0x02
#define PT_FLOAT	 0x03
#define PT_DOUBLE	 0x04
#define PT_STRING	 0x05
#define PT_FILENAME  0x06

//////////////////////////////////////////////////////////////////////////

struct mb_param
{
	int		type;
	void *	data;
	char *  name;
	char *  description;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MB_PARAM_H__