

// MyBackup.h
//

#pragma once

#include "PathParser.h"

class MyBackup
{
	// data.
	std::string m_xmlFullpath;
	std::vector<std::map<std::string, std::string>> m_item;
		
public:
	// 

public:
	// Interface.
	bool Load(const std::string &xmlFullpath);

	bool Backup();
	bool Restore();

protected:
	virtual std::vector<std::map<std::string, std::string>> load(const std::string &xmlFullpath);
	bool act(std::map<std::string, std::string> item);
};

class MyBackup_360sd : public MyBackup
{
public:
};
class MyBackup_MSN : public MyBackup
{
public:
};
class MyBackup_QQ : public MyBackup
{
public:
};