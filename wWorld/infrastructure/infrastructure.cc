

// main.cc
//

#include "bit.h"
#include "exception.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	byte x("000---0-0"), y("00000+000");

	try
	{
		cout <<x <<endl;
		cout <<y <<endl;
		cout <<x+y <<endl;
		cout <<x-y <<endl;
		cout <<x*y <<endl;
		cout <<x/y <<endl;
	}
	catch (exception &e)
	{
		cout <<e.why() <<endl;
	}

	return 0;
}
