#ifndef __PI_GENERAL_H__
#define __PI_GENERAL_H__
//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

/// deklaracja typu uzytego wewnatrz klasy

//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) piGeneral: public moduleBase
{
public:
	piGeneral();
	virtual ~piGeneral();

	virtual const char * get_module_description();
	virtual int get_module_type();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * status );
	virtual void mouse_select(int sx, int sy, int sw, int sh );

	virtual int  init( PropertyMgr * pm = NULL );
	virtual void free();

	//virtual pi_struct * process_frame( frame_data * inFrame, int * status );

protected:
	int temp_param;
	int alloc_mem;
	int Hmax,Hmin,Vmax,Vmin,Smin;
	frame_data * inFrame;
	frame_data * selected_region;
	hist_data  * histogram;

	void piGeneral::RGBtoHSV(int& r, int& g, int& b, float& h, float& s, float& v);
	void hist();
};

//////////////////////////////////////////////////////////////////////////

#endif // __PI_GENERAL_H__