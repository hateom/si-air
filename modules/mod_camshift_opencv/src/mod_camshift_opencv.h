/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:52
	plik:    	mod_camshift_opencv
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __MOD_CAMSHIFT_OPENCV_H__
#define __MOD_CAMSHIFT_OPENCV_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#ifndef _EiC
#include "cv.h"
#include "highgui.h"
#include <stdio.h>
#include <ctype.h>
#endif

//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) mod_camshift_opencv: public moduleBase
{
public:
	mod_camshift_opencv();
	virtual ~mod_camshift_opencv();

	virtual const char * get_module_description();

	virtual int  init( PropertyMgr * pm );
	virtual void free();

	virtual int get_module_type();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * result );

private:
	long alloc_mem;
	float factor;


	int track_object;
	int bin_w;

};

//////////////////////////////////////////////////////////////////////////

#endif // __MOD_CAMSHIFT_OPENCV_H__
