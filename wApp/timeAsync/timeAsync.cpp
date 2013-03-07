// timeAsync.cpp : Defines the entry point for the console application.
//

#include <Winsock2.h>
#include <process.h>
#include <iostream>
#include <string>
#include <thread>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iterator>
#include <utility>
#include "wCppExt.h"
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

static const unsigned sc_invalidYear = 1900,
					  sc_timeOut = 5 * 1000;		// 5s.

string hostnameToIp(const string &hostname)
{
	ostringstream oss;

	if (HOSTENT *host_entry = gethostbyname(hostname.c_str()))
	{
		oss <<static_cast<int>(host_entry->h_addr_list[0][0] & 0xff) <<'.' <<static_cast<int>(host_entry->h_addr_list[0][1] & 0xff) <<'.'
			<<static_cast<int>(host_entry->h_addr_list[0][2] & 0xff) <<'.' <<static_cast<int>(host_entry->h_addr_list[0][3] & 0xff);
	}

	return oss.str();
}

SYSTEMTIME asyncTimeFromIp(const string &timeServerIp)
{
	SYSTEMTIME st = {};
	st.wYear = sc_invalidYear;
	st.wMonth = 1;
	st.wDay = 1;

	// Construct socket address.
	sockaddr_in sa = {};
	sa.sin_family = AF_INET;
	sa.sin_port = htons(IPPORT_TIMESERVER);
	sa.sin_addr.S_un.S_addr = inet_addr(timeServerIp.c_str());

	// Send request to time server.
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock != INVALID_SOCKET)
	{
		if (connect(sock, reinterpret_cast<SOCKADDR *>(&sa), sizeof(sa)) == 0)
		{
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
		}
		closesocket(sock);
	}

	return st;
}

SYSTEMTIME getTimeFromInternet(vector<string> serversHost)
{
	SYSTEMTIME res = {};

	while (!serversHost.empty())
	{
		// Select a time server host and each server only connect once.
		unsigned r = abs(rand()) % serversHost.size();
		vector<string>::iterator it = serversHost.begin();
		advance(it, r);
		string host = *it;
		serversHost.erase(it);

		// Get system time from internet.
		string ip;
		SYSTEMTIME st = {};
		typedef tuple<string, string &, SYSTEMTIME &> Param;
		Param p(host, ip, st);
		HANDLE h = reinterpret_cast<HANDLE>(_beginthread([](void *param)
					{
						if (param != nullptr)
						{
							Param p = *reinterpret_cast<Param *>(param);
							string host = get<0>(p);			// In.
							string &ip = get<1>(p);				// Out.
							SYSTEMTIME &st = get<2>(p);			// Out.
cout <<"trying: " <<host;
							ip = hostnameToIp(host);
cout <<". ip is " <<ip;
							st = asyncTimeFromIp(ip);
cout <<". st.year: " <<st.wYear <<"," <<" hour: " <<st.wHour + 8;	// To east 8th area.
						}
					}, 0, &p));

		DWORD w = WaitForSingleObject(h, sc_timeOut);
		if (w == WAIT_OBJECT_0)
		{
			if (st.wYear != sc_invalidYear)
			{
cout <<". ok." <<endl;
				res = st;
				break;
			}
			else
			{
cout <<". fail." <<endl;
			}
		}
		else if (w == WAIT_TIMEOUT)
		{
cout <<". timeout." <<endl;
			TerminateThread(h, -1);
		}
		else
		{}
	}//while (!serversHost

	return res;
}

