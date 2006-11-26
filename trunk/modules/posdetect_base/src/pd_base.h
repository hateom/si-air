#ifndef __POSDETECT_BASE_H__
#define __POSDETECT_BASE_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"
#include "../../module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

/// klasa bazowa dla modulow tworzenia binarnego obrazu prawdopodobieñstwa
class __declspec(dllexport) pdBase: public moduleBase
{
public:
	pdBase() {}
	virtual ~pdBase() {}

	virtual Tpos * calc_position( float * piTable , int * status ) = 0;

	/// metoda zwalniajaca zasoby
	virtual void free() = 0;
protected:
};

#endif // __POSDETECT_BASE_H__