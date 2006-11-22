#include "mp_path.h"

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]

mpPath::mpPath() : dir(""), created(false), separator('\\')
{
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]

mpPath::~mpPath()
{
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]

bool mpPath::Init( HINSTANCE hInst )
{
	char buffer[MAX_PATH] = "";
	char mdir[MAX_PATH] = "";

	GetModuleFileName( hInst, buffer, MAX_PATH );

	for( int i=(int)strlen(buffer)-1; i>0; --i )
	{
		if( buffer[i] == '\\' || buffer[i] == '/' )
		{
			strncpy( mdir, buffer, i );
			mdir[i] = '\0';
			dir = mdir;
			separator = buffer[i];

			return( created = true );
		}
	}

	return( false );
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]

char * mpPath::GetFullPath( char * file )
{
	if( !created ) return( file );
	static char temp[MAX_PATH] = "";

	wsprintf( temp, "%s%c%s", dir.c_str(), separator, file );

	return( temp );
}

//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::]