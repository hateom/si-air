#include "posdetect.h"
#include "../../module_base/src/types.h"
#include "../../module_base/src/status_codes.h"

#include <cv.h>
#include <highgui.h>
#include <cvcam.h>

#pragma comment(lib,"cv.lib")
#pragma comment(lib,"cxcore")
#pragma comment(lib,"cvaux")
#pragma comment(lib,"cv")
#pragma comment(lib,"ml")
#pragma comment(lib,"highgui")

// #pragma warning ( disable: 4244 )	// convertion float->int (RGBtoHSV)

//////////////////////////////////////////////////////////////////////////

cPosdetect::cPosdetect()
{
//	REG_PARAM( PT_INT, Smin, "5. Wart. minimalna H", 15 );
}

//////////////////////////////////////////////////////////////////////////

cPosdetect::~cPosdetect()
{

}

//////////////////////////////////////////////////////////////////////////

const char * cPosdetect::get_module_description()
{
	static char descritpion[] = "Position, Rotation and Gesture Detection Module : Simple Implementation";
	return( descritpion );
}

//////////////////////////////////////////////////////////////////////////

int cPosdetect::get_module_type()
{
	return( MT_GESTURES );
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

Tpos * cPosdetect::calc_position( float * piTable , int * status )
{
	static Tpos pos;
	*status = ST_OK;
	return ( &pos );
}

//////////////////////////////////////////////////////////////////////////


void cPosdetect::free()
{
	
}

//////////////////////////////////////////////////////////////////////////
/// export funkcji exportujacej

#ifdef __cplusplus
extern "C" {
#endif

//////////////////////////////////////////////////////////////////////////

__declspec(dllexport) cPosdetect * export_module()
{
	return( new cPosdetect );
}

//////////////////////////////////////////////////////////////////////////

#ifdef __cplusplus
};
#endif

//////////////////////////////////////////////////////////////////////////