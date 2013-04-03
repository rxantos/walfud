// timeSync.cpp : Defines the entry point for the console application.
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

static const unsigned sc_timeOut = 3 * 1000;		// 3s.

bool isValidSystemTime(const SYSTEMTIME &st)
{ return 1601 <= st.wYear && st.wYear <= 30827
		 && 1 <= st.wMonth && st.wMonth <= 12
		 && 0 <= st.wDayOfWeek && st.wDayOfWeek <= 6
		 && 1 <= st.wDay && st.wDay <= 31
		 && 0 <= st.wHour && st.wHour <= 23
		 && 0 <= st.wMinute && st.wMinute <= 59
		 && 0 <= st.wSecond && st.wSecond <= 59
		 && 0 <= st.wMilliseconds && st.wMilliseconds <= 999; }

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

SYSTEMTIME syncTimeFromIp(const string &timeServerIp)
{
	SYSTEMTIME st = {};

	// Construct socket address.
	sockaddr_in sa = {};
	sa.sin_family = AF_INET;
	sa.sin_port = htons(IPPORT_TIMESERVER);
	sa.sin_addr.S_un.S_addr = inet_addr(timeServerIp.c_str());

	// Send request to time server.
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//SOCKET sock = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);		// UDP is unreliable.
	if (sock != INVALID_SOCKET)
	{
		if (connect(sock, reinterpret_cast<SOCKADDR *>(&sa), sizeof(sa)) == 0)
		{
			// Receive internet time.
			// The value returned by internet is the second elapsed since 1900/1/1 0:0:0.
			time_t elapsedSecond = 0;
			//sendto(sock, NULL, 0, 0, reinterpret_cast<sockaddr *>(&sa), sizeof(sa));
			//int addrSize = sizeof(sa);
			//recvfrom(sock, reinterpret_cast<char *>(&elapsedSecond), sizeof(elapsedSecond), 0, reinterpret_cast<sockaddr *>(&sa), &addrSize);
			recv(sock, reinterpret_cast<char *>(&elapsedSecond), sizeof(elapsedSecond), 0);
			elapsedSecond = (static_cast<time_t>(ntohl(static_cast<unsigned long>(elapsedSecond >> 32))) << 32 
							| ntohl(static_cast<unsigned long>(elapsedSecond)) - 2208988800);	// '2208988800' is the second "1900/01/01 00:00:00" - "1970/01/01 00:00:00".
																								// Time protocol return a second elapsed from 1970/01/01 00:00:00,
																								// but 'localtime' use a second goes from 1900/01/01 00:00:00. 

			if (tm *p = localtime(&elapsedSecond))
			{
				st.wYear = p->tm_year + 1900,
				st.wMonth = p->tm_mon + 1,
				st.wDay = p->tm_mday,
				st.wDayOfWeek = p->tm_wday,
					
				st.wHour = p->tm_hour,
				st.wMinute = p->tm_min,
				st.wSecond = p->tm_sec,
				st.wMilliseconds = 0;
			}//if (elapsedSecond
		}//if (connect
		closesocket(sock);
	}

	return st;
}

SYSTEMTIME getTimeFromInternet(vector<string> serversHost)
{
	SYSTEMTIME res = {};

	bool found = false;
	while (!serversHost.empty() && !found)
	{
		// Select a time server host and each server only connect once.
		unsigned r = abs(rand()) % serversHost.size();
		vector<string>::iterator it = serversHost.begin();
		advance(it, r);
		string host = *it;
		serversHost.erase(it);

		// Get system time from internet.
		typedef tuple<string *,				// In. Host.
					  string *,				// Out. Ip.
					  atomic_bool *,		// In. 'true' if caller to release memory; 'false' if callee to release memory.
					  SYSTEMTIME *			// Out. System time.
									> Param;
		Param *p = new Param;
		string *pHost = get<0>(*p) = new string(host);
		string *pIp = get<1>(*p) = new string;
		atomic_bool *pOwner = get<2>(*p) = new atomic_bool;
		SYSTEMTIME *pSt = get<3>(*p) = new SYSTEMTIME;

		*pOwner = true;					// Caller is resposible for release.

		HANDLE h = reinterpret_cast<HANDLE>(_beginthread([](void *param)
					{
						if (Param *p = reinterpret_cast<Param *>(param))
						{
							string *host = get<0>(*p);
							string *ip = get<1>(*p);
							atomic_bool *owner = get<2>(*p);
							SYSTEMTIME *st = get<3>(*p);
cout <<*host;
							*ip = hostnameToIp(*host);
cout <<"\t" <<*ip;
							*st = syncTimeFromIp(*ip);

							if (!*owner)
							{
								// Thread is resposible for release memory.
								delete host;
								delete ip;
								delete owner;
								delete st;
								delete p;
							}
						}//if (Param
					}, 0, p));

		switch (WaitForSingleObject(h, sc_timeOut))
		{
		case WAIT_OBJECT_0:
			if (isValidSystemTime(*pSt))
			{
				res = *pSt;
				found = true;
cout <<"\t" <<res.wYear <<"-" <<res.wMonth <<"-" <<res.wDay <<" " <<res.wHour <<":" <<res.wMinute <<":" <<res.wSecond <<endl;
			}
			else
			{
cout <<"\tfail." <<endl;
			}
			break;
		case WAIT_TIMEOUT:
			// Thread is pending, we don't know when it returns, 
			// so we ship the ownership to thread, and let it runs.
			*pOwner = false;
cout <<"\ttimeout." <<endl;
			break;
		default:
			break;
		}//switch
	}//while (!serversHost

	return res;
}

