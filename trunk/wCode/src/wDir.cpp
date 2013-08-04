

// wDir.h
//

#include "wDir.h"
#include <Shlwapi.h>
using namespace std;

#pragma comment(lib, "Shlwapi.lib")

namespace w
{

string getTrueFullpath(string fullpath, bool uncOrPlain)
{
	// "\\?\c:\foo\bar".
	fullpath = strTrimRight(strMakeLeft(fullpath, "\\\\?\\"), "\\");
	
	DWORD attr = GetFileAttributes(fullpath.c_str());
	if (attr == INVALID_FILE_ATTRIBUTES)
	{
		fullpath.empty();
	}
	else if (attr & FILE_ATTRIBUTE_DIRECTORY)
	{
		fullpath = strMakeRight(fullpath, "\\");
	}
	else
	{
		// Nothing.
	}
	
	return uncOrPlain ? fullpath : strTrimLeft(fullpath, "\\\\?\\");
}

bool pathSplit(string fullpath,
			   string &drive, string &dir, string &namePart, string &extPart)
{
	// drive.
	if (fullpath.length() > 1
		&& isalpha(fullpath[0]) != 0
		&& fullpath[1] == ':')
	{
		drive = fullpath.substr(0, 2);
		fullpath.erase(0, 2);
	}

	// Path.
	size_t pathEnd = fullpath.rfind('\\') == string::npos ? 0 : fullpath.rfind('\\') + 1;
	pathEnd = fullpath.find_first_not_of('.', pathEnd) == string::npos ? fullpath.length() : pathEnd;
	dir = strMakeRight(fullpath.substr(0, pathEnd), "\\");
	fullpath.erase(0, pathEnd);

	// Name part.
	const size_t nameEnd = fullpath.rfind('.');
	namePart = fullpath.substr(0, nameEnd);
	fullpath.erase(0, nameEnd + 1);

	// Extend part.
	extPart = fullpath;

	return true;
}

unordered_set<string> traverseNextLevel(const string &fullpath)
{
	unordered_set<string> res;

	bool isDir = regex_match(fullpath, regex("^.+\\\\$"));

	WIN32_FIND_DATA fd = {};
	HANDLE h = FindFirstFile((fullpath + (isDir ? "*" : "")).c_str(), &fd);
	if (h != INVALID_HANDLE_VALUE)		// If is directory, append "*".
	{
		while (FindNextFile(h, &fd))
		{
			// 'fullpath' must be a directory.
			if (!regex_match(fd.cFileName, regex("^\\.|\\.\\.$")))		// Skip "." or "..".
			{
				res.insert(fullpath + fd.cFileName + (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ? "\\" : ""));
			}
		}
	}
	FindClose(h);

	return res;
}
unordered_set<string> traverseNextLevel(const unordered_set<string> &fullpath)
{
	unordered_set<string> res;

	for (auto i : fullpath)
	{
		unordered_set<string> subRes = traverseNextLevel(i);
		copy(subRes.begin(), subRes.end(), inserter(res, res.end()));
	}

	return res;
}

unordered_multimap<unsigned, string> traverseInBreadth(const string &fullpath, unsigned begLevel, unsigned endLevel)
{
	unordered_multimap<unsigned, string> res;

	unsigned curLevel = 0;
	auto noSubLevelObj = [](const string &fullpath){ return regex_match(fullpath, regex("^.+\\\\$")); };

	// Retrive top level fullpath.
	if (begLevel <= curLevel && curLevel < endLevel)
	{
		res.insert(make_pair(curLevel, fullpath));
	}

	// Get sub level fullpaths.
	unordered_set<string> curLevelRes;
	curLevelRes.insert(fullpath);
	while (++curLevel < endLevel												// Within the last level.
		   && any_of(curLevelRes.begin(), curLevelRes.end(), noSubLevelObj))	// Still has sub objects.
	{
		curLevelRes = traverseNextLevel(curLevelRes);

		if (begLevel <= curLevel && curLevel < endLevel)
		{
			for (auto i : curLevelRes)
			{
				res.insert(make_pair(curLevel, i));
			}
		}//if (begLevel
	}//while (++curLevel

	return res;
}

}