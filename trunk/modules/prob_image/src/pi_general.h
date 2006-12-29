/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:54
	plik:    	pi_general
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:		Modul generujacy obraz prawdopodobienstwa
*********************************************************************/

#ifndef __PI_GENERAL_H__
#define __PI_GENERAL_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

class EXPORT_MODULE piGeneral: public moduleBase
{
public:
	piGeneral();
	virtual ~piGeneral();

	virtual const char * get_module_description();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * status );
	virtual void mouse_select(int sx, int sy, int sw, int sh );

	virtual int  init( PropertyMgr * pm = NULL );
	virtual void free();

protected:
	int				temp_param;
	int				alloc_mem;
	int				initVal;
	/// odwrotnosc najwiekszej wart. w histogramie - do przyspieszenia obliczen
	/// (eliminacja dzielen)
	float			inv_maxVal;
	/// Maksymlana i minimalna wartosc koloru, max i min wartosc jasnosci
	/// Smin - minimalna wartosc saturacji
	int_range		Hmax,Hmin,Vmax,Vmin,Smin;;
	/// ramka wejsciowa
	frame_data	*	inFrame;
	/// zmienna przechowujaca wybrany region
	frame_data	*	selected_region;
	/// przechowuje histogram wraz z jego skladowymi
	hist_data	*	histogram;
	/// histogram z wartosciami wydzielonymi przez histMaxVal
	/// stworzony, aby uniknac wielokrotnego dzielenia tego samego
	float		*	hist_probability;
	/// funkcja konwertujaca z formatu RGB do HSV
	/// \return void
	void piGeneral::RGBtoHSV(int& r, int& g, int& b, float& h, float& s, float& v);

	/// funkcja wyliczajaca histogram dla obszaru zaznaczenia
	/// \return void
	void hist();
};

//////////////////////////////////////////////////////////////////////////

#endif // __PI_GENERAL_H__