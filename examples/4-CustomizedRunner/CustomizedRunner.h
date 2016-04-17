#ifndef CUSTOM_RUNNER_H
#define CUSTOM_RUNNER_H

#include "testrunner.h"
#include "testcase.h"

using namespace easyunit;

class CustomizedRunner : public TestRunner
{

public:
	CustomizedRunner( char* testCaseName );
	void run( TestCase *testCase, int size );

private:
	char* testCaseName_;

};


#endif