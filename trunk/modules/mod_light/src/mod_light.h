/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:53
	plik:    	mod_light
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __MOD_LIGHT_H__
#define __MOD_LIGHT_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"

//////////////////////////////////////////////////////////////////////////

class EXPORT_MODULE modLight: public moduleBase
{
public:
	modLight();
	virtual ~modLight();

	virtual const char * get_module_description();

	virtual int  init( PropertyMgr * pm );
	virtual void free();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * result );

private:
	long alloc_mem;
	float_range factor;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MOD_LIGHT_H__
