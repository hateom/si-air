#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <string>

#ifdef _DEBUG
#define MB_ASSERT( MSG, EXP ) if( !(EXP) ) { throw mbException( MSG, #EXP, __FILE__, __LINE__ ); }
#else
#define MB_ASSERT( MSG, EXP )
#endif

class __declspec(dllexport) mbException
{
public:
	mbException( const char * ms, const char * ex, const char * fil, int lin ) : 
		line( lin ), msg( ms ), exp( ex ), file( fil ) {}
	~mbException() {}

	const char * show()
	{
		static char buffer[256] = "";
		sprintf( buffer, "%s at %d> `%s` : %s", file.c_str(), line, exp.c_str(), msg.c_str() );
		return( buffer );
	}

private:
	int line;
	std::string msg, exp, file;
};

#endif // __EXCEPTIONS_H__
