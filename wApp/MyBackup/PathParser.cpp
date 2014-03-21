

// PathParser.cpp
//

#include "stdafx.h"
#include "PathParser.h"
#include <map>
#include <Shlobj.h>
#pragma comment(lib, "Shell32.lib")
using namespace std;

const char *PathParser::sc_regex_csidl = "\\?[^?]+\\?",
		   *PathParser::sc_regex_env = "\\*[^*]+\\*";
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

PathParser::PathParser(const string &magicPath)
{
	m_path = magicPath;

	// Translate CSIDL.
	m_path = translate(m_path, regex(sc_regex_csidl), translateCsidl);
	// Translate Evvironment.
	m_path = translate(m_path, regex(sc_regex_env), translateEnv);

	// Attribute field.
	m_type = *m_path.rbegin() == '\\' ? Type::Dir : Type::File;
	m_fileExist = PathFileExists(m_path.c_str());
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