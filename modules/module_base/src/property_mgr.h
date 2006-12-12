#ifndef __PROPERTY_MGR_H__
#define __PROPERTY_MGR_H__

#include <string>
#include <map>

#define propertyMgr PropertyMgr::Single()

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

	static PropertyMgr * Single()
	{
		static PropertyMgr mgr;
		return( &mgr );
	}

private:
	std::map<std::string,void *> data;
};

#endif // __PROPERTY_MGR_H__
