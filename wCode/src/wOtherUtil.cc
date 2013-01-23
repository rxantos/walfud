

// wOtherUtil.cc
//

#include "wOtherUtil.h"
using namespace std;

namespace w
{

vector<string> getIniData(const string &fullpath, const char *sectionName, const char *keyName)
{
	string datas;
	unsigned size = 1024, readSize = 0;
	do
	{
		char *buf = new char[size *= 2];
		fill(buf, buf + size, '\0');

		readSize = static_cast<unsigned>(
								GetPrivateProfileStringA(sectionName,
														 keyName, 
														 NULL, 
														 buf, 
														 size, 
														 fullpath.c_str()));

		datas.assign(buf, readSize);
		
		delete[] buf;
		buf = NULL;

		// If there are more data, allocate more memory and retry.
	} while (readSize == size-(keyName != NULL && sectionName != NULL ? 1 : 2));	

	return strSplit(datas, string("\0", 1));
}
multimap<string, string> getIniKeyVal(const string &fullpath, const string &sectionName, const string &keyName)
{
	multimap<string, string> keyVal;

	vector<string> keys = getIniData(fullpath);
	for (vector<string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
	{
		vector<string> vals = getIniData(fullpath, sectionName.c_str(), keyName.c_str());

		if (vals.size() == 1)
		{
			//keyVal[*it] = vals[0];

		}
	}

	return keyVal;
}

}