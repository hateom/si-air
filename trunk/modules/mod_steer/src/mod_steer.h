/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	26:12:2006   13:20
	plik:    	mod_steer
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel: modul generujacy zdarzenia dla systemu operacyjnego    
*********************************************************************/

#ifndef __MOD_STEER_H__
#define __MOD_STEER_H__

//////////////////////////////////////////////////////////////////////////

#include "../../module_base/src/module_base.h"

//////////////////////////////////////////////////////////////////////////

/// Klasa (modul) do majaca za zadanie generowanie polecen dla systemu operacyjnego
/// to jest ostatni modul w torze
class EXPORT_MODULE modSteer: public moduleBase
{
public:
	modSteer();
	virtual ~modSteer();

	virtual const char * get_module_description();

	virtual int  init( PropertyMgr * pm );
	virtual void free();

	virtual int input_type();
	virtual int output_type();

	virtual proc_data * process_frame( proc_data * prev_frame, int * result );
	/// Funkcja zwracajaca wartosc parametru on_off
	/// \return int - wartosc parametru on_off (wl/wyl sterowania wskaznikiem myszy)
	int get_control_state ();
	/// Funkcja do ustawiania parametru on_off
	/// \return void
	void set_control_state( int param );

private:
	long alloc_mem;
	float_range factor;
	/// zmienna przechowuje informacje o tym czy ma byc wlaczone sterowanie
	/// wskaznikiem myszy, czy nie
	int	on_off;
	/// hook do klawiatury
	HHOOK hook;

	//LRESULT CALLBACK KeyboardProc (int nCode, WPARAM wParam, LPARAM lParam);
};

//////////////////////////////////////////////////////////////////////////

#endif // __MOD_STEER_H__
