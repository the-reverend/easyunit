#include "StdAfx.h"

#include "stringconvert.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace easyunit;

static const int DEFAULT_SIZE = 32;

std::string easyunit::ToString( bool value )
{
	char buffer [sizeof( "false" ) + 1];
	::sprintf_s( buffer, "%s", sizeof( "false" ) + 1, value ? "true" : "false" );
	return std::string( buffer );
}

std::string easyunit::ToString( const char *value )
{
	return std::string( value );
}

std::string easyunit::ToString( long value )
{
	char buffer [DEFAULT_SIZE];
	::sprintf_s( buffer, DEFAULT_SIZE, "%ld", value );

	return std::string( buffer );
}

std::string easyunit::ToString( int value )
{
	char buffer [DEFAULT_SIZE];
	::sprintf_s( buffer, DEFAULT_SIZE, "%d", value );

	return std::string( buffer );
}

std::string easyunit::ToString( __int64 value )
{
	char buffer [DEFAULT_SIZE];
	::sprintf_s( buffer, DEFAULT_SIZE, "%I64d", value );

	return std::string( buffer );
}

std::string easyunit::ToString( unsigned int value )
{
	char buffer [DEFAULT_SIZE];
	::sprintf_s( buffer, DEFAULT_SIZE, "%d", value );

	return std::string( buffer );
}

std::string easyunit::ToString( unsigned long value )
{
	char buffer [DEFAULT_SIZE];
	::sprintf_s( buffer, DEFAULT_SIZE, "%d", value );

	return std::string( buffer );
}

std::string easyunit::ToString( double value )
{
	char buffer [DEFAULT_SIZE];
	::sprintf_s( buffer, DEFAULT_SIZE, "%lf", value );

	return std::string( buffer );
}

std::string easyunit::ToString( const std::string& value )
{
	return std::string( value );
}



