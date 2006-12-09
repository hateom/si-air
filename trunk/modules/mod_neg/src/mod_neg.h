#ifndef __MOD_NEG_H__
#define __MOD_NEG_H__

#include "../../module_base/src/module_base.h"

class __declspec(dllexport) modNeg: public moduleBase
{
public:
	modNeg();
	virtual ~modNeg();

	virtual const char * get_module_description();

	virtual int  init();
	virtual void free();

	virtual int get_module_type();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * result );

private:
	int alloc_mem;
};

#endif // __MOD_NEG_H__
