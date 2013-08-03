

// main.cc
// 

#include "wCppExt.h"
using namespace std;
using namespace w;

int main(/*int argc, char *argv[]*/)
{
	//auto s = getServiceInfoByPid(404);
	//for (const auto &i : s)
	//{
	//	auto d = getDependentServicesInfo(i.name);

	//	cout <<i.name <<" : ";
	//	for (const auto &j : d)
	//	{
	//		cout <<j.name <<"\t";
	//	}
	//	cout <<endl;
	//}
	string svcName = getServiceNameFromTid(2380);

	return 0;
}
