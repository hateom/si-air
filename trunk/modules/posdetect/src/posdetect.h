/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:53
	plik:    	posdetect
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __POSDETECT_H__
#define __POSDETECT_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) cPosdetect: public moduleBase
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
	void draw_frame_marker( frame_data * frame, int posx, int posy, float angle );

protected:
	int or_mask_size;
	int alloc_mem;
	int angle_max;
};

//////////////////////////////////////////////////////////////////////////

#endif // __POSDETECT_H__