//int main()
//{
//	WSADATA WSAData = {};
//	WSAStartup(MAKEWORD(2,0), &WSAData);
//
//	// Available time server.
//	vector<string> timeServersHost;
//	//timeServersHost.push_back("ntp.sjtu.edu.cn");	// 上海交通大学.
//	//timeServersHost.push_back("s1a.time.edu.cn");	// 北京邮电大学.
//	//timeServersHost.push_back("s1b.time.edu.cn");	// 清华大学.
//	//timeServersHost.push_back("s1c.time.edu.cn");	// 北京大学.
//	//timeServersHost.push_back("s1d.time.edu.cn");	// 东南大学.
//	//timeServersHost.push_back("s1e.time.edu.cn");	// 清华大学.
//	//timeServersHost.push_back("s2a.time.edu.cn");	// 清华大学.
//	//timeServersHost.push_back("s2b.time.edu.cn");	// 清华大学.
//	//timeServersHost.push_back("s2c.time.edu.cn");	// 北京邮电大学.
//	//timeServersHost.push_back("s2d.time.edu.cn");	// 西南地区网络中心.
//	//timeServersHost.push_back("s2e.time.edu.cn");	// 西北地区网络中心.
//	//timeServersHost.push_back("s2f.time.edu.cn");	// 东北地区网络中心.
//	//timeServersHost.push_back("s2g.time.edu.cn");	// 华东南地区网络中心.
//	//timeServersHost.push_back("s2h.time.edu.cn");	// 四川大学网络管理中心.
//	//timeServersHost.push_back("s2j.time.edu.cn");	// 大连理工大学网络中心.
//	//timeServersHost.push_back("s2k.time.edu.cn");	// CERNET桂林主节点.
//	//timeServersHost.push_back("s2m.time.edu.cn");	// 北京大学.
//
//	timeServersHost.push_back("www.time.ac.cn");	// 国家授时中心.
//	timeServersHost.push_back("time-a.nist.gov");	// NIST, Gaithersburg, Maryland .
//	timeServersHost.push_back("time-b.nist.gov");	// NIST, Gaithersburg, Maryland .
//	timeServersHost.push_back("time-a.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
//	timeServersHost.push_back("time-b.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
//	timeServersHost.push_back("time-c.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
//	//timeServersHost.push_back("utcnist.colorado.edu");	// University of Colorado, Boulder .
//	timeServersHost.push_back("time.nist.gov");	// NCAR, Boulder, Colorado .
//	//timeServersHost.push_back("time-nw.nist.gov");	// Microsoft, Redmond, Washington .
//	timeServersHost.push_back("nist1.symmetricom.com");	// Symmetricom, San Jose, California .
//	//timeServersHost.push_back("nist1-dc.glassey.com");	// Abovenet, Virginia .
//	//timeServersHost.push_back("nist1-ny.glassey.com");	// Abovenet, New York City .
//	timeServersHost.push_back("nist1-sj.glassey.com");	// Abovenet, San Jose, California .
//	timeServersHost.push_back("nist1.aol-ca.truetime.com");	// TrueTime, AOL facility, Sunnyvale, California .
//	//timeServersHost.push_back("nist1.aol-va.truetime.com");	// TrueTime, AOL facility, Virginia.
//
//	for (int i = 0; i < 100; ++i)
//	{
//		SYSTEMTIME st = getTimeFromInternet(timeServersHost);
//		if (st.wYear != sc_invalidYear)
//		{
//			SetSystemTime(&st);
//			break;
//		}
//	}
//
//	WSACleanup();
//	return 0;
// }

