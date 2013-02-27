

// IniHelper.cpp
//

#include "wIniHelper.h"
using namespace std;

namespace w
{

// IniHelper.
IniHelper::IniHelper(const string &iniFullpath) : m_iniFullpath(iniFullpath)
{}

// Interface.
bool IniHelper::load()
{
	bool res = true;

	// Load sections.
	char *buf = new char[msc_maxBufLen];
	ZeroMemory(buf, msc_maxBufLen);

	DWORD writeLen = GetPrivateProfileSectionNames(buf, msc_maxBufLen, m_iniFullpath.c_str());
	if (writeLen != msc_maxBufLen - 2)
	{
		// Read successfully.
		// 'buf' is like: "1234\0abcd\0!@#$\0\0".
		vector<string> sections = strSplit(buf, buf + writeLen, '\0');
		for (auto const &i : sections)
		{
			if (!i.empty())
			{
				m_data.insert(make_pair(i, unordered_multimap<string, string>()));
			}
		}
	}

	delete []buf;
	buf = NULL;

	// Load key/value pairs.
	for (auto &i : m_data)
	{
		char *buf = new char[msc_maxBufLen];
		ZeroMemory(buf, msc_maxBufLen);

		DWORD writeLen = GetPrivateProfileSection(i.first.c_str(), buf, msc_maxBufLen, m_iniFullpath.c_str());
		if (writeLen != msc_maxBufLen - 2)
		{
			// Read successfully.
			// 'buf' is like "key1=val1\0key2=val2\0key3=val3\0".
			vector<string> pairs = strSplit(buf, buf + writeLen, '\0');
			for (auto j : pairs)
			{
				if (!j.empty())
				{
					vector<string> keyVal = strSplit(j, '=');
					keyVal.resize(2);

					i.second.insert(make_pair(keyVal[0], keyVal[1]));
				}
			}
		}

		delete []buf;
		buf = NULL;
	}//for

	return res;
}
bool IniHelper::save()
{
	bool res = true;

	ofstream outFile(m_iniFullpath.c_str(), ios_base::trunc | ios_base::out);
	if (outFile.is_open())
	{
		for (auto i : m_data)
		{
			outFile <<"[" <<i.first <<"]" <<endl;
			for (auto j : i.second)
			{
				outFile <<j.first <<"=" <<j.second <<endl;
			}
		}

		outFile.close();
	}

	return res;
}

string IniHelper::get(const string &section, const string &key) const
{
	string val;

	unordered_multimap<string, unordered_multimap<string, string>>::const_iterator it = m_data.find(section);
	if (it != m_data.end())
	{
		unordered_multimap<string, string>::const_iterator jt = it->second.find(key);
		if (jt != it->second.end())
		{
			val = jt->second;
		}
	}

	return val;
}
unordered_multimap<string, string> IniHelper::get(const string &section) const
{
	unordered_multimap<string, string> keyVal;

	unordered_multimap<string, unordered_multimap<string, string>>::const_iterator it = m_data.find(section);
	if (it != m_data.end())
	{
		keyVal = it->second;
	}

	return keyVal;
}
unordered_multimap<string, unordered_multimap<string, string>> IniHelper::get() const { return m_data; }

bool IniHelper::set(const string &section, const string &key, const string &val)
{
	bool res = false;

	auto sectionPos = find_if(m_data.begin(), m_data.end(), [&section](const pair<string, unordered_multimap<string, string>> &item) -> bool { return item.first == section; });
	if (sectionPos != m_data.end())
	{
		auto keyPos = find_if(sectionPos->second.begin(), sectionPos->second.end(), [&key](const pair<string, string> &keyVal) -> bool { return keyVal.first == key; });
		if (keyPos != sectionPos->second.end())
		{
			keyPos->second = val;
			res = true;
		}
	}

	return res;
}
bool IniHelper::set(const string &section, const unordered_multimap<string, string> keyVals)
{
	bool res = false;

	auto sectionPos = find_if(m_data.begin(), m_data.end(), [&section](const pair<string, unordered_multimap<string, string>> &item){ return item.first == section; });
	if (sectionPos != m_data.end())
	{
		sectionPos->second = keyVals;
		res = true;
	}

	return res;
}
bool IniHelper::set(const unordered_multimap<string, unordered_multimap<string, string>> &data)
{
	bool res = true;

	m_data = data;

	return res;
}

// logic.

}