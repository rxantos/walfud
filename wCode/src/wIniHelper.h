

// wIniHelper.h
//

#ifndef W_INI_HELPER_H
#define W_INI_HELPER_H

#include <wCppExt.h>

namespace w
{

/**
 *
 *		For easy parse Ini file.
 *
 */
/***** My testing case *****
			[0]
			a=
			=b
			c=d
			\=/
			=
			==
			===
			=a=

			[1]
			"="
			[=[

			[2]

			[0]
			y = x

			[=]
			[ ]
 ******************************/
class IniHelper
{
	// data.
	std::string m_iniFullpath;
	bool m_caseSensitive;
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> m_data;			// unordered_map<setction, unordered_map<key, value>>.

public:
	IniHelper();
	IniHelper(const std::string &iniFullpath, bool caseSensitive = false);

public:
	// Interface.
	bool load();
	bool save();

	std::string get(const std::string &section, const std::string &key) const;
	std::unordered_map<std::string, std::string> get(const std::string &section) const;				// '.first' is key, '.second' is value.
	std::unordered_map<std::string, std::unordered_map<std::string, std::string>> get() const;	// '.first' is section, '.second' is key/value pairs.

	bool set(const std::string &section, const std::string &key, const std::string &val);
	bool set(const std::string &section, const std::unordered_map<std::string, std::string> keyVals);
	bool set(const std::unordered_map<std::string, std::unordered_map<std::string, std::string>> &data);
private:
	// logic.
	void parseLine(const std::string &str);
};

}

#endif // W_INI_HELPER_H