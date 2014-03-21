

// MainDlg.cpp
//

#include "stdafx.h"
#include "MainDlg.h"
#include "PathParser.h"
#include "FileOp.h"
using namespace std;

#include "../Common/pugixml-1.4/src/pugixml.hpp"
using namespace pugi;
using namespace w;

auto 
		// Root node name.
		c_nodeName_myBackup = "MyBackup", c_nodeName_item = "Item",
		// Attribute name.
		c_attrName_myBackup_name = "name", c_attrName_item_pathSrc = "pathSrc", c_attrName_item_pathDst = "pathDst", c_attrName_item_mode = "mode", 
		// Value constant.
		c_mode_replaceIfExist = "replaceIfExist";

void foo(const string xmlFullpath)
{
	xml_document doc;
	if (doc.load_file(xmlFullpath.c_str()))
	{
		if (auto node_myBackup = doc.child(c_nodeName_myBackup))
		{
			// Root's Attr.
			auto attr_myBackup_name = node_myBackup.attribute(c_attrName_myBackup_name);

			// Item.
			for (auto node_item = node_myBackup.child(c_nodeName_item); node_item; node_item = node_item.next_sibling())
			{
				// Item's Attr.
				auto attr_item_pathSrc = node_item.attribute(c_attrName_item_pathSrc),
					 attr_item_pathDst = node_item.attribute(c_attrName_item_pathDst),
					 attr_item_mode = node_item.attribute(c_attrName_item_mode);

				// 
				auto src = PathParser(attr_item_pathSrc.as_string()),
					 dst = PathParser(attr_item_pathDst.as_string());

				// 
				Copy(src, dst);
			}//for node_item
		}// if node_myBackup
	}//if doc
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	foo("E:\\walfud\\trunk\\wApp\\MyBackup\\test.xml");

	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
	SetIcon(hIconSmall, FALSE);

	// register object for message filtering and idle updates
	CMessageLoop* pLoop = _Module.GetMessageLoop();
	ATLASSERT(pLoop != NULL);
	pLoop->AddMessageFilter(this);
	pLoop->AddIdleHandler(this);

	UIAddChildWindowContainer(m_hWnd);

	return TRUE;
}