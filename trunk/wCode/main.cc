

// main.cc
// 

#include "wCppExt.h"
using namespace std;

int main(/*int argc, char *argv[]*/)
{
	auto res = w::traverseInBreadth("d:\\foo\\", 1, 3);

	res;













	//async(launch::async, 
	//[]() -> void
	//{
	//	w::SyncPipe spServer("1234");
	//	while (true)
	//	{
	//		unsigned char buf[1024] = {};
	//		unsigned readSize = spServer.read(buf, sizeof(buf));

	//		cout <<"read: " <<readSize <<" : " <<buf <<endl;
	//	}
	//});

	//int i;
	//cin >>i;

	//w::SyncPipe spClient("1234", true);	
	//while (true)
	//{
	//	unsigned char buf[10] = {"234jkl"};
	//	unsigned writeSize = spClient.write(buf, sizeof(buf));

	//	cout <<"write: " <<writeSize <<endl;
	//	this_thread::sleep_for(chrono::seconds(1));
	//}

	return 0;
}