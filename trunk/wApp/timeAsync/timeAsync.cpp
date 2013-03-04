// timeAsync.cpp : Defines the entry point for the console application.
//

#include <Winsock2.h>
#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <process.h>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

SYSTEMTIME asyncFromInternet(const string &timeServerIp)
{
	SYSTEMTIME st = {};
	st.wYear = 1900;
	st.wMonth = 1;
	st.wDay = 1;

	// Construct socket address.
	sockaddr_in sa = {};
	sa.sin_family = AF_INET;
	sa.sin_port = htons(IPPORT_TIMESERVER);
	sa.sin_addr.S_un.S_addr = inet_addr(timeServerIp.c_str());

	// Send request to time server.
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(sock, reinterpret_cast<SOCKADDR *>(&sa), sizeof(sa)); 

	// Receive internet time.
	// The value returned by internet is the second elapsed since 1900/1/1 0:0:0.
	unsigned long elapsedSecond = 0;
	recv(sock, reinterpret_cast<char *>(&elapsedSecond), sizeof(elapsedSecond), MSG_WAITALL);
	elapsedSecond = ntohl(elapsedSecond);

	// Convert to system time.
	// 'SYSTEMTIME' goes from 1900/1/1 0:0:0, but 'FILETIME' goes from 1601/1/1 0:0:0.
	// 'SYSTEMTIME' in second, 'FILETIME' in 100 nanosecond.
	FILETIME ft = {};
	SystemTimeToFileTime(&st, &ft);
	LARGE_INTEGER &li = reinterpret_cast<LARGE_INTEGER &>(ft);
	li.QuadPart += elapsedSecond * static_cast<long long>(1000 * 1000 * 10);
	FileTimeToSystemTime(&ft, &st);

	closesocket(sock);
	return st;
}

string hostnameToIp(const string &hostname)
{
	ostringstream oss;

	if (HOSTENT *host_entry = gethostbyname(hostname.c_str()))
	{
		oss <<(host_entry->h_addr_list[0][0] & 0x00ff) <<'.' <<(host_entry->h_addr_list[0][1] & 0x00ff) <<'.'
			<<(host_entry->h_addr_list[0][2] & 0x00ff) <<'.' <<(host_entry->h_addr_list[0][3] & 0x00ff);
	}

	return oss.str();
}

string getValidTimeServerIp(vector<string> timeServersIp)
{
	string res;

	while (!timeServersIp.empty())
	{
		unsigned r = abs(rand()) % timeServersIp.size();
		vector<string>::iterator it = timeServersIp.begin();
		advance(it, r);
		string host = *it;
		timeServersIp.erase(it);
cout <<"trying: " <<host;
		string ip;
		pair<string, string &> p(host, ip);
		HANDLE h = reinterpret_cast<HANDLE>(_beginthread([](void *param)
		{
			if (param != nullptr)
			{
				// '.first' is return ip address, '.second' is host name.
				pair<string, string &> *p = reinterpret_cast<pair<string, string &> *>(param);
				p->second = hostnameToIp(p->first);
			}
		}, 0, &p));

		DWORD w = WaitForSingleObject(h, 5 * 1000);
		if (w == WAIT_OBJECT_0 && !ip.empty())
		{
cout <<" ok." <<endl;
			res = ip;
			break;
		}
		else if (WAIT_TIMEOUT)
		{
cout <<" fail." <<endl;
			TerminateThread(h, -1);
		}
		else
		{}
	}

	return res;
}

int main()
{
	WSADATA WSAData = {};
	::WSAStartup(MAKEWORD(2,0), &WSAData);

	vector<string> v;
	v.push_back("ntp.sjtu.edu.cn");	// 上海交通大学.
	v.push_back("s1a.time.edu.cn");	// 北京邮电大学.
	v.push_back("s1b.time.edu.cn");	// 清华大学.
	v.push_back("s1c.time.edu.cn");	// 北京大学.
	v.push_back("s1d.time.edu.cn");	// 东南大学.
	v.push_back("s1e.time.edu.cn");	// 清华大学.
	v.push_back("s2a.time.edu.cn");	// 清华大学.
	v.push_back("s2b.time.edu.cn");	// 清华大学.
	v.push_back("s2c.time.edu.cn");	// 北京邮电大学.
	v.push_back("s2d.time.edu.cn");	// 西南地区网络中心.
	v.push_back("s2e.time.edu.cn");	// 西北地区网络中心.
	v.push_back("s2f.time.edu.cn");	// 东北地区网络中心.
	v.push_back("s2g.time.edu.cn");	// 华东南地区网络中心.
	v.push_back("s2h.time.edu.cn");	// 四川大学网络管理中心.
	v.push_back("s2j.time.edu.cn");	// 大连理工大学网络中心.
	v.push_back("s2k.time.edu.cn");	// CERNET桂林主节点.
	v.push_back("s2m.time.edu.cn");	// 北京大学.

	v.push_back("www.time.ac.cn");	// 国家授时中心.
	v.push_back("time-a.nist.gov");	// NIST, Gaithersburg, Maryland .
	v.push_back("time-b.nist.gov");	// NIST, Gaithersburg, Maryland .
	v.push_back("time-a.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	v.push_back("time-b.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	v.push_back("time-c.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	v.push_back("utcnist.colorado.edu");	// University of Colorado, Boulder .
	v.push_back("time.nist.gov");	// NCAR, Boulder, Colorado .
	v.push_back("time-nw.nist.gov");	// Microsoft, Redmond, Washington .
	v.push_back("nist1.symmetricom.com");	// Symmetricom, San Jose, California .
	v.push_back("nist1-dc.glassey.com");	// Abovenet, Virginia .
	v.push_back("nist1-ny.glassey.com");	// Abovenet, New York City .
	v.push_back("nist1-sj.glassey.com");	// Abovenet, San Jose, California .
	v.push_back("nist1.aol-ca.truetime.com");	// TrueTime, AOL facility, Sunnyvale, California .
	v.push_back("nist1.aol-va.truetime.com");	// TrueTime, AOL facility, Virginia.

	// Server selection testing.
	for (int i = 0; i < 100; ++i)
	{
		srand(static_cast<unsigned>(time(nullptr)));

		getValidTimeServerIp(v);
	}

	// Server connection testing.
	//unordered_map<string, unsigned> m;
	//for (unsigned i = 0; i < 100; ++i)
	//{
	//	cout <<"processing: ";
	//	for (auto const &i : v)
	//	{
	//		string ip = hostnameToIp(i);
	//		if (!ip.empty())
	//		{
	//			++m[i];
	//		}

	//		cout <<'.';
	//	}
	//	cout <<endl;

	//	for (auto const &i : v)
	//	{
	//		auto it = m.find(i);
	//		int n = it == m.end() ? 0 : it->second;
	//		cout <<i <<" : " <<n <<endl;
	//	}
	//}

	//cout <<"statistics: " <<endl;
	//for (auto const &i : m)
	//{
	//	cout <<i.first <<" : " <<i.second <<endl;
	//}

	::WSACleanup();
	return 0;
 }

