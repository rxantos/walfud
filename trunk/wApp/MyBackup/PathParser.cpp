

// PathParser.cpp
//

#include "stdafx.h"
#include "PathParser.h"
#include <map>
#include <Shlobj.h>
#pragma comment(lib, "Shell32.lib")
using namespace std;
using namespace w;

PathParser::PathParser() {}
PathParser::PathParser(const string &magicPath) { operator()(magicPath); }

void PathParser::operator()(const string &magicPath)
{
	m_path = magicPath;

	// Registry.
	m_path = translate(m_path, regex(sc_regex_reg), translateReg);
	// Environment.
	m_path = translate(m_path, regex(sc_regex_env), translateEnv);
	// CSIDL.
	m_path = translate(m_path, regex(sc_regex_csidl), translateCsidl);

	// If the path is valid, we parse it to absolute one.
	// Relative -> Absolute path.
	if (m_path.find_first_of(R"(:*?"<>|)") == string::npos)
	{
		m_path = translateRel(m_path);
	}

	// Attribute field.
	if (!m_path.empty())
	{
		m_type = *m_path.rbegin() == '\\' ? Type::Dir : Type::File;
		m_fileExist = PathFileExists(m_path.c_str());
	}
}

string PathParser::translate(const string &magicPath, regex rg, function<string (const string &)> translater)
{
	string res = magicPath;

	unordered_multimap<string, string> magic_real;
	for (auto i = sregex_iterator(magicPath.begin(), magicPath.end(), rg); i != sregex_iterator(); ++i)
	{
		// Magic string.
		auto magic = i->str();
		auto pos = i->position();
		auto len = magic.length();
		//  Real string.
		auto real = translater(magic.substr(1, magic.length() - 2));	// Trim left and right side escape character.

		// If translate successfully, we replace the maigc string,
		// otherwise, we keep it in path unchanged.
		if (!real.empty())
		{
			magic_real.insert(make_pair(magic, real));
		}
	}//for i

	// Replace magic string with real string.
	for (auto const &i : magic_real)
	{
		auto magic = i.first,
				real = i.second;

		auto pos = res.find(magic);
		if (pos != string::npos)
		{
			auto itBeg = res.begin(), itEnd = res.begin();
			advance(itBeg, pos);
			advance(itEnd, pos + magic.length());

			res.replace(itBeg, itEnd, real);
		}
	}

	return res;
}
string PathParser::translateCsidl(const string &csidl)
{
	string res;

	auto it = sc_csidlTranslater.find(csidl);
	if (it == sc_csidlTranslater.end())
	{
		// Wrong csidl.
	}
	else
	{
		char buf[MAX_PATH] = {};
		if (SHGetSpecialFolderPath(nullptr, buf, it->second, FALSE))
		{
			// Success decode.
			res = buf;
		}
		else
		{
			// Fail.
		}
	}//if 

	return res;
}
string PathParser::translateEnv(const string &env)
{
	string res;

	char buf[MAX_PATH] = {};
	auto len = GetEnvironmentVariable(env.c_str(), buf, COUNTOF(buf));
	if (0 < len && len < COUNTOF(buf))
	{
		res = buf;
	}

	return res;
}
string PathParser::translateReg(const string &reg)
{
	string res;

	// HKEY_LOCAL_MACHINE   \    SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\360safe.exe   \   Path
	//      Main Key                                           Sub Key                                 Value
	string mainKey = regex_replace(reg, regex(R"(^([A-Z_]+)\\(.+)\\(.+)$)"), "$1"),
		   subKey = regex_replace(reg, regex(R"(^([A-Z_]+)\\(.+)\\(.+)$)"), "$2"),
		   val = regex_replace(reg, regex(R"(^([A-Z_]+)\\(.+)\\(.+)$)"), "$3");

	// 
	auto it = sc_regTranslater.find(mainKey);
	if (it == sc_regTranslater.end())
	{
		// Wrong main key.
	}
	else
	{
		HKEY hKey;
		if (RegOpenKeyEx(it->second, subKey.c_str(), 0, KEY_QUERY_VALUE | KEY_WOW64_64KEY, &hKey)
			== ERROR_SUCCESS)
		{
			char data[1024] = {};
			DWORD dataType = 0, dataLen = sizeof(data) - 1;		// `RegQueryValueEx` can NOT sure '\0' terminated.
			if (RegQueryValueEx(hKey, val.c_str(), nullptr, &dataType, (BYTE *)data, &dataLen)
				== ERROR_SUCCESS)
			{
				res = data;
			}
		}//if RegOpenKeyEx
	}//if it

	return res;
}

string PathParser::translateRel(const string &rel)
{
	// '.\foo'		=>	'foo' at CURRENT directory
	// '..\bar'		=>	'bar' at PARENT directory
	// '\baz'		=>	'baz' at ROOT directory. '\' takes effect only in the begin of a path.

	string res;

	auto v = strSplit(rel, '\\');	
	if (v.empty())
	{
		return res;
	}

	char moduleFullpath[MAX_PATH] = {};
	GetModuleFileName(nullptr, moduleFullpath, COUNTOF(moduleFullpath));	// Do NOT modify me!

	// If '\' terminated?
	auto isDir = *v.rbegin() == "";

	// At front: '.\foo\bar'. First part.
	{
		string strFirstPart;
		auto i = v.begin();
		if (false)
		{
		}
		else if (*i == ".")
		{
			// '.\foo'
			strFirstPart = regex_replace(moduleFullpath, regex(R"(^(.+)\\([^\\]+)\\?$)"), "$1");
		}
		else if (*i == "..")
		{
			// '..\bar'
			strFirstPart = regex_replace(moduleFullpath, regex(R"(^(.+)\\([^\\]+)\\([^\\]+)$)"), "$1");	// Parent path.
		}
		else if (*i == "")
		{
			// '\baz'
			strFirstPart.assign(moduleFullpath, moduleFullpath + 2);
		}
		else
		{
		}

		if (!strFirstPart.empty())
		{
			auto vFirstPart = strSplit(strFirstPart, "\\");
			v.erase(i);			
			copy(v.begin(), v.end(), back_inserter(vFirstPart));

			swap(vFirstPart, v);
		}
	}

	// Symbol in following part.
	vector<string> vRes;
	bool needDriName = false;
	for (size_t i = 0; i < v.size(); ++i)
	{
		string &s = v[i];
		if (false) {}
		else if (s == ".")
		{
			// Skip.
		}
		else if (s == "..")
		{
			if (!vRes.empty())
			{
				vRes.pop_back();
			}
			else
			{
				// Reach root path.
				// We'd append a driver name to the front.
				needDriName = true;
			}
		}
		else if (s == "")
		{
			// Skip.
		}
		else
		{
			vRes.push_back(s);
		}
	}

	// Re-construct.
	for_each(vRes.begin(), vRes.end(), [&res](const string &s){ res += s + "\\"; });
	
	// 
	if (!isDir)
	{
		res = strTrimRight(res, "\\");
	}

	// 
	if (needDriName)
	{
		res = string(moduleFullpath, moduleFullpath + 2) + "\\" + res;
	}

	return res;
}


///
const char *PathParser::sc_regex_csidl = R"(\|)"   R"(([^|]+))"   R"(\|)",
		   *PathParser::sc_regex_env = R"(\?)"   R"(([^?]+))"   R"(\?)",
		   *PathParser::sc_regex_reg = R"(:)"   R"(([^:]+))"   R"(:)";
const map<string, DWORD> PathParser::sc_csidlTranslater = 
{
	{ "CSIDL_DESKTOP"                   , 0x0000        /* <desktop */ }, 
	{ "CSIDL_INTERNET"                  , 0x0001        /* Internet Explorer (icon on desktop */ }, 
	{ "CSIDL_PROGRAMS"                  , 0x0002        /* Start Menu\Program */ }, 
	{ "CSIDL_CONTROLS"                  , 0x0003        /* My Computer\Control Pane */ }, 
	{ "CSIDL_PRINTERS"                  , 0x0004        /* My Computer\Printer */ }, 
	{ "CSIDL_PERSONAL"                  , 0x0005        /* My Document */ }, 
	{ "CSIDL_FAVORITES"                 , 0x0006        /* <user name>\Favorite */ }, 
	{ "CSIDL_STARTUP"                   , 0x0007        /* Start Menu\Programs\Startu */ }, 
	{ "CSIDL_RECENT"                    , 0x0008        /* <user name>\Recen */ }, 
	{ "CSIDL_SENDTO"                    , 0x0009        /* <user name>\SendT */ }, 
	{ "CSIDL_BITBUCKET"                 , 0x000a        /* <desktop>\Recycle Bi */ }, 
	{ "CSIDL_STARTMENU"                 , 0x000b        /* <user name>\Start Men */ }, 
	{ "CSIDL_MYDOCUMENTS"               , 0x0005        /* CSIDL_PERSONAL. Personal was just a silly name for My Document */ }, 
	{ "CSIDL_MYMUSIC"                   , 0x000d        /* "My Music" folde */ }, 
	{ "CSIDL_MYVIDEO"                   , 0x000e        /* "My Videos" folde */ }, 
	{ "CSIDL_DESKTOPDIRECTORY"          , 0x0010        /* <user name>\Deskto */ }, 
	{ "CSIDL_DRIVES"                    , 0x0011        /* My Compute */ }, 
	{ "CSIDL_NETWORK"                   , 0x0012        /* Network Neighborhood (My Network Places */ }, 
	{ "CSIDL_NETHOOD"                   , 0x0013        /* <user name>\nethoo */ }, 
	{ "CSIDL_FONTS"                     , 0x0014        /* windows\font */ }, 
	{ "CSIDL_TEMPLATES"                 , 0x0015 }, 
	{ "CSIDL_COMMON_STARTMENU"          , 0x0016        /* All Users\Start Men */ }, 
	{ "CSIDL_COMMON_PROGRAMS"           , 0X0017        /* All Users\Start Menu\Program */ }, 
	{ "CSIDL_COMMON_STARTUP"            , 0x0018        /* All Users\Startu */ }, 
	{ "CSIDL_COMMON_DESKTOPDIRECTORY"   , 0x0019        /* All Users\Deskto */ }, 
	{ "CSIDL_APPDATA"                   , 0x001a        /* <user name>\Application Dat */ }, 
	{ "CSIDL_PRINTHOOD"                 , 0x001b        /* <user name>\PrintHoo */ }, 
	{ "CSIDL_LOCAL_APPDATA"             , 0x001c        /* <user name>\Local Settings\Applicaiton Data (non roaming */ }, 
	{ "CSIDL_ALTSTARTUP"                , 0x001d        /* non localized startu */ }, 
	{ "CSIDL_COMMON_ALTSTARTUP"         , 0x001e        /* non localized common startu */ }, 
	{ "CSIDL_COMMON_FAVORITES"          , 0x001f }, 
	{ "CSIDL_INTERNET_CACHE"            , 0x0020 }, 
	{ "CSIDL_COOKIES"                   , 0x0021 }, 
	{ "CSIDL_HISTORY"                   , 0x0022 }, 
	{ "CSIDL_COMMON_APPDATA"            , 0x0023        /* All Users\Application Dat */ }, 
	{ "CSIDL_WINDOWS"                   , 0x0024        /* GetWindowsDirectory( */ }, 
	{ "CSIDL_SYSTEM"                    , 0x0025        /* GetSystemDirectory( */ }, 
	{ "CSIDL_PROGRAM_FILES"             , 0x0026        /* C:\Program File */ }, 
	{ "CSIDL_MYPICTURES"                , 0x0027        /* C:\Program Files\My Picture */ }, 
	{ "CSIDL_PROFILE"                   , 0x0028        /* USERPROFIL */ }, 
	{ "CSIDL_SYSTEMX86"                 , 0x0029        /* x86 system directory on RIS */ }, 
	{ "CSIDL_PROGRAM_FILESX86"          , 0x002a        /* x86 C:\Program Files on RIS */ }, 
	{ "CSIDL_PROGRAM_FILES_COMMON"      , 0x002b        /* C:\Program Files\Commo */ }, 
	{ "CSIDL_PROGRAM_FILES_COMMONX86"   , 0x002c        /* x86 Program Files\Common on RIS */ }, 
	{ "CSIDL_COMMON_TEMPLATES"          , 0x002d        /* All Users\Template */ }, 
	{ "CSIDL_COMMON_DOCUMENTS"          , 0x002e        /* All Users\Document */ }, 
	{ "CSIDL_COMMON_ADMINTOOLS"         , 0x002f        /* All Users\Start Menu\Programs\Administrative Tool */ }, 
	{ "CSIDL_ADMINTOOLS"                , 0x0030        /* <user name>\Start Menu\Programs\Administrative Tool */ }, 
	{ "CSIDL_CONNECTIONS"               , 0x0031        /* Network and Dial-up Connection */ }, 
	{ "CSIDL_COMMON_MUSIC"              , 0x0035        /* All Users\My Musi */ }, 
	{ "CSIDL_COMMON_PICTURES"           , 0x0036        /* All Users\My Picture */ }, 
	{ "CSIDL_COMMON_VIDEO"              , 0x0037        /* All Users\My Vide */ }, 
	{ "CSIDL_RESOURCES"                 , 0x0038        /* Resource Direcotr */ }, 
	{ "CSIDL_RESOURCES_LOCALIZED"       , 0x0039        /* Localized Resource Direcotr */ }, 
	{ "CSIDL_COMMON_OEM_LINKS"          , 0x003a        /* Links to All Users OEM specific app */ }, 
	{ "CSIDL_CDBURN_AREA"               , 0x003b        /* USERPROFILE\Local Settings\Application Data\Microsoft\CD Burnin */ }, 
	{ "CSIDL_COMPUTERSNEARME"           , 0x003d        /* Computers Near Me (computered from Workgroup membership */ }, 
	{ "CSIDL_FLAG_CREATE"               , 0x8000        /* combine with CSIDL_ value to force folder creation in SHGetFolderPath( */ }, 
	{ "CSIDL_FLAG_DONT_VERIFY"          , 0x4000        /* combine with CSIDL_ value to return an unverified folder pat */ }, 
	{ "CSIDL_FLAG_DONT_UNEXPAND"        , 0x2000        /* combine with CSIDL_ value to avoid unexpanding environment variable */ }, 
	{ "CSIDL_FLAG_NO_ALIAS"             , 0x1000        /* combine with CSIDL_ value to insure non-alias versions of the pid */ }, 
	{ "CSIDL_FLAG_PER_USER_INIT"        , 0x0800        /* combine with CSIDL_ value to indicate per-user init (eg. upgrade */ }, 
	{ "CSIDL_FLAG_MASK"                 , 0xFF00        /* mask for all possible flag value */ }, 
};
const map<string, HKEY> PathParser::sc_regTranslater = 
{
	{ "HKEY_CURRENT_USER"				, HKEY_CURRENT_USER }, 
	{ "HKEY_LOCAL_MACHINE"				, HKEY_LOCAL_MACHINE }, 
	{ "HKEY_USERS"						, HKEY_USERS }, 
};