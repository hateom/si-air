#ifndef __MP_PATH_H__
#define __MP_PATH_H__

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]

#include <windows.h>
#include <iostream>

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]

/*!
	Object stores current path.
*/
class mpPath
{
public:
	mpPath();
	virtual ~mpPath();

	bool Init( HINSTANCE hInst );
	char * GetFullPath( char * file );

	static mpPath * Single()
	{
		static mpPath singleton;
		return( &singleton );
	}

private:
	std::string dir;
	bool created;
	char separator;
};

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]

#define GETPATH( NFILE ) mpPath::Single()->GetFullPath( NFILE )

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]

#endif // __MP_PATH_H__
