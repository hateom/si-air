#define MOD_CPP
#include "mod_steer.h"
#include "../../module_base/src/status_codes.h"
#include <windows.h>
#include <winuser.h>

//////////////////////////////////////////////////////////////////////////

#define MIN( A, B ) (A)<(B)?(A):(B)

//////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK KeyboardProc (int nCode, WPARAM wParam, LPARAM lParam)
{
	return 0;
}

//////////////////////////////////////////////////////////////////////////

int modSteer::get_control_state ()
{
	return on_off;
}
//////////////////////////////////////////////////////////////////////////

void modSteer::set_control_state( int param )
{
	on_off = param;
}
//////////////////////////////////////////////////////////////////////////


modSteer::modSteer() : alloc_mem(0L)
{
	//REG_PARAM( PT_FLOAT_RANGE, factor, "Lighting factor (1.0f = neutral)", float_range( 1.0f, 0.1f, 10.0f ) );
	REG_PARAM( PT_BOOL, on_off, "Turn steering on or off", 0 );
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
	hook = SetWindowsHookEx (13, (HOOKPROC) KeyboardProc, GetModuleHandle (NULL), 0);
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
	float Xaspect = (float)screenWitdh/(float)movieWidth;
	float Yaspect = (float)screenHeight/(float)movieHeight;
	int x=(int)Xaspect*wx;
	int y=(int)Yaspect*wy;
	if( on_off ) SetCursorPos(x,y);
	/*
	INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_RIGHTDOWN;
	SendInput(1,&ip,sizeof(ip));
	*/
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