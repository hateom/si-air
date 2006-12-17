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

#define sPreviewMgr PreviewMgr::singleton()

//////////////////////////////////////////////////////////////////////////

class PreviewMgr: public QObject
{
	Q_OBJECT

public:
	PreviewMgr();
	~PreviewMgr();

	int register_preview();
	int render_frame( int preview, frame_data * frame );
	int close_preview( int preview );
	int close_all();

	static PreviewMgr * singleton();

public slots:
	void in_mouse_select( int sx, int sy, int sw, int sh );
	void preview_closed( int id );

signals:
	void mouse_select( int sx, int sy, int sw, int sh );

private:
	std::vector<PrevForm*> prev_list;
};

//////////////////////////////////////////////////////////////////////////

#endif // __PREVIEW_MGR_H__