// Server testing.
int main()
{
	WSADATA WSAData = {};
	WSAStartup(MAKEWORD(2,0), &WSAData);

	// Available time server.
	vector<string> timeServersHost;
	timeServersHost.push_back("ntp.sjtu.edu.cn");	// 上海交通大学.
	timeServersHost.push_back("s1a.time.edu.cn");	// 北京邮电大学.
	timeServersHost.push_back("s1b.time.edu.cn");	// 清华大学.
	timeServersHost.push_back("s1c.time.edu.cn");	// 北京大学.
	timeServersHost.push_back("s1d.time.edu.cn");	// 东南大学.
	timeServersHost.push_back("s1e.time.edu.cn");	// 清华大学.
	timeServersHost.push_back("s2a.time.edu.cn");	// 清华大学.
	timeServersHost.push_back("s2b.time.edu.cn");	// 清华大学.
	timeServersHost.push_back("s2c.time.edu.cn");	// 北京邮电大学.
	timeServersHost.push_back("s2d.time.edu.cn");	// 西南地区网络中心.
	timeServersHost.push_back("s2e.time.edu.cn");	// 西北地区网络中心.
	timeServersHost.push_back("s2f.time.edu.cn");	// 东北地区网络中心.
	timeServersHost.push_back("s2g.time.edu.cn");	// 华东南地区网络中心.
	timeServersHost.push_back("s2h.time.edu.cn");	// 四川大学网络管理中心.
	timeServersHost.push_back("s2j.time.edu.cn");	// 大连理工大学网络中心.
	timeServersHost.push_back("s2k.time.edu.cn");	// CERNET桂林主节点.
	timeServersHost.push_back("s2m.time.edu.cn");	// 北京大学.

	timeServersHost.push_back("www.time.ac.cn");	// 国家授时中心.
	timeServersHost.push_back("time-a.nist.gov");	// NIST, Gaithersburg, Maryland .
	timeServersHost.push_back("time-b.nist.gov");	// NIST, Gaithersburg, Maryland .
	timeServersHost.push_back("time-a.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	timeServersHost.push_back("time-b.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	timeServersHost.push_back("time-c.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	timeServersHost.push_back("utcnist.colorado.edu");	// University of Colorado, Boulder .
	timeServersHost.push_back("time.nist.gov");	// NCAR, Boulder, Colorado .
	timeServersHost.push_back("time-nw.nist.gov");	// Microsoft, Redmond, Washington .
	timeServersHost.push_back("nist1.symmetricom.com");	// Symmetricom, San Jose, California .
	timeServersHost.push_back("nist1-dc.glassey.com");	// Abovenet, Virginia .
	timeServersHost.push_back("nist1-ny.glassey.com");	// Abovenet, New York City .
	timeServersHost.push_back("nist1-sj.glassey.com");	// Abovenet, San Jose, California .
	timeServersHost.push_back("nist1.aol-ca.truetime.com");	// TrueTime, AOL facility, Sunnyvale, California .
	timeServersHost.push_back("nist1.aol-va.truetime.com");	// TrueTime, AOL facility, Virginia.

	// Time service testing.
	unordered_map<string, unsigned> hostCnt;
	unordered_map<string, string> hostIp;
	
	for (int i = 0; i < 33; ++i)
	{
		cout <<"---------------------------------   " <<i + 1 <<"-th   --------------------------------" <<endl;

		for (auto const &j : timeServersHost)
		{
			hostIp[j] = hostnameToIp(j);
			hostCnt[j] += !hostIp[j].empty() ? 1 : 0;

			cout <<setw(30) <<j <<" : " <<setw(16) <<hostIp[j] <<" : " <<setw(3) <<hostCnt[j];
			SYSTEMTIME st = {};
			typedef pair<string, SYSTEMTIME &> Param;
			Param param(hostIp[j], st);
			HANDLE h = reinterpret_cast<HANDLE>(_beginthread([](void *param)
						{
							if (param != nullptr)
							{
								Param p = *reinterpret_cast<Param *>(param);
								p.second = asyncTimeFromIp(p.first);
							}
						}, 0, &param));
			switch (WaitForSingleObject(h, sc_timeOut))
			{
			case WAIT_OBJECT_0:
				if (st.wYear != sc_invalidYear)
				{
					cout <<" succ : hour is " <<setw(2) <<st.wHour+8 <<".";	// To east the 8th area.
				}
				else
				{
					cout <<" fail.";
				}
				cout <<endl;
				break;
			case WAIT_TIMEOUT:
				cout <<" time out." <<endl;
				break;
			default:
				cout <<" thread fail." <<endl;
				break;
			}
		}
	}

	WSACleanup();
	return 0;
}