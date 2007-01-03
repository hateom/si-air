#define MOD_CPP
#include "mod_steer.h"
#include "../../module_base/src/status_codes.h"
#include <windows.h>

//////////////////////////////////////////////////////////////////////////

#define MIN( A, B ) (A)<(B)?(A):(B)

static modSteer * g_modSteer = NULL;

//////////////////////////////////////////////////////////////////////////
/// CALLBACK hooka klawiatury
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
			if (g_modSteer->get_control_state()) 
			{
				g_modSteer->set_control_state(0);
				INPUT ip; 
				if (g_modSteer->get_last_gesture() == GESTURE_LMBDOWN)
				{
					ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_LEFTUP;
					SendInput(1,&ip,sizeof(ip));
				}
				if (g_modSteer->get_last_gesture() == GESTURE_RMBDOWN)
				{
					ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_RIGHTUP;
					SendInput(1,&ip,sizeof(ip));
				}
				if (g_modSteer->get_last_gesture() == GESTURE_MIDDLEBTNDOWN)
				{
					ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_MIDDLEUP;
					SendInput(1,&ip,sizeof(ip));
				}

			}
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


modSteer::modSteer() : alloc_mem(0L), mov_w(0), mov_h(0)
{
	//REG_PARAM( PT_FLOAT_RANGE, factor, "Lighting factor (1.0f = neutral)", float_range( 1.0f, 0.1f, 10.0f ) );
	REG_PARAM( PT_BOOL, on_off, "Turn steering on or off [F12]", 0 );
	REG_PARAM( PT_BOOL, steer_type_position, "Steering type (1)Position (0)Speed", 1 );
	REG_PARAM( PT_FLOAT_RANGE, steer_speed, "Steer Speed Ratio", float_range( 0.5f, 0.01f, 1.0f ));
	REG_PARAM( PT_INT_RANGE, window_size, "Wielkosc okna neutralnego", int_range(10,5,30));
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
	prev_gest = GESTURE_NULL;
	hook = SetWindowsHookEx( WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, GetModuleHandle( NULL ), 0 );
	return( ST_OK );
}

//////////////////////////////////////////////////////////////////////////

void modSteer::free()
{
	g_modSteer = NULL;
	UnhookWindowsHookEx( hook );
	INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_LEFTUP;
	SendInput(1,&ip,sizeof(ip));
	ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_RIGHTUP;
	SendInput(1,&ip,sizeof(ip));
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

	if( mov_w != prev_frame->frame->width || mov_h != prev_frame->frame->width )
	{
		mov_w = prev_frame->frame->width;
		mov_h = prev_frame->frame->height;
		screen_width = GetSystemMetrics(SM_CXSCREEN);
		screen_height = GetSystemMetrics(SM_CYSCREEN);
		x_asp = (float) screen_width / (float)mov_w;
		y_asp = (float) screen_height / (float)mov_h;
	}

	if( on_off ) 
	{
		if(steer_type_position)
			position_steer( prev_frame->position->x, prev_frame->position->y,
							prev_frame->position->gesture);
		else 
			speed_steer(prev_frame->position->x, prev_frame->position->y,
						prev_frame->position->gesture);
	}
	return prev_frame;
}
//////////////////////////////////////////////////////////////////////////

void modSteer::position_steer( int xpos, int ypos, int gesture)
{
	static int last_pos_x=0, last_pos_y=0;
	int x = (int)(x_asp*(float)xpos);
	int y = (int)(y_asp*(float)ypos);

	SetCursorPos(int(0.5*(x+last_pos_x)),int(0.5*(y+last_pos_y)));
	last_pos_x=x; last_pos_y=y;
	send_input(gesture);
}
//////////////////////////////////////////////////////////////////////////

void modSteer::speed_steer ( int xpos, int ypos, int gesture)
{
	static int xc = (int)(mov_w *0.5f) , yc = (int)(mov_h *0.5f);
	static int last_x=(int)(screen_width*0.5f), last_y = int(screen_height*0.5f);

	if (abs(xc-xpos)>window_size || abs(yc-ypos)>window_size)
	{
		x = last_x - (int)(x_asp*( steer_speed*(xc-xpos) ));
		y = last_y - (int)(y_asp*( steer_speed*(yc-ypos) ));
		if (x>screen_width) x=screen_width;
		if (x<0) x=0;
		if (y>screen_height) y=screen_height;
		if (y<0) y=0;
	}
	else 
	{
		//x = l;
		//y = ;
	}
	last_x = x;
	last_y = y;
	SetCursorPos(x,y);
	//send_input(gesture);
}

//////////////////////////////////////////////////////////////////////////

void modSteer::send_input( int gesture )
{

	if (gesture==GESTURE_RMBDOWN && prev_gest == GESTURE_NULL)
	{
		INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_RIGHTDOWN;
		SendInput(1,&ip,sizeof(ip));
	}
	else  if (gesture==GESTURE_LMBDOWN && prev_gest == GESTURE_NULL) 
	{
		INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_LEFTDOWN;
		SendInput(1,&ip,sizeof(ip));	
	}
	else  if (gesture==GESTURE_MIDDLEBTNDOWN && prev_gest == GESTURE_NULL) 
	{
		INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_MIDDLEDOWN;
		SendInput(1,&ip,sizeof(ip));	
	}
	else  if (gesture==GESTURE_NULL && prev_gest == GESTURE_RMBDOWN) 
	{
		INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_RIGHTUP;
		SendInput(1,&ip,sizeof(ip));	
	}
	else  if (gesture==GESTURE_NULL && prev_gest == GESTURE_LMBDOWN) 
	{
		INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_LEFTUP;
		SendInput(1,&ip,sizeof(ip));	
	}
	else  if (gesture==GESTURE_NULL && prev_gest == GESTURE_MIDDLEBTNDOWN) 
	{
		INPUT ip; ZeroMemory(&ip,sizeof(ip)); ip.type=INPUT_MOUSE; ip.mi.dwFlags=MOUSEEVENTF_MIDDLEUP;
		SendInput(1,&ip,sizeof(ip));	
	}
	prev_gest = gesture;
}

//////////////////////////////////////////////////////////////////////////

int modSteer::get_last_gesture ()
{
	return prev_gest;
}

/// export funkcji exportujacej

extern "C" {

__declspec(dllexport) moduleBase * export_module()
{
	return( new modSteer );
}

};

//////////////////////////////////////////////////////////////////////////