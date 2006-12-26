/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	26:12:2006   13:20
	plik:    	mod_steer
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel: modul generujacy zdarzenia dla systemu operacyjnego    
*********************************************************************/

#ifndef __MOD_STEER_H__
#define __MOD_STEER_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"

//////////////////////////////////////////////////////////////////////////

class EXPORT_MODULE modSteer: public moduleBase
{
public:
	modSteer();
	virtual ~modSteer();

	virtual const char * get_module_description();

	virtual int  init( PropertyMgr * pm );
	virtual void free();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * result );

private:
	long alloc_mem;
	float_range factor;

	int	on_off;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MOD_STEER_H__
