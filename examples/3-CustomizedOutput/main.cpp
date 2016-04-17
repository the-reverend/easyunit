/// @file main.cpp

#include "testharness.h"
#include "XmlReportPrinter.h"
using namespace easyunit;

int main()
{
	XmlReportPrinter *cp = new XmlReportPrinter( "Customized Output" );
	TestRegistry::runAndPrint( cp );
	delete cp;
}