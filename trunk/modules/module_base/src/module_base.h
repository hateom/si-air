#ifndef __MODULE_BASE_H__
#define __MODULE_BASE_H__

//////////////////////////////////////////////////////////////////////////

#include <windows.h>

//////////////////////////////////////////////////////////////////////////

/// Typy modu³ów - wartosci zwracane przez get_module_type

#define MT_VIDEO_ACQ		0x01
#define MT_PROBABILITY		0x02
#define MT_GESTURES			0x03
#define MT_INPUT			0x04

//////////////////////////////////////////////////////////////////////////

/// tablica opisujaca kazdy z typow modulow 
/// zadeklarowanych powyzej
static char * mt_description[] = { 
	"undefined", 
	"Video Acquisiton Type", 
	"Probability Image Module", 
	"Getures and Position Detection Module", 
	"Input Handler Module",
	0
};

//////////////////////////////////////////////////////////////////////////

/// klasa bazowa dla wszystkich modulow
class __declspec(dllexport) moduleBase
{
public:
	moduleBase() : lib_handle(NULL) {}
	virtual ~moduleBase() { FreeLibrary( lib_handle ); }

	/// metoda zwracajaca opis danego modulu
	/// \return opis danego modulu jako tablice znakow
	virtual const char * get_module_description() = 0;

	/// zwraca informacja o typie modulu
	/// \return typ modulu zadeklarowany jako MT_*
	virtual int get_module_type() = 0;

	virtual void assign_library_handle( HMODULE hlib ) { lib_handle = hlib; }

protected:
	HMODULE lib_handle;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MODULE_BASE_H__
