

// timeSync.cpp
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

enum class SyncProtocol : unsigned
{
	DEFAULT,
	TimeProtocol,
	NetworkTimeProtocol,
};
enum class NetworkProtocol : unsigned
{
	DEFAULT,
	TCP,
	UDP,
};

struct NTP_Pack 
{
	char flag;
	char peerClockStratum;
	char peerPollingInterval;
	char peerClockPrecision; 
	char rootDelay[4];
	char clockDispersion[4];
	char referenceClock[4];
	char referenceClockUpdateTime[8];
	char originateTimeStamp[8];
	char receiveTimeStamp[8];
	char transmitTimeStamp[8];
};

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

/*
 *
 *		Synchronous time from specified server. Time Protocol. Both TCP and UDP is ok.
 *
 */
time_t syncTimeFromIp_tp_tcp(const sockaddr_in &sa)
{
cout <<"\t" <<"[tp/tcp]";
	time_t elapsedSecond = 0;

	// Send request to time server.
	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock != INVALID_SOCKET)
	{
		if (connect(sock, reinterpret_cast<const sockaddr *>(&sa), sizeof(sa)) == 0)
		{
			// Receive internet time.
			// The value returned by internet is the second elapsed since 1900/1/1 0:0:0.			
			recv(sock, reinterpret_cast<char *>(&elapsedSecond), sizeof(elapsedSecond), 0);
			elapsedSecond = ntohl(static_cast<unsigned long>(elapsedSecond)) - 2208988800;
		}//if (connect

		closesocket(sock);
	}//if (sock

	return elapsedSecond;
}
time_t syncTimeFromIp_tp_udp(const sockaddr_in &sa)
{
cout <<"\t" <<"[tp/udp]";
	time_t elapsedSecond = 0;

	// Send request to time server.
	SOCKET sock = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);		// UDP is unreliable.
	if (sock != INVALID_SOCKET)
	{
		// Receive internet time.
		// The value returned by internet is the second elapsed since 1900/1/1 0:0:0.
		sendto(sock, NULL, 0, 0, reinterpret_cast<const sockaddr *>(&sa), sizeof(sa));
		recvfrom(sock, reinterpret_cast<char *>(&elapsedSecond), sizeof(elapsedSecond), 0, nullptr, 0);
		elapsedSecond = ntohl(static_cast<unsigned long>(elapsedSecond)) - 2208988800;

		closesocket(sock);
	}//if (sock

	return elapsedSecond;
}
time_t syncTimeFromIp_tp(const sockaddr_in &sa, NetworkProtocol np = NetworkProtocol::TCP)
{
	// Time protocol.
	return np == NetworkProtocol::UDP ? syncTimeFromIp_tp_udp(sa)		// Using UDP.
									  : syncTimeFromIp_tp_tcp(sa);		// Using TCP.
}

/*
 *
 *		Synchronous time from specified server. Network Time Protocol. Only UDP.
 *
 */
time_t syncTimeFromIp_ntp_tcp(const sockaddr_in &sa)
{
cout <<"\t" <<"[ntp/tcp]";
	assert(false && "NetworkTimeProtocol only support UDP. Please call 'syncTimeFromIp_ntp_udp' instead.");

	return 0;
}
time_t syncTimeFromIp_ntp_udp(const sockaddr_in &sa)
{
cout <<"\t" <<"[ntp/udp]";
	time_t elapsedSecond = 0;

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock != INVALID_SOCKET)
	{
		NTP_Pack ntpPack = {};
		ntpPack.flag =0x1b;

		if (sendto(sock, reinterpret_cast<char *>(&ntpPack), sizeof(ntpPack), 
				   0, reinterpret_cast<const sockaddr *>(&sa), sizeof(sa)) == sizeof(ntpPack)
			&& recvfrom(sock, reinterpret_cast<char *>(&ntpPack), sizeof(ntpPack), 
						0, nullptr, nullptr) == sizeof(ntpPack))
		{
			memcpy(&elapsedSecond, ntpPack.receiveTimeStamp, sizeof(elapsedSecond));
			elapsedSecond = ntohl(static_cast<unsigned long>(elapsedSecond)) - 2208988800;	// '2208988800' is the second "1900/01/01 00:00:00" - "1970/01/01 00:00:00".
																							// Time protocol return a second elapsed from 1970/01/01 00:00:00,
																							// but 'gmtime' use a second goes from 1900/01/01 00:00:00. 
		}//if (sendto
		closesocket(sock);
	}//if (sock

	return elapsedSecond;
}
time_t syncTimeFromIp_ntp(const sockaddr_in &sa, NetworkProtocol np = NetworkProtocol::UDP)
{
	// Network time protocol.
	return np == NetworkProtocol::TCP ? syncTimeFromIp_ntp_tcp(sa)		// Using TCP.
									  : syncTimeFromIp_ntp_udp(sa);		// Using UDP.
}

