

// wIniHelper.h
//

#ifndef W_INI_HELPER_H
#define W_INI_HELPER_H

#include <wCppExt.h>

namespace w
{

class IniHelper
{
	// data.
	std::string m_iniFullpath;
	std::unordered_multimap<std::string, std::unordered_multimap<std::string, std::string>> m_data;			// unordered_multimap<setction, unordered_multimap<key, value>>.

	static const unsigned msc_maxBufLen = 1024 * 1024;												// Ini file must within 1Mb, otherwise, truncated.

public:
	IniHelper(const std::string &iniFullpath);
public:
	// Interface.
	bool load();
	bool save();

	std::string get(const std::string &section, const std::string &key) const;
	std::unordered_multimap<std::string, std::string> get(const std::string &section) const;				// '.first' is key, '.second' is value.
	std::unordered_multimap<std::string, std::unordered_multimap<std::string, std::string>> get() const;		// '.first' is section, '.second' is key/value pairs.

	bool set(const std::string &section, const std::string &key, const std::string &val);
	bool set(const std::string &section, const std::unordered_multimap<std::string, std::string> keyVals);
	bool set(const std::unordered_multimap<std::string, std::unordered_multimap<std::string, std::string>> &data);
private:
	// logic.
};

}

#endif // W_INI_HELPER_H