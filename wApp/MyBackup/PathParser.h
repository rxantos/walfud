

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
	static const char *sc_regex_csidl, *sc_regex_env, *sc_regex_reg;
	static const std::map<std::string, DWORD> sc_csidlTranslater;
	static const std::map<std::string, HKEY>  sc_regTranslater;

public:
	PathParser();
	PathParser(const std::string &magicPath);

	void operator()(const std::string &magicPath);

private:
	std::string translate(const std::string &magicPath, std::regex rg, std::function<std::string (const std::string &)> translater);
	static std::string translateCsidl(const std::string &csidl);
	static std::string translateEnv(const std::string &env);
	static std::string translateReg(const std::string &reg);
	static std::string translateRel(const std::string &rel);

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