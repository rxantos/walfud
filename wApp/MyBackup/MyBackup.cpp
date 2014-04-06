

// MyBackup.cpp
//

#include "stdafx.h"
#include "MyBackup.h"
#include "FileOp.h"
#include "../Common/pugixml-1.4/src/pugixml.hpp"
using namespace pugi;
using namespace w;
using namespace std;

auto 
		// Root node name.
		c_nodeName_myBackup = "MyBackup", c_nodeName_item = "Item",
		// Attribute name.
		c_attrName_myBackup_name = "name", c_attrName_item_pathSrc = "pathSrc", c_attrName_item_pathDst = "pathDst";

bool MyBackup::Load(const std::string &xmlFullpath)
{
	m_item = load(xmlFullpath);
	return !m_item.empty();
}
vector<map<string, string>> MyBackup::load(const string &xmlFullpath)
{
	decltype(m_item) items;
	m_xmlFullpath = xmlFullpath;

	xml_document doc;
	if (doc.load_file(xmlFullpath.c_str()))
	{
		if (auto node_myBackup = doc.child(c_nodeName_myBackup))
		{
			// MyBackup's Attr.
			auto attr_myBackup_name = node_myBackup.attribute(c_attrName_myBackup_name);

			// Item.
			for (auto node_item = node_myBackup.child(c_nodeName_item); node_item; node_item = node_item.next_sibling())
			{
				map<string, string> item;
				// Item's Attr.
				auto attr_item_pathSrc = node_item.attribute(c_attrName_item_pathSrc),
					 attr_item_pathDst = node_item.attribute(c_attrName_item_pathDst);

				// Xml => map.
				item[c_attrName_item_pathSrc] = PathParser(attr_item_pathSrc.as_string()).m_path;
				item[c_attrName_item_pathDst] = PathParser(attr_item_pathDst.as_string()).m_path;

				items.push_back(item);
			}//for node_item
		}// if node_myBackup
	}//if doc

	return items;
}
bool MyBackup::Backup()
{
	bool res = false;

	for (auto const &i : m_item)
	{
		act(i);
	}

	return res;
}
bool MyBackup::Restore()
{
	bool res = false;

	for (auto i : m_item)
	{
		// swap src and dst.
		swap(i[c_attrName_item_pathSrc], i[c_attrName_item_pathDst]);

		act(i);
	}

	return res;
}

// logic.
bool MyBackup::act(map<string, string> item)
{
	bool res = false;
	
	string src = item[c_attrName_item_pathSrc],
		   dst = item[c_attrName_item_pathDst];
	res = Copy(src, dst);

	return res;
}

///////////////