#ifndef __PI_GENERAL_H__
#define __PI_GENERAL_H__
//////////////////////////////////////////////////////////////////////////

#include "../../prob_image_base/src/pi_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

/// deklaracja typu uzytego wewnatrz klasy

//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) piGeneral: public piBase
{
public:
	piGeneral();
	virtual ~piGeneral();

	virtual const char * get_module_description();
	virtual int get_module_type();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * status );

	virtual void free();

	//virtual pi_struct * process_frame( frame_data * inFrame, int * status );

protected:
	int temp_param;
	int alloc_mem;
	int Hmax,Hmin,Vmax,Vmin,Smin;

	void piGeneral::RGBtoHSV(int& r, int& g, int& b, float& h, float& s, float& v);
};

//////////////////////////////////////////////////////////////////////////
/// export funkcji exportujacej bez wiklania nazw DLL

#ifdef __cplusplus
extern "C" {
#endif
//////////////////////////////////////////////////////////////////////////

/// funkcja exportujaca modul z biblioteki	
/// \return wskaznik do obiektu modulu
__declspec(dllexport) piGeneral * export_module(); 


//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
};
#endif
#endif // __PI_GENERAL_H__