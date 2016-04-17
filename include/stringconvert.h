#pragma once

#include <string>

namespace easyunit
{

// Those functions are provided to ease the conversion between
// primary datatypes and string. Feel free to extend this list
// to support your own datatype.
	std::string ToString( bool value );
	std::string ToString( const char *value );
	std::string ToString( long value );
	std::string ToString( int value );
	std::string ToString( __int64 value );
	std::string ToString( unsigned int value );
	std::string ToString( unsigned long value );
	std::string ToString( double value );
	std::string ToString( const std::string& other );

} // EasyUnit ns