#ifndef TEST
int main()
{
	WSADATA WSAData = {};
	WSAStartup(MAKEWORD(2,0), &WSAData);

	// Available time server.
	vector<string> timeServersHost;
	//timeServersHost.push_back("ntp.sjtu.edu.cn");	// 上海交通大学.
	//timeServersHost.push_back("s1a.time.edu.cn");	// 北京邮电大学.
	//timeServersHost.push_back("s1b.time.edu.cn");	// 清华大学.
	//timeServersHost.push_back("s1c.time.edu.cn");	// 北京大学.
	//timeServersHost.push_back("s1d.time.edu.cn");	// 东南大学.
	//timeServersHost.push_back("s1e.time.edu.cn");	// 清华大学.
	//timeServersHost.push_back("s2a.time.edu.cn");	// 清华大学.
	//timeServersHost.push_back("s2b.time.edu.cn");	// 清华大学.
	//timeServersHost.push_back("s2c.time.edu.cn");	// 北京邮电大学.
	//timeServersHost.push_back("s2d.time.edu.cn");	// 西南地区网络中心.
	//timeServersHost.push_back("s2e.time.edu.cn");	// 西北地区网络中心.
	//timeServersHost.push_back("s2f.time.edu.cn");	// 东北地区网络中心.
	//timeServersHost.push_back("s2g.time.edu.cn");	// 华东南地区网络中心.
	//timeServersHost.push_back("s2h.time.edu.cn");	// 四川大学网络管理中心.
	//timeServersHost.push_back("s2j.time.edu.cn");	// 大连理工大学网络中心.
	//timeServersHost.push_back("s2k.time.edu.cn");	// CERNET桂林主节点.
	//timeServersHost.push_back("s2m.time.edu.cn");	// 北京大学.

	//timeServersHost.push_back("www.time.ac.cn");	// 国家授时中心.
	timeServersHost.push_back("time-a.nist.gov");	// NIST, Gaithersburg, Maryland .
	timeServersHost.push_back("time-b.nist.gov");	// NIST, Gaithersburg, Maryland .
	timeServersHost.push_back("time-a.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	timeServersHost.push_back("time-b.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	timeServersHost.push_back("time-c.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	//timeServersHost.push_back("utcnist.colorado.edu");	// University of Colorado, Boulder .
	//timeServersHost.push_back("time.nist.gov");	// NCAR, Boulder, Colorado .
	//timeServersHost.push_back("time-nw.nist.gov");	// Microsoft, Redmond, Washington .
	timeServersHost.push_back("nist1.symmetricom.com");	// Symmetricom, San Jose, California .
	//timeServersHost.push_back("nist1-dc.glassey.com");	// Abovenet, Virginia .
	//timeServersHost.push_back("nist1-ny.glassey.com");	// Abovenet, New York City .
	timeServersHost.push_back("nist1-sj.glassey.com");	// Abovenet, San Jose, California .
	timeServersHost.push_back("nist1.aol-ca.truetime.com");	// TrueTime, AOL facility, Sunnyvale, California .
	//timeServersHost.push_back("nist1.aol-va.truetime.com");	// TrueTime, AOL facility, Virginia.

	SYSTEMTIME st = getTimeFromInternet(timeServersHost);
	if (isValidSystemTime(st))
	{
		SetSystemTime(&st);
	}

	WSACleanup();
	return 0;
 }
#else
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
	
	//for (int i = 0; i < 33; ++i)
	int i = 0;
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
								p.second = syncTimeFromIp(p.first);
							}
						}, 0, &param));
			switch (WaitForSingleObject(h, sc_timeOut))
			{
			case WAIT_OBJECT_0:
				if (isValidSystemTime(st))
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
#endif // TEST