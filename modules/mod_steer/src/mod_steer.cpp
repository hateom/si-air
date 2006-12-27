#define MOD_CPP
#include "mod_steer.h"
#include "../../module_base/src/status_codes.h"
#include <windows.h>

//////////////////////////////////////////////////////////////////////////

#define MIN( A, B ) (A)<(B)?(A):(B)

static modSteer * g_modSteer = NULL;

//////////////////////////////////////////////////////////////////////////

LRESULT CALLBACK KeyboardProc( int nCode, WPARAM wParam, LPARAM lParam )
{
	if( nCode < 0 )
	{
		return CallNextHookEx( NULL, nCode, wParam, lParam );
	}

	KBDLLHOOKSTRUCT * ptr = (KBDLLHOOKSTRUCT*)lParam;

	if( ptr->vkCode == VK_F12 )
	{
		/*if( wParam == WM_KEYDOWN )
		{
			if( g_modSteer->get_control_state() != 1 )
			{
				printf( ">>> on\n" );
				g_modSteer->set_control_state( 1 );
			}
		}
		else */
		if( wParam == WM_KEYUP )
		{
			//printf( ">>> off\n" );
			//g_modSteer->set_control_state( 0 );
			if (g_modSteer->get_control_state()) g_modSteer->set_control_state(0);
			else g_modSteer->set_control_state(1);
		}
	}

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
	g_modSteer = this;
	hook = SetWindowsHookEx( WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, GetModuleHandle( NULL ), 0 );
	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void modSteer::free()
{
	g_modSteer = NULL;
	UnhookWindowsHookEx( hook );
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
	static int prev_gest = GESTURE_NULL;
	if( on_off ) 
	{
		SetCursorPos(x,y);
		if (prev_frame->position->gesture==GESTURE_RMBDOWN && prev_gest == GESTURE_NULL)
		{
			INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_RIGHTDOWN;
			SendInput(1,&ip,sizeof(ip));
		}
		else  if (prev_frame->position->gesture==GESTURE_NULL && prev_gest == GESTURE_LMBDOWN) 
		{
			INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_LEFTDOWN;
			SendInput(1,&ip,sizeof(ip));	
		}
		else  if (prev_frame->position->gesture==GESTURE_NULL && prev_gest == GESTURE_RMBDOWN) 
		{
			INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_RIGHTUP;
			SendInput(1,&ip,sizeof(ip));	
		}
		else  if (prev_frame->position->gesture==GESTURE_NULL && prev_gest == GESTURE_LMBDOWN) 
		{
			INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_LEFTUP;
			SendInput(1,&ip,sizeof(ip));	
		}
		prev_gest = prev_frame->position->gesture;
	}

	
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