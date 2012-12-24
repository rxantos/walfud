// UProtector.cpp : Defines the entry point for the console application.
//

#include "wFilePermission.h"
#include "wDisk.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
	//unsigned permission = 0;
	//if (strchr(argv[2], 'r') != NULL)
	//{
	//	permission |= GENERIC_READ;
	//}
	//if (strchr(argv[2], 'w') != NULL)
	//{
	//	permission |= GENERIC_WRITE;
	//}
	//if (strchr(argv[2], 'e') != NULL)
	//{
	//	permission |= GENERIC_EXECUTE;
	//}
	//if (strchr(argv[2], 'a') != NULL)
	//{
	//	permission |= GENERIC_ALL;
	//}

	string usb = w::getRemovableDrivesName()[0];
	//cout <<w::setPermission(usb, argv[1], permission, false, false) <<endl;
	cout <<w::setPermission(usb, "song", GENERIC_READ, false, true) <<endl;

	return 0;
}