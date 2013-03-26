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

static const unsigned sc_timeOut = 2 * 1000;		// 5s.

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
	if (sock != INVALID_SOCKET)
	{
		if (connect(sock, reinterpret_cast<SOCKADDR *>(&sa), sizeof(sa)) == 0)
		{
			// Receive internet time.
			// The value returned by internet is the second elapsed since 1900/1/1 0:0:0.
			unsigned long elapsedSecond = 0;
			recv(sock, reinterpret_cast<char *>(&elapsedSecond), sizeof(elapsedSecond), MSG_WAITALL);
			elapsedSecond = ntohl(elapsedSecond);

			if (elapsedSecond != 0)
			{
				// Convert to system time.
				// 'SYSTEMTIME' goes from 1900/1/1 0:0:0, but 'FILETIME' goes from 1601/1/1 0:0:0.
				// 'SYSTEMTIME' in second, 'FILETIME' in 100 nanosecond.
				SYSTEMTIME tmp = {};
				tmp.wYear = 1900;
				tmp.wMonth = 1;
				tmp.wDay = 1;

				FILETIME ft = {};
				SystemTimeToFileTime(&tmp, &ft);
				LARGE_INTEGER &li = reinterpret_cast<LARGE_INTEGER &>(ft);
				li.QuadPart += elapsedSecond * static_cast<long long>(1000 * 1000 * 10);
				FileTimeToSystemTime(&ft, &tmp);

				if (isValidSystemTime(tmp))
				{
					st = tmp;
				}
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
		string ip;
		SYSTEMTIME st = {};
		
		//Param p(host, ip, st);

		typedef tuple<string *,				// In. Host.
					  string *,				// Out. Ip.
					  atomic_bool *,		// In. 'true' if caller to release memory; 'false' if callee to release memory.
					  SYSTEMTIME *			// Out. System time.
									> Param;
		Param *p = new Param;
		string *host = get<0>(*p) = new string(host);
		string *ip = get<1>(*p) = new string;
		atomic_bool *owner = get<2>(*p) = new atomic_bool;
		SYSTEMTIME *st = get<3>(*p) = new SYSTEMTIME;

		*owner = true;					// Caller is resposible for release.

		HANDLE h = reinterpret_cast<HANDLE>(_beginthread([](void *param)
					{
						if (Param *p = reinterpret_cast<Param *>(param))
						{
							string *host = get<0>(*p);
							string *ip = get<1>(*p);
							atomic_bool *owner = get<2>(*p);
							SYSTEMTIME *st = get<3>(*p);
cout <<"trying: " <<*host;
							*ip = hostnameToIp(*host);
cout <<". ip is " <<*ip;
							*st = syncTimeFromIp(*ip);
//cout <<". st.year: " <<*st.wYear <<"," <<" hour: " <<st.wHour + 8;	// To east 8th area.

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
			if (isValidSystemTime(st))
			{
cout <<". ok." <<endl;
				res = st;
			}
			else
			{
cout <<". fail." <<endl;
			}
		case WAIT_TIMEOUT:
			// Thread is pending, we don't know when it returns, 
			// so we ship the ownership to thread, and let it runs.
			*owner = false;
cout <<". timeout." <<endl;
			break;
		default:
			break;
		}//switch
			



	}//while (!serversHost

	return res;
}

int main()
{
	WSADATA WSAData = {};
	WSAStartup(MAKEWORD(2,0), &WSAData);

	// Available time server.
	vector<string> timeServersHost;
	//timeServersHost.push_back("ntp.sjtu.edu.cn");	// �Ϻ���ͨ��ѧ.
	//timeServersHost.push_back("s1a.time.edu.cn");	// �����ʵ��ѧ.
	//timeServersHost.push_back("s1b.time.edu.cn");	// �廪��ѧ.
	//timeServersHost.push_back("s1c.time.edu.cn");	// ������ѧ.
	//timeServersHost.push_back("s1d.time.edu.cn");	// ���ϴ�ѧ.
	//timeServersHost.push_back("s1e.time.edu.cn");	// �廪��ѧ.
	//timeServersHost.push_back("s2a.time.edu.cn");	// �廪��ѧ.
	//timeServersHost.push_back("s2b.time.edu.cn");	// �廪��ѧ.
	//timeServersHost.push_back("s2c.time.edu.cn");	// �����ʵ��ѧ.
	//timeServersHost.push_back("s2d.time.edu.cn");	// ���ϵ�����������.
	//timeServersHost.push_back("s2e.time.edu.cn");	// ����������������.
	//timeServersHost.push_back("s2f.time.edu.cn");	// ����������������.
	//timeServersHost.push_back("s2g.time.edu.cn");	// �����ϵ�����������.
	//timeServersHost.push_back("s2h.time.edu.cn");	// �Ĵ���ѧ�����������.
	//timeServersHost.push_back("s2j.time.edu.cn");	// ����������ѧ��������.
	//timeServersHost.push_back("s2k.time.edu.cn");	// CERNET�������ڵ�.
	//timeServersHost.push_back("s2m.time.edu.cn");	// ������ѧ.

	timeServersHost.push_back("www.time.ac.cn");	// ������ʱ����.
	timeServersHost.push_back("time-a.nist.gov");	// NIST, Gaithersburg, Maryland .
	timeServersHost.push_back("time-b.nist.gov");	// NIST, Gaithersburg, Maryland .
	timeServersHost.push_back("time-a.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	timeServersHost.push_back("time-b.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	timeServersHost.push_back("time-c.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
	//timeServersHost.push_back("utcnist.colorado.edu");	// University of Colorado, Boulder .
	timeServersHost.push_back("time.nist.gov");	// NCAR, Boulder, Colorado .
	//timeServersHost.push_back("time-nw.nist.gov");	// Microsoft, Redmond, Washington .
	timeServersHost.push_back("nist1.symmetricom.com");	// Symmetricom, San Jose, California .
	//timeServersHost.push_back("nist1-dc.glassey.com");	// Abovenet, Virginia .
	//timeServersHost.push_back("nist1-ny.glassey.com");	// Abovenet, New York City .
	timeServersHost.push_back("nist1-sj.glassey.com");	// Abovenet, San Jose, California .
	timeServersHost.push_back("nist1.aol-ca.truetime.com");	// TrueTime, AOL facility, Sunnyvale, California .
	//timeServersHost.push_back("nist1.aol-va.truetime.com");	// TrueTime, AOL facility, Virginia.

	for (int i = 0; i < 100; ++i)
	{
		SYSTEMTIME st = getTimeFromInternet(timeServersHost);
		if (isValidSystemTime(st))
		{
			SetSystemTime(&st);
			break;
		}
	}

	WSACleanup();
	return 0;
 }

//// Server testing.
//int main()
//{
//	WSADATA WSAData = {};
//	WSAStartup(MAKEWORD(2,0), &WSAData);
//
//	// Available time server.
//	vector<string> timeServersHost;
//	timeServersHost.push_back("ntp.sjtu.edu.cn");	// �Ϻ���ͨ��ѧ.
//	timeServersHost.push_back("s1a.time.edu.cn");	// �����ʵ��ѧ.
//	timeServersHost.push_back("s1b.time.edu.cn");	// �廪��ѧ.
//	timeServersHost.push_back("s1c.time.edu.cn");	// ������ѧ.
//	timeServersHost.push_back("s1d.time.edu.cn");	// ���ϴ�ѧ.
//	timeServersHost.push_back("s1e.time.edu.cn");	// �廪��ѧ.
//	timeServersHost.push_back("s2a.time.edu.cn");	// �廪��ѧ.
//	timeServersHost.push_back("s2b.time.edu.cn");	// �廪��ѧ.
//	timeServersHost.push_back("s2c.time.edu.cn");	// �����ʵ��ѧ.
//	timeServersHost.push_back("s2d.time.edu.cn");	// ���ϵ�����������.
//	timeServersHost.push_back("s2e.time.edu.cn");	// ����������������.
//	timeServersHost.push_back("s2f.time.edu.cn");	// ����������������.
//	timeServersHost.push_back("s2g.time.edu.cn");	// �����ϵ�����������.
//	timeServersHost.push_back("s2h.time.edu.cn");	// �Ĵ���ѧ�����������.
//	timeServersHost.push_back("s2j.time.edu.cn");	// ����������ѧ��������.
//	timeServersHost.push_back("s2k.time.edu.cn");	// CERNET�������ڵ�.
//	timeServersHost.push_back("s2m.time.edu.cn");	// ������ѧ.
//
//	timeServersHost.push_back("www.time.ac.cn");	// ������ʱ����.
//	timeServersHost.push_back("time-a.nist.gov");	// NIST, Gaithersburg, Maryland .
//	timeServersHost.push_back("time-b.nist.gov");	// NIST, Gaithersburg, Maryland .
//	timeServersHost.push_back("time-a.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
//	timeServersHost.push_back("time-b.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
//	timeServersHost.push_back("time-c.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
//	timeServersHost.push_back("utcnist.colorado.edu");	// University of Colorado, Boulder .
//	timeServersHost.push_back("time.nist.gov");	// NCAR, Boulder, Colorado .
//	timeServersHost.push_back("time-nw.nist.gov");	// Microsoft, Redmond, Washington .
//	timeServersHost.push_back("nist1.symmetricom.com");	// Symmetricom, San Jose, California .
//	timeServersHost.push_back("nist1-dc.glassey.com");	// Abovenet, Virginia .
//	timeServersHost.push_back("nist1-ny.glassey.com");	// Abovenet, New York City .
//	timeServersHost.push_back("nist1-sj.glassey.com");	// Abovenet, San Jose, California .
//	timeServersHost.push_back("nist1.aol-ca.truetime.com");	// TrueTime, AOL facility, Sunnyvale, California .
//	timeServersHost.push_back("nist1.aol-va.truetime.com");	// TrueTime, AOL facility, Virginia.
//
//	// Time service testing.
//	unordered_map<string, unsigned> hostCnt;
//	unordered_map<string, string> hostIp;
//	
//	//for (int i = 0; i < 33; ++i)
//	int i = 0;
//	{
//		cout <<"---------------------------------   " <<i + 1 <<"-th   --------------------------------" <<endl;
//
//		for (auto const &j : timeServersHost)
//		{
//			hostIp[j] = hostnameToIp(j);
//			hostCnt[j] += !hostIp[j].empty() ? 1 : 0;
//
//			cout <<setw(30) <<j <<" : " <<setw(16) <<hostIp[j] <<" : " <<setw(3) <<hostCnt[j];
//			SYSTEMTIME st = {};
//			typedef pair<string, SYSTEMTIME &> Param;
//			Param param(hostIp[j], st);
//			HANDLE h = reinterpret_cast<HANDLE>(_beginthread([](void *param)
//						{
//							if (param != nullptr)
//							{
//								Param p = *reinterpret_cast<Param *>(param);
//								p.second = syncTimeFromIp(p.first);
//							}
//						}, 0, &param));
//			switch (WaitForSingleObject(h, sc_timeOut))
//			{
//			case WAIT_OBJECT_0:
//				if (isValidSystemTime(st))
//				{
//					cout <<" succ : hour is " <<setw(2) <<st.wHour+8 <<".";	// To east the 8th area.
//				}
//				else
//				{
//					cout <<" fail.";
//				}
//				cout <<endl;
//				break;
//			case WAIT_TIMEOUT:
//				cout <<" time out." <<endl;
//				break;
//			default:
//				cout <<" thread fail." <<endl;
//				break;
//			}
//		}
//	}
//
//	WSACleanup();
//	return 0;
//}