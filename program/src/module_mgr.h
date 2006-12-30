/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:51
	plik:    	module_mgr
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __MODULE_MGR_H__
#define __MODULE_MGR_H__

//////////////////////////////////////////////////////////////////////////

#include <qobject.h>
#include <qtimer.h>
#include <qstring.h>
#include <vector>
#include <string>
#include "../../modules/module_base/src/module_base.h"
#include "../../modules/module_base/src/property_mgr.h"

//////////////////////////////////////////////////////////////////////////

/// makro ulatwiajace korzystanie z modulu globalnego
#define sModuleMgr ModuleMgr::singleton()

//////////////////////////////////////////////////////////////////////////

/// klasa zarzadzajaca modulami
class ModuleMgr: public QObject
{
	Q_OBJECT

public:
	ModuleMgr();
	~ModuleMgr();

	/// metoda laduje obiekty z dysku, z katalogu `directory`
	int load_modules( std::string directory );

	/// metoda zwalnia zasoby z modulow, i zwalnia biblioteki dll
	int unload_modules();

	/// metoda zwraca wskaznik do obiektu globalnego
	static ModuleMgr * singleton();

	int get_proper_modules( std::vector<moduleBase*> & list );

	int remove_module( moduleBase * mod );

private:
	moduleBase * last_on_path();

public slots:
	void clear_path();										/// slot czyszczacy tor przetwarzania
	void add_to_path( int module );							/// slot dodajacy modul do toru przetwarzania
	void add_to_path( moduleBase * mod );					/// j/w
	void start_processing();								/// slot rozpoczynajacy przetwarzanie
	void stop_processing();									/// slot zatrzymujacy przetwarzanie
	void process_frame();									/// slot rzetwarzajacy jedna ramke obrazu
	void mouse_select( int sx, int sy, int sw, int sh );	/// zaznaczenie fragmentu okna podgladu

	void switch_preview( int module, bool on );				/// zamkniecie lub otworzenie okna podgladu

signals:
	void module_loaded( moduleBase * base, int no );		/// sygnal zaladowania modulu
	void module_unload( moduleBase * base, int no );		/// sygnal usuniecia modulu
	void added_to_path( moduleBase * base, int no );		/// sygnal dodania modulu do toru
	void path_cleared();									/// sygnal wyczyszczenia toru
	void processing_started();								/// sygnal rozpoczenia przetwarzania
	void processing_finished();								/// sygnal zatrzymania przetwarzania
	void module_removed();

private:
	int load_single_module( std::string filename );			/// metoda laduje pojedynczy modul
	std::vector<moduleBase*> module_list;					/// wektor modulow
	std::vector<int> path_list;								/// wektor modulow znajdujacych sie w torze
	std::vector<int> prev_list;								/// wektor okien podgladu

	bool is_running;										/// flaga oznaczajaca dzialanie przetwarzania
	QTimer * timer;											/// timer taktujacy przetwarzanie ramek obrazu
	PropertyMgr property_mgr;								/// obiekt do zarzadzania globalnymi parametrami
};

//////////////////////////////////////////////////////////////////////////

#endif // __MODULE_MGR_H__
