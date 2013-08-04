

// IniHelper.cpp
//

#include "wIniHelper.h"
using namespace std;

namespace w
{

// IniHelper.
IniHelper::IniHelper()
	: IniHelper("", false)
{}
IniHelper::IniHelper(const string &iniFullpath, bool caseSensitive) 
	: m_iniFullpath(iniFullpath), m_caseSensitive(caseSensitive), m_data()
{}

// Interface.
bool IniHelper::load()
{
	bool res = true;

	ifstream inFile(m_iniFullpath.c_str());
	if (inFile.is_open())
	{
		m_data.clear();

		string line;
		while (getline(inFile, line))
		{
			// Everyline.
			parseLine(line);
		}

		inFile.close();
	}

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

	unordered_map<string, unordered_map<string, string>>::const_iterator it = m_data.find(section);
	if (it != m_data.end())
	{
		unordered_map<string, string>::const_iterator jt = it->second.find(key);
		if (jt != it->second.end())
		{
			val = jt->second;
		}
	}

	return val;
}
unordered_map<string, string> IniHelper::get(const string &section) const
{
	unordered_map<string, string> keyVal;

	unordered_map<string, unordered_map<string, string>>::const_iterator it = m_data.find(section);
	if (it != m_data.end())
	{
		keyVal = it->second;
	}

	return keyVal;
}
unordered_map<string, unordered_map<string, string>> IniHelper::get() const { return m_data; }

bool IniHelper::set(const string &section, const string &key, const string &val)
{
	bool res = false;

	auto sectionPos = find_if(m_data.begin(), m_data.end(), [&section](const pair<string, unordered_map<string, string>> &item) -> bool { return item.first == section; });
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
bool IniHelper::set(const string &section, const unordered_map<string, string> keyVals)
{
	bool res = false;

	auto sectionPos = find_if(m_data.begin(), m_data.end(), [&section](const pair<string, unordered_map<string, string>> &item){ return item.first == section; });
	if (sectionPos != m_data.end())
	{
		sectionPos->second = keyVals;
		res = true;
	}

	return res;
}
bool IniHelper::set(const unordered_map<string, unordered_map<string, string>> &data)
{
	bool res = true;

	m_data = data;

	return res;
}

// logic.
void IniHelper::parseLine(const std::string &str)
{
	static string s_prevSectionName;

	// Empty line.
	if (str.empty())
	{
		return;
	}

	if (regex_match(str, regex("^\\[.+\\]$")))		// "[section name]".
	{
		// Section name.
		string sectionName;

		size_t i = 1, j = str.length() - 1;
		if (i <= j)
		{
			sectionName = str.substr(i, j - i);

			m_data[sectionName];
			s_prevSectionName = sectionName;
		}
	}
	else if (regex_match(str, regex("^.*=.*$")))	// "key=value".
	{
		// Key-value pair.
		string k, v;

		string::const_iterator it = find(str.cbegin(), str.cend(), '=');
		if (it != str.cend())
		{
			copy(str.cbegin(), it, back_inserter(k));
			copy(it + 1, str.cend(), back_inserter(v));

			m_data[s_prevSectionName].insert(make_pair(k, v));
		}
	}
	else
	{
		// Invalid line. Maybe comment.
	}
}

}