SYSTEMTIME syncTimeFromIp(const string &timeServerIp, unsigned timeoutPerTry, 
						  SyncProtocol sp = SyncProtocol::NetworkTimeProtocol, NetworkProtocol np = NetworkProtocol::TCP)
{
	SYSTEMTIME st = {};
	time_t elapsedSecond = 0;

	// Network time protocol.
	// Construct socket address.
	sockaddr_in sa = {};
	sa.sin_family = AF_INET;
	sa.sin_addr.S_un.S_addr = inet_addr(timeServerIp.c_str());
	switch (sp)
	{
	case SyncProtocol::DEFAULT:
		// Fall through.
	case SyncProtocol::NetworkTimeProtocol:
		sa.sin_port = htons(IPPORT_NTP);
		elapsedSecond = syncTimeFromIp_ntp(sa, np);
		break;
	case SyncProtocol::TimeProtocol:
		sa.sin_port = htons(IPPORT_TIMESERVER);
		elapsedSecond = syncTimeFromIp_tp(sa, np);
		break;
	default:
		break;
	}

	if (elapsedSecond != 0)
	{
		if (tm *p = gmtime(&elapsedSecond))
		{
			st.wYear = p->tm_year + 1900,
			st.wMonth = p->tm_mon + 1,
			st.wDay = p->tm_mday,
			st.wDayOfWeek = p->tm_wday,
					
			st.wHour = p->tm_hour,
			st.wMinute = p->tm_min,
			st.wSecond = p->tm_sec,
			st.wMilliseconds = 0;
		}
	}

	return st;
}

SYSTEMTIME getTimeFromInternet(vector<string> serversHost, 
							   unsigned timeoutPerTry = sc_timeOut, 
							   SyncProtocol sp = SyncProtocol::NetworkTimeProtocol, NetworkProtocol np = NetworkProtocol::UDP,
							   bool tryAllServers = false)
{
	SYSTEMTIME res = {};

	bool found = false;

	for (vector<string>::const_iterator it = serversHost.cbegin(); 
		 it != serversHost.cend() && (!found || tryAllServers);		// If in debug mode, NOT exit.
		 ++it)
	{
		// Get system time from internet.
		typedef tuple<string *,				// In. Host.
					  string *,				// Out. Ip.
					  unsigned *,			// In. Timeout per try.
					  atomic_bool *,		// In. 'true' if caller to release memory; 'false' if callee to release memory.
					  SYSTEMTIME *,			// Out. System time.
					  SyncProtocol *,		// In. Synchronous protocol.
					  NetworkProtocol *		// In. Network protocol.
									> Param;
		Param *p = new Param;
		string *pHost = get<0>(*p) = new string(*it);
		string *pIp = get<1>(*p) = new string;
		unsigned *pTo = get<2>(*p) = new unsigned(timeoutPerTry);
		atomic_bool *pOwner = get<3>(*p) = new atomic_bool;
		SYSTEMTIME *pSt = get<4>(*p) = new SYSTEMTIME;
		SyncProtocol *pSp = get<5>(*p) = new SyncProtocol(sp);
		NetworkProtocol *pNp = get<6>(*p) = new NetworkProtocol(np);

		*pOwner = true;					// Caller is resposible for release.

		HANDLE h = reinterpret_cast<HANDLE>(_beginthread([](void *param)
					{
						if (Param *p = reinterpret_cast<Param *>(param))
						{
							string *host = get<0>(*p);
							string *ip = get<1>(*p);
							unsigned *to = get<2>(*p);
							atomic_bool *owner = get<3>(*p);
							SYSTEMTIME *st = get<4>(*p);
							SyncProtocol *sp = get<5>(*p);
							NetworkProtocol *np = get<6>(*p);
cout <<left <<setw(25) <<*host;
							*ip = hostnameToIp(*host);
cout <<"\t" <<*ip;
							*st = syncTimeFromIp(*ip, *to, *sp, *np);

							if (!*owner)
							{
								// Thread is resposible for release memory.
								delete host;
								delete ip;
								delete to;
								delete owner;
								delete st;
								delete sp;
								delete np;
								delete p;
							}
						}//if (Param
					}, 0, p));

		switch (WaitForSingleObject(h, timeoutPerTry))
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
	}//for

	return res;
}

struct Arg
{
	vector<string> hosts, ips;

	SyncProtocol sp;
	unsigned timeout;

