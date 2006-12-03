#ifndef __POSDETECT_H__
#define __POSDETECT_H__
//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

/// deklaracja typu uzytego wewnatrz klasy

//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) cPosdetect: public moduleBase
{
public:
	cPosdetect();
	virtual ~cPosdetect();

	virtual const char * get_module_description();
	virtual int get_module_type();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * result );

	virtual int  init();
	virtual void free();

//	virtual Tpos * calc_position( float * piTable , float maxVal, int width, int height, int * status );

private:
	void draw_frame_marker( frame_data * frame, int posx, int posy );

protected:
	int draw_marker;
	int or_mask_size;
	int temp_param;
	int alloc_mem;
};

//////////////////////////////////////////////////////////////////////////
/// export funkcji exportujacej bez wiklania nazw DLL

#ifdef __cplusplus
extern "C" {
#endif
//////////////////////////////////////////////////////////////////////////

/// funkcja exportujaca modul z biblioteki	
/// \return wskaznik do obiektu modulu
__declspec(dllexport) cPosdetect * export_module(); 


//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
};
#endif
#endif // __POSDETECT_H__