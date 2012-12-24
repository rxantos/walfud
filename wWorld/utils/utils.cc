

// utils.cc
//

#include "convert.h"
#include <iostream>
using namespace std;

int main()
{
	cout <<bToD("01110110") <<endl;
	cout <<bToH("-01110110") <<endl;
	cout <<endl;

	cout <<dToB("1234987") <<endl;
	cout <<dToH("-1234987") <<endl;
	cout <<endl;
	
	cout <<hToB("1af0") <<endl;
	cout <<hToD("-1af0") <<endl;
	cout <<endl;

	return 0;
}
