#include "StdAfx.h"
#include "XmlReportPrinter.h"

#include "testpartresult.h"
#include <iostream>
#include <sstream>

#include <stdio.h>

using namespace easyunit;

XmlReportPrinter::XmlReportPrinter( const char* const testGroupName )
		: output_( stdout )
		, header_( "test-results" )
		, results_( "results" )
		, testGroupName_( testGroupName )
{
}

XmlReportPrinter::~XmlReportPrinter()
{
}

void XmlReportPrinter::print( const TestResult *testResult )
{
	printHeader( testResult );

	TestCase *testCase = testResult->getTestCases();
	int size = testResult->getTestCaseCount();

	SimpleXMLWriter::Element testSuite( "test-suite" );
	for ( int i = 0;i < size;i++ )
	{
		testSuite.Clear();
		testSuite.Add( SimpleXMLWriter::Attrib( "name", testCase->getName() ) );
		if ( testCase->getFailuresCount() > 0 )
		{
			testSuite.Add( SimpleXMLWriter::Attrib( "success", "False" ) );
		}
		else
		{
			testSuite.Add( SimpleXMLWriter::Attrib( "success", "True" ) );
		}
		if ( testCase->ran() )
		{
			testSuite.Add( SimpleXMLWriter::Attrib( "executed", "True" ) );
			printTests( testCase, testSuite );
		}
		else
		{
			testSuite.Add( SimpleXMLWriter::Attrib( "executed", "False" ) );
		}

		results_.Add( testSuite );
		testCase = testCase->getNext();
	}

	header_.Add( results_ );

	doc_.AddBaseElem( header_ );

	std::stringstream strm;
	strm << doc_;
	fprintf( output_ , strm.str().c_str() );
}

void XmlReportPrinter::setOutput( FILE *output )
{
	output_ = output;
}

void XmlReportPrinter::printHeader( const TestResult *testResult )
{
	doc_.AddProlog( "DOCTYPE HTML PUBLIC '-//W3C//DTD HTML 4.01 Transitional//EN'" );

	header_.Add( SimpleXMLWriter::Attrib( "name", testGroupName_ ) );
	header_.Add( SimpleXMLWriter::Attrib( "total", testResult->getTotalRunCount() ) );
	header_.Add( SimpleXMLWriter::Attrib( "failures", testResult->getTotalFailureCount() ) );
	header_.Add( SimpleXMLWriter::Attrib( "not-run", testResult->getTotalErrorCount() ) );
	header_.Add( SimpleXMLWriter::Attrib( "date", __DATE__ ) );
	header_.Add( SimpleXMLWriter::Attrib( "time", __TIME__ ) );
}

void XmlReportPrinter::printTests( TestCase *testCase, SimpleXMLWriter::Element& element )
{
	Test *test = testCase->getTests();
	int size = testCase->getTestsCount();

	SimpleXMLWriter::Element testCaseEle( "test-case" );
	for ( int i = 0;i < size;i++ )
	{
		testCaseEle.Clear();
		testCaseEle.Add( SimpleXMLWriter::Attrib( "name", test->getTestName() ) );
		if ( test->getFailuresCount() > 0 )
		{
			testCaseEle.Add( SimpleXMLWriter::Attrib( "success", "False" ) );
		}
		else
		{
			testCaseEle.Add( SimpleXMLWriter::Attrib( "success", "True" ) );
		}
		element.Add( testCaseEle );
		test = test->getNext();
	}
}

void XmlReportPrinter::printResults( Test *test, SimpleXMLWriter::Element& element )
{
	TestPartResult *testPR = test->getTestPartResult();
	int size = test->getFailuresCount() + test->getSuccessesCount() + test->getErrorsCount();

	for ( int i = 0;i < size;i++ )
	{
		switch ( testPR->getType() )
		{
			case failure:
			{
				break;
			}
			case error:
			{
				break;
			}
			case success:
			{
				break;
			}
		}

		testPR = testPR->getNext();
	}
}


