/********************************************************************
    Projekt z przedmiotu : Sztuczna Inteligencja i Sensoryka

	stworzono:	17:12:2006   16:50
	plik:    	property_mgr
	autorzy:	Tomasz Huczek, Andrzej Jasiñski
	
    cel:	    
*********************************************************************/

#ifndef __PROPERTY_MGR_H__
#define __PROPERTY_MGR_H__

//////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>
#include "status_codes.h"

//////////////////////////////////////////////////////////////////////////

#pragma warning ( disable: 4251 )	// STL & dll

//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) PropertyMgr
{
public:
	PropertyMgr() {}
	~PropertyMgr() {}

	int register_property( std::string name, void * value )
	{
		if( get_property( name ) != NULL ) return( ST_ALREADY_EXISTS );

		typedef std::pair<std::string,void*> myPair;
		data.insert( myPair( name, value ) );

		return( ST_OK );
	}

	void * get_property( std::string name )
	{
		return( data[name] );
	}

	void release() { data.clear(); }

private:
	std::map<std::string,void *> data;
};

//////////////////////////////////////////////////////////////////////////

#endif // __PROPERTY_MGR_H__
