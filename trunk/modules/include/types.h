#ifndef __INCLUDE_H__
#define __INCLUDE_H__
#include "../video_acq_base/src/va_base.h"
/*
struct frame_data
{
	unsigned int  width;
	unsigned int  height;
	unsigned int  depth;
	unsigned char * bits;
};
*/
/*struktura przechowujaca informacje o prawdopodb. i obraz prawdopodob. */
struct pi_struct{
	/*przechowywana ramka*/
	frame_data * frame;
	/*tablica prawdopodobienstw dla kazdego piksela */
	float * prob_table;
};

#endif // __INCLUDE_H__