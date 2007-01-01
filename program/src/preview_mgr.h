/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:51
	plik:    	preview_mgr
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __PREVIEW_MGR_H__
#define __PREVIEW_MGR_H__

//////////////////////////////////////////////////////////////////////////

#include <qobject.h>
#include <vector>
#include "prevform.h"
#include "../../modules/module_base/src/types.h"

//////////////////////////////////////////////////////////////////////////

/// makro ulatwiajace korzystanie z obiektu globalnego
#define sPreviewMgr PreviewMgr::singleton()

//////////////////////////////////////////////////////////////////////////

/// klasa zarzadzajaca oknami podgladu
class PreviewMgr: public QObject
{
	Q_OBJECT

public:
	PreviewMgr();
	~PreviewMgr();

	/// rejestruj okno podgladu
	/// \return id okna podgladu
	int register_preview();

	/// renderuj ramke obrazu
	int render_frame( int preview, frame_data * frame );

	/// zamknij okno podgladu
	int close_preview( int preview );

	/// zamknij wszytkie okna podgladu
	int close_all();

	void show_window( int win, bool on_off );

	static PreviewMgr * singleton();

	void reset_positions();

public slots:
	void in_mouse_select( int sx, int sy, int sw, int sh );
	void preview_closed( int id );

signals:
	void mouse_select( int sx, int sy, int sw, int sh );
	void preview_closed();

private:
	void set_win_pos( PrevForm * prv );

	std::vector<PrevForm*> prev_list;
	int visible;
};

//////////////////////////////////////////////////////////////////////////

#endif // __PREVIEW_MGR_H__
