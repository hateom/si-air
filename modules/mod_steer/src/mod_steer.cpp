#define MOD_CPP
#include "mod_steer.h"
#include "../../module_base/src/status_codes.h"
#include <windows.h>

//////////////////////////////////////////////////////////////////////////

#include "../../posdetect/src/marker_data.h" /// marker zapisany jako tablica pixeli

static const int marker_w_2 = MARKER_W/2;
static const int marker_h_2 = MARKER_H/2;

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
	REG_PARAM( PT_INT_RANGE, window_size, "Wielkosc okna neutralnego", int_range(40,20,100));
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

	static proc_data p_data = { 0, 0, 0, 0, 0 };
	static frame_data frame = { 0, 0, 0, 0 };
	static int xpos, ypos;
	static int alloc_mem;

	if( mov_w != prev_frame->frame->width || mov_h != prev_frame->frame->width )
	{
		mov_w = prev_frame->frame->width;
		mov_h = prev_frame->frame->height;
		screen_width = GetSystemMetrics(SM_CXSCREEN);
		screen_height = GetSystemMetrics(SM_CYSCREEN);
		x_asp = (float) screen_width / (float)mov_w;
		y_asp = (float) screen_height / (float)mov_h;
	}
	xpos = prev_frame->position->x;
	ypos = prev_frame->position->y;
	if( on_off ) 
	{
		if(steer_type_position)
			position_steer( xpos, ypos,
							prev_frame->position->gesture);
		else 
			speed_steer(xpos, ypos,
						prev_frame->position->gesture);
	}
	
	if( preview_param )
	{
		if( alloc_mem == 0 )
		{
			alloc_mem = prev_frame->frame->depth*prev_frame->frame->height*prev_frame->frame->width;
			frame.bits = new unsigned char[alloc_mem];
			frame.depth = 4; //(3*frame->depth)/8;
			frame.width=mov_w;
			frame.height=mov_h;
		}
		else
		{
			if( alloc_mem != frame.depth*frame.height*frame.width )
			{
				delete [] frame.bits;
				alloc_mem =  prev_frame->frame->depth*prev_frame->frame->height*prev_frame->frame->width;
				frame.bits = new unsigned char[alloc_mem];
				frame.depth = 4; //(3*frame->depth)/8;
				frame.width=mov_w;
				frame.height=mov_h;

			}
		}

		memcpy( frame.bits, prev_frame->input_frame->bits, mov_h*mov_w*4);

		draw_frame_marker( &frame, xpos, ypos, 0.0f );
	}
	p_data.frame = &frame;
	frame.width = prev_frame->input_frame->width;
	frame.height = prev_frame->input_frame->height;
	return &p_data;
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
	send_input(gesture);
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
//////////////////////////////////////////////////////////////////////////
void modSteer::draw_frame_marker( frame_data * frame, int posx, int posy, float angle )
{
	static long ox1, ox2, oy1, oy2;
	for( int y=0; y<MARKER_H; ++y )
	{
		oy1 = (posy+y-marker_h_2)*frame->width;
		oy2 = y*MARKER_W;
		for( int x=0; x<MARKER_W; ++x )
		{
			ox1 = (posx+x-marker_w_2+oy1)*4;
			ox2 = (x+oy2)*3;
			if( posx+x-marker_w_2 < 0 || posx+x-marker_w_2 >= (int)frame->width ||
				posy+y-marker_h_2 < 0 || posy+y-marker_h_2 >= (int)frame->height )
			{
				continue;
			}
			if( marker[ox2+0] != 0 )
			{
				frame->bits[ox1+0] = marker[ox2+0];
				frame->bits[ox1+1] = marker[ox2+1];
				frame->bits[ox1+2] = marker[ox2+2];

				if (prev_gest == GESTURE_LMBDOWN)		frame->bits[ox1+2] = 100;
				if (prev_gest == GESTURE_RMBDOWN)		frame->bits[ox1+1] = 150;
				if (prev_gest == GESTURE_MIDDLEBTNDOWN)	frame->bits[ox1+0] = 150;
			}
		}
	}
	if (!steer_type_position)
	{
		static int xc,yc;
		xc = (int)(0.5*mov_w);
		yc = (int)(0.5*mov_h);
/// rysowanie wskaznikow
		/// gorny pionowy
		for (int u=0;u<yc-(int)(0.5f*window_size);u++)
		{
			frame->bits[(u*mov_w+xc)*4+2] = 255;
		}
		/// dolny pionowy
		for (int u=yc+(int)(0.5f*window_size);u<(int)mov_h;u++)
		{
			frame->bits[(u*mov_w+xc)*4+2] = 255;
		}
		/// lewy poziomy
		for (int u=0;u<xc-(int)(0.5f*window_size);u++)
		{
			frame->bits[(yc*mov_w+u)*4+2] = 255;
		}
		//prawy poziomy
		for (int u=xc+(int)(0.5f*window_size);u<(int)mov_w;u++)
		{
			frame->bits[(yc*mov_w+u)*4+2] = 255;
		}
		/// pionowa czesc okienka
		for (int u=0;u<2;u++) 
		{
			int y_line = (int)(yc+(-0.5+u)*window_size);
			for (int i=(int)(xc-0.5*window_size);i<(int)(xc+0.5*window_size);i++)
			{
				frame->bits[(y_line*mov_w+i)*4] = 255;
			}
		}
		/// pozioma czesc okienka
		for (int u=0;u<2;u++) 
		{
			int x_line = (int)(xc+(-0.5+u)*window_size);
			for (int i=(int)(yc-0.5*window_size);i<(int)(yc+0.5*window_size);i++)
			{
				frame->bits[(i*mov_w+x_line)*4] = 255;
			}
		}
		/// znaczniki wychylenia - w poziomie
		if (abs(xc-posx)>(int)(window_size*0.5))
		{
			for (int u=yc-10;u<yc+10;u++)
			{
				frame->bits[(u*mov_w+posx)*4+1] = 255;
			}
		}
		/// znaczniki wychylenia - w pionie
		if (abs(yc-posy)>(int)(window_size*0.5))
		{
			for (int u=xc-10;u<xc+10;u++)
			{
				frame->bits[(posy*mov_w+u)*4+1] = 255;
			}
		}
	}
}
/// export funkcji exportujacej

extern "C" {

__declspec(dllexport) moduleBase * export_module()
{
	return( new modSteer );
}

};

//////////////////////////////////////////////////////////////////////////