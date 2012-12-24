// changeIpAndDns.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "../wCode/wSysUtil.h"
#include "../wCode/wStrUtil.h"
using namespace std;

void changeIpAndDns(const wstring &name, const wstring &ip, const wstring &mask,
					const wstring &gateway, const wstring &dns)
{
	wstring changeIpParam = L"/C netsh interface ip set address name=\"" + name + L"\" source=static address=" + ip + L" mask=" + mask + L" gateway=" + gateway,
			changeDnsParam = L"/C netsh interface ip set dns name=\"" + name + L"\" source=static address=" + dns;

	// Change ip.
	w::runAndWait(L"cmd.exe", changeIpParam, INFINITE, false);

	// Wait the ipchanging success.
	Sleep(2000);

	// Change dns.
	w::runAndWait(L"cmd.exe", changeDnsParam, INFINITE, false);
}

/*
 *
 *	Param:
 *		1: Address of the connect device. (Local connection)
 *		2: Ip address. (192.168.1.1)
 *		3: Mask. (255.255.255.0)
 *		4: Gateway. (192.168.1.254)
 *		5: Dns. (8.8.8.8)
 */
int wmain(int argc, wchar_t *argv[])
{
	if (argc == 1 + 5)
	{
		changeIpAndDns(argv[1], argv[2], argv[3], argv[4], argv[5]);
	}

	return 0;
}

