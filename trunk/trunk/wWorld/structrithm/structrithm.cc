
// structrithm.cc
//

#include "structure/sequence/block.h"
#include "structure/associate/list.h"
#include "structure/string.h"
#include <iostream>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;

int main()
{
	string s1, s2("1234"), s3(4312), s4('0');
	cout <<s1 <<endl
		 <<s2 <<endl
		 <<s3 <<endl
		 <<s4 <<endl;
	cout <<"--------------" <<endl;

	string s0;
	s0 = s1 + s2;
	cout <<s0 <<endl;

	s0 = "+++" + s2;
	cout <<s0 <<endl;
	
	s0 += s3 + "---";
	cout <<s0 <<endl;
	
	//cout <<s0.reverse() <<endl;

	cout <<"-------------" <<endl;
	cout <<s0.find('-') <<endl;
	cout <<s0.find("234") <<endl;
	cout <<s0.find("20034") <<endl;

	cout <<"-------------" <<endl;
	cout <<s0.erase(5, 7) <<endl;
	cout <<s0.trimLeft("++") <<endl;
	cout <<s0.trimRight("--") <<endl;
	cout <<s0.replace("2", "**") <<endl;

	cout <<"-------------" <<endl;
	cout <<s0.subStr(1, 4) <<endl;

	std::vector<string> v = s0.split("*");
	std::for_each(v.begin(), v.end(), 
			 [](const string &str) -> void { cout <<str <<endl; });

	return 0;
}
