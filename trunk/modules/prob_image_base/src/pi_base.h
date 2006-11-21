#ifndef __PROBL_IMAGE_BASE_H__
#define __PROBL_IMAGE_BASE_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"

//////////////////////////////////////////////////////////////////////////

/// klasa bazowa dla modulow tworzenia binarnego obrazu prawdopodobieñstwa
class __declspec(dllexport) piBase: public moduleBase
{
public:
	piBase() {}
	virtual ~piBase() {}

	virtual int process_frame( void * frame ) = 0;

	/// metoda zwalniajaca zasoby
	virtual void free() = 0;
protected:
};

#endif // __PROBL_IMAGE_BASE_H__