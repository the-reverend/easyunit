
#pragma once

#include <string>
#include "SimpleXMLWriter.h"
#include "testprinter.h"
#include "testcase.h"
#include "test.h"
#include "testresult.h"
#include <stdio.h>

namespace easyunit
{

	/**
	 * Complete header level means that a header will be printed
	 * before the test details with all information available in
	 * the test result.
	 *
	 * Normal header level means that a header will be printed
	 * before the test details with the most useful information
	 * available in the test result.
	 *
	 * Off header level means that no header will be printed
	 * before the test details.
	 *
	 * Whatever the level, there will always be a clear indication
	 * telling if there was a failure/error or not at the global
	 * level.
	 */


	/**
	 * This is a report printer to
	 */
	class XmlReportPrinter : public TestPrinter
	{
	public:

		/**
		 * Default constructor that sets the name of
		 * the test group
		 */
		XmlReportPrinter( const char* const testGroupName = "EASYUNIT" );

		/**
		 * Empty destructor.
		 */
		virtual ~XmlReportPrinter();
		/**
		 * Prints a header depending of the header level and
		 * details about each test to the output_.
		 *
		 * @param testResult Results of all tests that were ran.
		 */
		virtual void print( const TestResult *testResult );

		/**
		 * Set whether or not the printer should display the details
		 * of test that succeeded.
		 *
		 * @param show Set to true to display details about success
		 */
		void showSuccessDetail( bool show );

		/**
		 * Set the output to which the printer will print results.
		 *
		 * @param output Output used to print the results
		 */
		void setOutput( FILE *output );

	protected:
		virtual void printHeader( const TestResult *testResult );
		virtual void printTests( TestCase *testCase, SimpleXMLWriter::Element& element );
		virtual void printResults( Test *test, SimpleXMLWriter::Element& element );
		FILE *output_;
		SimpleXMLWriter::Document doc_;
		SimpleXMLWriter::Element header_;
		SimpleXMLWriter::Element results_;
		std::string testGroupName_;
	};

} // EasyUnit ns

