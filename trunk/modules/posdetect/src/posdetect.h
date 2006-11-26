#ifndef __POSDETECT_H__
#define __POSDETECT_H__
//////////////////////////////////////////////////////////////////////////

#include "../../posdetect_base/src/pd_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

/// deklaracja typu uzytego wewnatrz klasy

//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) cPosdetect: public pdBase
{
public:
	cPosdetect();
	virtual ~cPosdetect();

	virtual const char * get_module_description();
	virtual int get_module_type();

	virtual void free();

	virtual Tpos * calc_position( float * piTable , int * status );

protected:
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