#include "stack.h"
#include <string>

Stack::Stack()
		: value( 0 ), size_( 0 )
{

}

/**
 This operation is wrong! This
 is not a stack at all!
*/
void Stack::push( int val )
{
	size_++;
	value = val;
}

int Stack::pull()
{
	size_--;
	return value;
}

int Stack::top()
{
	return value;
}

int Stack::size() const
{
	return size_;
}

void Stack::throwEx()
{
	throw StackException();
}

void Stack::throwUnknownEx()
{
	throw std::string();
}

void Stack::nothrowEx()
{

}