#define MOD_CPP
#include "mod_steer.h"
#include "../../module_base/src/status_codes.h"
#include <Windows.h>

//////////////////////////////////////////////////////////////////////////

#define MIN( A, B ) (A)<(B)?(A):(B)

//////////////////////////////////////////////////////////////////////////

modSteer::modSteer() : alloc_mem(0L)
{
	//REG_PARAM( PT_FLOAT_RANGE, factor, "Lighting factor (1.0f = neutral)", float_range( 1.0f, 0.1f, 10.0f ) );
}

//////////////////////////////////////////////////////////////////////////

modSteer::~modSteer()
{
}

//////////////////////////////////////////////////////////////////////////

const char * modSteer::get_module_description()
{
	static char descritpion[] = "System Command Generator";
	return( descritpion );
}	
	

//////////////////////////////////////////////////////////////////////////

int modSteer::init( PropertyMgr * pm )
{
	USE_PROPERTY_MGR( pm );
	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void modSteer::free()
{
}

//////////////////////////////////////////////////////////////////////////

int modSteer::input_type()
{
	return( MT_POSGEST );
}

//////////////////////////////////////////////////////////////////////////

int modSteer::output_type()
{
	return( MT_NONE );
}

//////////////////////////////////////////////////////////////////////////

proc_data * modSteer::process_frame( proc_data * prev_frame, int * result )
{
	int wx=prev_frame->position->x;
	int wy=prev_frame->position->y;
	int screenWitdh = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	int movieHeight = prev_frame->frame->height;
	int movieWidth = prev_frame->frame->width;
	float Xaspect = screenWitdh/movieWidth;
	float Yaspect = screenHeight/movieHeight;
	int x=(int)Xaspect*wx;
	int y=(int)Yaspect*wy;
	SetCursorPos(x,y);
	return prev_frame;
}

//////////////////////////////////////////////////////////////////////////
/// export funkcji exportujacej

extern "C" {

__declspec(dllexport) moduleBase * export_module()
{
	return( new modSteer );
}

};

//////////////////////////////////////////////////////////////////////////