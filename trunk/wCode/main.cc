

// main.cc
// 

#include "wCppExt.h"
using namespace std;
using namespace w;

void foo(void *param)
{
	const char *p = reinterpret_cast<const char *>(param);
	cout <<p <<endl;
}

void bar(int a, int b)
{
	cout <<a <<" : " <<b <<endl;
}

class T
{
public:
	void baz()
	{
		cout <<"T::baz()." <<endl;
	}
};

int main(/*int argc, char *argv[]*/)
{
	MyConsole c;
	c.add("1", function<void (void *)>(foo), "12344321");
	c.add("2", string("notepad.exe"));
	c.add("3", bind(bar, 1, 2));

	T t;
	//c.add("4", &T::baz, &t);

	c.run();

	return 0;
}


	