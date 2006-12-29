/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:53
	plik:    	posdetect
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    Modul wykrywajacy polozenie obiektu oraz orientacje
*********************************************************************/

#ifndef __POSDETECT_H__
#define __POSDETECT_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

class EXPORT_MODULE cPosdetect: public moduleBase
{
public:
	cPosdetect();
	virtual ~cPosdetect();

	virtual const char * get_module_description();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * result );

	virtual int  init( PropertyMgr * pm = NULL );
	virtual void free();

private:
	/// funkcja rysuje marker na obrazie
	/// \return void
	void draw_frame_marker( frame_data * frame, int posx, int posy, float angle );

protected:
	//int			or_mask_size;
	int				alloc_mem;
	float_range		angle_max;
	float_range		treshold;
	float			angle;
	preview			angle_prv;
	float			M00;
	float			M10;
	float			M01;
	float			M20;
	float			M02;
	float			M11;
	float			maxVal;
	float			*piTable;
	float			xc, yc;
	bool			retry;
	int				offs1, offs2;
	float			u;
};

//////////////////////////////////////////////////////////////////////////

#endif // __POSDETECT_H__