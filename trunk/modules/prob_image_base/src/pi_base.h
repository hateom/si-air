#ifndef __PROBL_IMAGE_BASE_H__
#define __PROBL_IMAGE_BASE_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#include "../../module_base/src/types.h"
//#include "../../video_acq_base/src/va_base.h"

//////////////////////////////////////////////////////////////////////////

/// klasa bazowa dla modulow tworzenia binarnego obrazu prawdopodobieñstwa
class __declspec(dllexport) piBase: public moduleBase
{
public:
	piBase() {}
	virtual ~piBase() {}

	virtual pi_struct * process_frame( frame_data * inFrame, int * status ) = 0;

	/// metoda zwalniajaca zasoby
	virtual void free() = 0;
protected:
};

#endif // __PROBL_IMAGE_BASE_H__