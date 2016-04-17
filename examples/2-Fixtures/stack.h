#ifndef STACK_H
#define STACK_H

#include <exception>

class StackException : public std::exception
{
public:
	StackException() {}
	~StackException() {}
};

class Stack
{
public:
	Stack();

	void push( int val );
	int pull();
	int top();

	int size() const;

	void throwEx();
	void throwUnknownEx();
	void nothrowEx();

private:
	int value;
	int size_;
};

#endif