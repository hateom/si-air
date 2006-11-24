#ifndef __INCLUDE_H__
#define __INCLUDE_H__
/*Struktura z zawartoscia ramki*/
struct frame_data
{
	unsigned int  width;
	unsigned int  height;

	/** Ilosc bajtow na pixel - dla RGB 3*/
	unsigned int  depth;
	/** Tablica wartosci pikseli, jedno wymiarowowa o dlugosci width*height*depth
	    Jeden piksel to 3 kolejne elementy w kolejnoœci G B R
	    P1       |P2      |P3      .....
	    [0][1][2][3][4][5][6][7][8]..... itd
	    |G  B  R |G  B  R |G  B  R|
	*/
	unsigned char * bits;
};

/*struktura przechowujaca informacje o prawdopodb. i obraz prawdopodob. */
struct pi_struct{
	/*przechowywana ramka*/
	frame_data * frame;
	/*tablica prawdopodobienstw dla kazdego piksela */
	float * prob_table;
};

#endif // __INCLUDE_H__