/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:53
	plik:    	posdetect
	autorzy:	Tomasz Huczek, Andrzej Jasi�ski
	
    cel:	    Modul wykrywajacy polozenie obiektu oraz orientacje
*********************************************************************/

#ifndef __POSDETECT_H__
#define __POSDETECT_H__
#define MOMENTS_SIZE 6
//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

/// klasa(modul) odpowiedzialna za wyznaczenie pozycji oraz orientacji obiektu
/// po tym module powinien byc modul generacji polecen dla OS
class EXPORT_MODULE cPosdetect: public moduleBase
{
public:
	cPosdetect();
	virtual ~cPosdetect();
	virtual const char * get_module_description();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * result );
	void mouse_select(int sx, int sy, int sw, int sh );

	virtual int  init( PropertyMgr * pm = NULL );
	virtual void free();

private:
	/// funkcja rysuje marker na obrazie
	/// \return void
	void draw_frame_marker( frame_data * frame, int posx, int posy, float angle );

protected:
	//int			or_mask_size;
	int				alloc_mem;
	/// wartosc graniczna kata, po przekroczeniu ktorej jest wykrywane klikniecie
	float_range		angle_max;
	/// szerokosc "histerezy"
	float_range		treshold;
	float			angle;
	preview			angle_prv;
	/// moment M00
	float			M00;
	/// Moment M10
	float			M10;
	/// Moment M01 
	float			M01;
	/// Moment M20
	float			M20;
	/// Moment M02
	float			M02;
	/// Moment M11
	float			M11;
	/// maksymalna wartosc w histogramie
	//float			maxVal;
	/// wartosci prawdopodobienst przyn. piksela do obiektu
	//float			*piTable;
	/// wspolrzedne srodka masy
	float			xc, yc;
	/// zmienne pomocnicze do wyznaczania pozycji piksela
	int				offs1, offs2;
	/// przewrotnie nazwana wartosc kata
	float			u;
	/// zmienna przechowujaca ostatnia wartosc wykrytego gestu
	int				last_gesture;
	/// bufor pamietajacy kilka ostatnich proporcji wys/szer obiektu
	float			*buffer;
	/// rozmiar bufora proporcji
	int_range		buff_size;
	/// jaki ma byc stosunek wyspocz/wyskonc
	float_range		ratio;
	/// czy uzywac emulacji 3-go przycisku
	int				thirdBtn;
	/// czy korygowac polozenie
	int correctPlacement;
	/// czy analizowana ramka jest pierwsza
	bool			isFirst;
};

//////////////////////////////////////////////////////////////////////////

#endif // __POSDETECT_H__