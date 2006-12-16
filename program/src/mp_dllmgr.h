#ifndef __MP_DLLMGR_H__
#define __MP_DLLMGR_H__

//////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include "../../modules/module_base/src/module_base.h"

//////////////////////////////////////////////////////////////////////////

/// struktura przechowujaca informacje o kazdym module, 
/// ktory mozna zaladowac
struct mp_dll_module
{
	std::string filename;
	std::string description;
//	int			type;
};

//////////////////////////////////////////////////////////////////////////

/// klasa zarzadzajaca obsluga modulow
class mpdllMgr
{
public:
	mpdllMgr();
	virtual ~mpdllMgr();

	/// metoda wczytuje podstawowe informacje o modulach z danego katalogu
	/// \param directory sciezka dostepu do katalogu z modulami
	/// \return 0 w przypadku powodzenia, wartosc ujemna w przypadku bledu
	int read_module_directory( std::string directory );

	/// zwalnia pamiec
	void free();

	moduleBase * load_module( mp_dll_module * module_info );

	int count();
	mp_dll_module * get_module_info( int item_no );

private:

	/// prywatna metoda wczytujaca informacje z konkretnego modulu
	/// na podstawie nazwy pliku przekazanej w strukturze \b mp_dll_module
	/// \param item wskaznik do struktury mp_dll_module zawierajacy pole z 
	///				informacja o nazwie pliku modulu
	/// \return 0 w przypadku powodzenia, liczba ujemna w przypadku bledu
	int get_module_information( mp_dll_module * item );

	/// lista zaladowanych modulow
	std::vector<mp_dll_module*> list;
};

//////////////////////////////////////////////////////////////////////////

#endif // __MP_DLLMGR_H__
