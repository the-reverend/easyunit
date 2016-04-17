
#include "CustomizedRunner.h"
#include "stringconvert.h"

CustomizedRunner::CustomizedRunner( char* testCaseName )
		: testCaseName_( testCaseName )
{

}


void CustomizedRunner::run( TestCase *testCase, int size )
{
	for ( int i = 0; i < size; i++ )
	{
		if ( ToString( testCase->getName() ) == ToString( testCaseName_ ) )
		{
			testCase->run();
		}
		testCase = testCase->getNext();
	}
}

