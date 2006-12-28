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
	int temp_param;
	int alloc_mem;
	int initVal;
	float inv_maxVal;
	//int Hmax,Hmin,Vmax,Vmin,Smin;
	
	int_range Hmax,Hmin,Vmax,Vmin,Smin;;

	frame_data * inFrame;
	frame_data * selected_region;
	hist_data  * histogram;
	/// funkcja konwertujaca z formatu RGB do HSV
	/// \return void
	void piGeneral::RGBtoHSV(int& r, int& g, int& b, float& h, float& s, float& v);

	/// funkcja wyliczajaca histogram dla obszaru zaznaczenia
	/// \return void
	void hist();
};

//////////////////////////////////////////////////////////////////////////

#endif // __PI_GENERAL_H__