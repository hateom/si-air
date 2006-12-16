#ifndef __PROPERTY_MGR_H__
#define __PROPERTY_MGR_H__

//////////////////////////////////////////////////////////////////////////

#include <string>
#include <map>

//////////////////////////////////////////////////////////////////////////

#pragma warning ( disable: 4251 )	// STL & dll

//////////////////////////////////////////////////////////////////////////

class __declspec(dllexport) PropertyMgr
{
public:
	PropertyMgr() {}
	~PropertyMgr() {}

	bool register_property( std::string name, void * value )
	{
		typedef std::pair<std::string,void*> myPair;
		data.insert( myPair( name, value ) );

		return( true );
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
