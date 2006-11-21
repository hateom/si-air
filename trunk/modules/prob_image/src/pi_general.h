#ifndef __PI_GENERAL_H__
#define __PI_GENERAL_H__

//////////////////////////////////////////////////////////////////////////

#include "../../prob_image_base/src/pi_base.h"

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

	virtual void free();

	virtual int process_frame( void * frame );

protected:
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