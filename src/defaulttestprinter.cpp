/*
EasyUnit : Simple C++ Unit testing framework
Copyright (C) 2004 Barthelemy Dagenais

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

Barthelemy Dagenais
barthelemy@prologique.com
*/

#include "StdAfx.h"
#include "defaulttestprinter.h"

#include "testpartresult.h"

#include <stdio.h>
#include <windows.h>

using namespace easyunit;

DefaultTestPrinter::DefaultTestPrinter( const char* const testGroupName )
		: testsTotal_( 0 )
		, failuresTotal_( 0 )
		, testFailuresTotal_( 0 )
		, showSuccessDetail_( false )
		, level_( normal )
		, output_( stdout )
		, testGroupName_( testGroupName )
{
}

DefaultTestPrinter::~DefaultTestPrinter()
{
}

void DefaultTestPrinter::print( const TestResult *testResult )
{
	int failures;
	int successes;
	int errors;
	std::string state;
	std::string name;
	TestCase *testCase = testResult->getTestCases();
	int size = testResult->getTestCaseCount();

	printHeader( testResult );

	if ( testResult->getTestCaseRanCount() == 0 )
	{
		fprintf( output_, "No test ran\n" );
	}

	for ( int i = 0;i < size;i++ )
	{
		if ( testCase->ran() )
		{
			name = testCase->getName();
			failures = testCase->getFailuresCount();
			successes = testCase->getSuccessesCount();
			errors = testCase->getErrorsCount();

			if ( failures > 0 || errors > 0 )
			{
				state = "FAILED";
			}
			else
			{
				state = "PASSED";
			}

			fprintf( output_, "Test case \"%s\" %s with %d error(s), %d failure(s) and %d success(es):\n", name.c_str(), state.c_str(), errors, failures, successes );

			printTests( testCase );

			fprintf( output_, "\n" );
		}

		testCase = testCase->getNext();
	}
}

void DefaultTestPrinter::setHeaderLevel( headerLevel level )
{
	level_ = level;
}

void DefaultTestPrinter::showSuccessDetail( bool show )
{
	showSuccessDetail_ = show;
}

void DefaultTestPrinter::setOutput( FILE *output )
{
	output_ = output;
}

void DefaultTestPrinter::printHeader( const TestResult *testResult )
{
	SYSTEMTIME st;
	::GetLocalTime( &st );

	fprintf( output_ , "-- %s Results for %04d-%02d-%02d, %02d:%02d:%02d --\n\n", testGroupName_.c_str(), st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond );

	if ( level_ != off )
	{
		fprintf( output_ , "SUMMARY\n\n" );
		fprintf( output_ , "Test summary: " );

		if ( testResult->getErrors() > 0 || testResult->getFailures() > 0 )
		{
			fprintf( output_ , "FAIL\n" );
		}
		else
		{
			fprintf( output_ , "SUCCESS\n" );
		}

		if ( level_ == normal )
		{
			printNormalHeader( testResult );
		}
		else
		{
			printCompleteHeader( testResult );
		}
	}

	fprintf( output_, "DETAILS\n\n" );
}

void DefaultTestPrinter::printCompleteHeader( const TestResult *testResult )
{
	fprintf( output_, "Number of test cases: %d\n", testResult->getTestCaseCount() );
	fprintf( output_, "Number of test cases ran: %d\n", testResult->getTestCaseRanCount() );
	fprintf( output_, "Test cases that passed: %d\n", testResult->getSuccesses() );
	fprintf( output_, "Test cases with errors: %d\n", testResult->getErrors() );
	fprintf( output_, "Test cases that failed: %d\n", testResult->getFailures() );
	fprintf( output_, "Number of tests ran: %d\n", testResult->getTestRanCount() );
	fprintf( output_, "Tests that passed: %d\n", testResult->getTotalSuccesses() );
	fprintf( output_, "Tests with errors: %d\n", testResult->getTotalErrors() );
	fprintf( output_, "Tests that failed: %d\n", testResult->getTotalFailures() );
	fprintf( output_, "\n" );
}

void DefaultTestPrinter::printNormalHeader( const TestResult *testResult )
{
	fprintf( output_, "Number of test cases ran: %d\n", testResult->getTestCaseRanCount() );
	fprintf( output_, "Test cases that passed: %d\n", testResult->getSuccesses() );
	fprintf( output_, "Test cases with errors: %d\n", testResult->getErrors() );
	fprintf( output_, "Test cases that failed: %d\n", testResult->getFailures() );
	fprintf( output_, "\n" );
}

void DefaultTestPrinter::printTests( TestCase *testCase )
{
	char *indent = " ";
	Test *test = testCase->getTests();
	int size = testCase->getTestsCount();
	std::string state;

	for ( int i = 0;i < size;i++ )
	{
		if ( test->getFailuresCount() > 0 || test->getErrorsCount() > 0 )
		{
			state = "FAILED :";
		}
		else
		{
			state = "passed :";
		}

		fprintf( output_, "%s %s \"%s\"\n", indent, state.c_str(), test->getTestName().c_str() );
		printResults( test );
		test = test->getNext();
	}
}

void DefaultTestPrinter::printResults( Test *test )
{
	char *indent = "    ";
	TestPartResult *testPR = test->getTestPartResult();
	int size = test->getFailuresCount() + test->getSuccessesCount() + test->getErrorsCount();
	int type;

	for ( int i = 0;i < size;i++ )
	{
		type = testPR->getType();

		if ( type == failure )
		{
			fprintf( output_, "%s%s%s%s%s%ld%s%s\n",
			         indent,
			         "Failure: \"",
			         testPR->getMessage().c_str(),
			         "\" " ,
			         "line ",
			         testPR->getLineNumber(),
			         " in ",
			         testPR->getFileName().c_str() );
		}
		else if ( type == error )
		{
			fprintf( output_, "%s%s%s%s%s%s\n",
			         indent,
			         "Error in ",
			         test->getTestName().c_str(),
			         ": \"",
			         testPR->getMessage().c_str(),
			         "\"" );
		}
		else if ( type == success && showSuccessDetail_ )
		{
			fprintf( output_, "%s%s%s%s%s%ld%s%s\n",
			         indent,
			         "Success: \"",
			         testPR->getMessage().c_str(),
			         "\" " ,
			         "line ",
			         testPR->getLineNumber(),
			         " in ",
			         testPR->getFileName().c_str() );
		}
		testPR = testPR->getNext();
	}
}