	unsigned flag;
	static const unsigned sc_hosts	= 1 << 0,
						  sc_ips	= 1 << 1,
						  sc_sp		= 1 << 2,
						  sc_timeout= 1 << 3,
						  sc_debug	= 1 << 4;		// Only test servers but NOT change system time.
};

Arg getArg(const int argc, const char * const argv[])
{
	Arg arg = {};

	unsigned flag = 0;
	for (int i = 1; i < argc; ++i)
	{
		string str = argv[i];
		if (str[0] == '-')
		{
			// Options key.
			switch (str[1])
			{
			case 'p':
				// Synchronus protocol.
				flag = Arg::sc_sp;
				break;
			case 'h':
				// Time servers host.
				flag = Arg::sc_hosts;
				break;
			case 'i':
				// Time servers ip.
				flag = Arg::sc_ips;
				break;
			case 't':
				// Time out.
				flag = Arg::sc_timeout;
				break;
			case 'd':
				// Debug.
				flag = Arg::sc_debug;
			default:
				break;
			}//switch

			arg.flag |= flag;
		}
		else
		{
			// Options value.
			switch (flag)
			{
			case Arg::sc_sp:
				arg.sp = str == "tp" ? SyncProtocol::TimeProtocol
									 : SyncProtocol::NetworkTimeProtocol;
				break;
			case Arg::sc_hosts:
				arg.hosts.push_back(str);
				break;
			case Arg::sc_ips:
				// Not implement.
				break;
			case Arg::sc_timeout:
				arg.timeout = w::strToUnsigned(str);
				break;
			default:
				break;
			}//switch
		}//if
	}//for

	return arg;
}

#ifndef TEST
/*
 *
 *	Param: 
 *		-p: "tp"	=>	time protocol by tcp;
 *			"ntp"	=>	network time protocol by udp. (default)
 *		-h: time server host name. seperated by backspace.
 *		-i: time server ip. seperated by backspace. (unimplement)
 *		-t: time out per try, in millisecond. (default is 3000 ms.)
 *		-d: debug mode. All time server hosts will be tested, but NOT change your system time.
 *
 */
int main(int argc, char *argv[])
{
	WSADATA WSAData = {};
	WSAStartup(MAKEWORD(2,0), &WSAData);

	// Get parameter.
	Arg arg = getArg(argc, argv);

	// Available time server.
	vector<string> timeServersHost;
	if (Arg::sc_hosts & arg.flag)
	{
		// Use argument specified hosts.
		timeServersHost = arg.hosts;
	}
	else
	{
		// No argument hosts, use default hosts.
		timeServersHost.push_back("time-a.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
		timeServersHost.push_back("time-b.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
		timeServersHost.push_back("time-c.timefreq.bldrdoc.gov");	// NIST, Boulder, Colorado .
		timeServersHost.push_back("nist1.symmetricom.com");			// Symmetricom, San Jose, California .
		timeServersHost.push_back("nist1-sj.glassey.com");			// Abovenet, San Jose, California .
		timeServersHost.push_back("india.colorado.edu");			// 
		timeServersHost.push_back("time-a.nist.gov");				// NIST, Gaithersburg, Maryland .
		timeServersHost.push_back("time-b.nist.gov");				// NIST, Gaithersburg, Maryland .
	}

	unsigned timeout = Arg::sc_timeout & arg.flag ? arg.timeout : sc_timeOut;
	SyncProtocol sp = Arg::sc_sp & arg.flag ? arg.sp : SyncProtocol::DEFAULT;
	NetworkProtocol np = sp == SyncProtocol::TimeProtocol ? NetworkProtocol::TCP		// Only TimeProtocol uses TCP,
														  : NetworkProtocol::UDP;		// Otherwise use UDP.
	bool debugMode = (Arg::sc_debug & arg.flag) != 0 ? true : false;
	SYSTEMTIME st = getTimeFromInternet(timeServersHost, timeout, sp, np, debugMode);

	if (!(Arg::sc_debug & arg.flag))
	{
		if (isValidSystemTime(st))
		{
#ifndef DEBUG
			SetSystemTime(&st);
#endif // DEBUG.
		}
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

	timeServersHost.push_back("india.colorado.edu");	// 

	// Time service testing.
	unordered_map<string, unsigned> hostCnt;
	unordered_map<string, string> hostIp;
	
	for (int i = 0; i < 10; ++i)
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
					cout <<" succ : hour is " <<setw(2) <<st.wHour <<".";
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
			}//switch (WaitForSingleObject
		}//for (auto
	}//for (int

	WSACleanup();
	return 0;
}
#endif // TEST