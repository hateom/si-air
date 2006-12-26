#include "mp_logger.h"
#include <cstdarg>
#include <qtextedit.h>
#include <qstring.h>

//////////////////////////////////////////////////////////////////////////

int mpLogger::output_type = OT_NONE;
QTextEdit * mpLogger::te = NULL;

mpLogger::mpLogger()
{
}

//////////////////////////////////////////////////////////////////////////

mpLogger::~mpLogger()
{
}

//////////////////////////////////////////////////////////////////////////

void mpLogger::set_output( int ot, QTextEdit * t_e )
{
	output_type = ot;

	if( ot == OT_WINDOW )
	{
		te = t_e;
	}
}

//////////////////////////////////////////////////////////////////////////

void mpLogger::log( std::string text )
{
	log( text.c_str() );
}

//////////////////////////////////////////////////////////////////////////

void mpLogger::log( const char * text, ... )
{
	va_list al;
	static char buffer[256] = "";

	va_start( al, text );
	vsprintf( buffer, text, al );
	va_end( al );

	switch( output_type )
	{
	case OT_CONSOLE:
		printf( buffer );
		break;
	case OT_WINDOW:
		if( te != NULL )
		{
			te->insert( QString(buffer) );
		}
		break;
	default:
		/// none
		break;
	}
}

//////////////////////////////////////////////////////////////////////////

