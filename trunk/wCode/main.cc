

// main.cc
// 

#include "wCppExt.h"
using namespace std;
using namespace w;

int main(/*int argc, char *argv[]*/)
{
	vector<pair<string, string>> v;
	v.push_back(make_pair("4444", "4"));
	v.push_back(make_pair("444.4", "5"));
	v.push_back(make_pair("4444", "0.45"));
	v.push_back(make_pair("444.4", "444.4")),
	v.push_back(make_pair("0.1234", "0.1234")),
	v.push_back(make_pair("0.1234", "0.12345"));

	v.push_back(make_pair("-4444", "4"));
	v.push_back(make_pair("-4444", "-0.45"));
	v.push_back(make_pair("-444.4", "+444.4")),
	v.push_back(make_pair("+0.1234", "0.1234")),
	v.push_back(make_pair("+0.1234", "+0.12345"));

	for (auto i : v)
	{
		cout <<i.first <<" : " <<i.second <<" <=> " <<mul(i.first, i.second) <<endl;
	}
	cout <<endl;
	for (auto i : v)
	{
		cout <<i.first <<" : " <<i.second <<" <=> " <<div(i.first, i.second) <<endl;
	}

	return 0;
}