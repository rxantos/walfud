

// PathParser.h
//

#pragma once

#include <string>
#include <unordered_map>
#include <regex>
#include <functional>

/**
 *		We now support: plain text, CSIDL(wrapped in '?'), enviroment path(wrapped by '*').
 */
class PathParser
{
	static const char *sc_regex_csidl, *sc_regex_env;
	static const std::map<std::string, DWORD> sc_csidlTranslater;

public:
	PathParser(const std::string &magicPath);

private:
	std::string translate(const std::string &magicPath, std::regex rg, std::function<std::string (const std::string &)> translater);
	static std::string translateCsidl(const std::string &csidl);
	static std::string translateEnv(const std::string &env);

public:
	// data.
	std::string m_path;
	enum class Type
	{
		Default = 0,
		File,
		Dir,
	} m_type;
	bool m_fileExist;
};