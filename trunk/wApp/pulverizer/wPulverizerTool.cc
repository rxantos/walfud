

// wPulverizerTool.cc
//

#include "wPulverizerTool.h"
#include "wFilePermission.h"
#include <fstream>
using namespace std;

void grantPermission(const string &fullpath)
{ w::setPermission(fullpath, "everyone", GENERIC_ALL, true, false); }

void unloadHandle(const string &handleName)
{
	// TODO: 
}

void multiErase(const string &fullpath)
{
	static const char cx = static_cast<char>(0x00),
					  cy = static_cast<char>(0x55),
					  cz = static_cast<char>(static_cast<unsigned char>(0xAA));

	fstream::pos_type fileSize = 0;
	ifstream inFile(fullpath.c_str());
	if (inFile.is_open())
	{
		inFile.seekg(ios_base::end);
		fileSize = inFile.tellg();

		inFile.close();
	}

	ofstream outFile(fullpath.c_str());
	if (outFile.is_open())
	{
		for (int i = 0; i < 7; ++i)
		{
			char c = i == 0 ? cx :
					 i % 2 == 1 ? cy : cz;

			outFile.seekp(ios_base::beg);
			for (size_t i = 0; i < fileSize; ++i)
			{
				outFile.put(c);
			}

			outFile.flush();
		}

		outFile.close();
	}
}

string multiRename(const string &fullpath)
{
	string lastName;

	for (int i = 0; i < 7; ++i)
	{
		rename(fullpath.c_str(), (lastName = tmpnam(nullptr)).c_str()); 
	}

	return lastName;
}

void pulverize(const string &fullpath)
{ remove(fullpath.c_str()); }

void antiRegenerate(const string &fullpath)
{
	// TODO: 
}