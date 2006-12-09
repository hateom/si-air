#ifndef __MOD_LIGHT_H__
#define __MOD_LIGHT_H__

#include "../../module_base/src/module_base.h"

class __declspec(dllexport) modLight: public moduleBase
{
public:
	modLight();
	virtual ~modLight();

	virtual const char * get_module_description();

	virtual int  init();
	virtual void free();

	virtual int get_module_type();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * result );

private:
	long alloc_mem;
	float factor;
};

#endif // __MOD_LIGHT_H__
