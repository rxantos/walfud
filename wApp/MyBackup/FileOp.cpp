

// FileOp.cpp
//

#include "stdafx.h"
#include "FileOp.h"
using namespace std;
using namespace w;

static const auto fn_isDir = [](const string &path) 
{
	auto attr = GetFileAttributes(path.c_str());

	return attr != INVALID_FILE_ATTRIBUTES && attr & FILE_ATTRIBUTE_DIRECTORY;
};

bool Copy(const PathParser &src, const PathParser &dst)
{
	auto srcPath = src.m_path, dstPath = dst.m_path;

	if (false)
	{ /* Stub */ }
	else if (src.m_type == PathParser::Type::File)
	{
		if (false)
		{}
		else if (dst.m_type == PathParser::Type::File)
		{
			// File -> File.
			CopyFile(srcPath.c_str(), dstPath.c_str(), FALSE);
		}
		else if (dst.m_type == PathParser::Type::Dir)
		{
			// File -> Dir.
			// Append file name at the end of `dstPath`.
			string dstFullpath = dstPath + PathFindFileName(srcPath.c_str());
			CopyFile(srcPath.c_str(), dstFullpath.c_str(), FALSE);
		}
		else
		{}
	}
	else if (src.m_type == PathParser::Type::Dir)
	{
		if (dst.m_type == PathParser::Type::Dir)
		{
			// Dir -> Dir.
			list<string> files, dirs = {src.m_path};

			for (list<string>::iterator it = dirs.begin(); it != dirs.end(); ++it)
			{
				srcPath = strMakeRight(*it, "\\");

				WIN32_FIND_DATA wfd = {};
				auto hFind = FindFirstFile((srcPath + "*").c_str(), &wfd);
				if (hFind != INVALID_HANDLE_VALUE)
				{
					do 
					{
						if (string(wfd.cFileName) != "."
							&& string(wfd.cFileName) != "..")
						{
							string newDst = srcPath + wfd.cFileName;
							if (fn_isDir(newDst))
							{
								// New dir.
								string path = strMakeRight(newDst, "\\");
								dirs.push_back(path);
							}
							else
							{
								// New file.
								files.push_back(newDst);
							}
						}
					} while (FindNextFile(hFind, &wfd));

					FindClose(hFind);
				}
			}//for

			// Get source directory name.
			auto srcParentPath = regex_replace(src.m_path, regex("^(.+\\\\)(.+)\\\\$"), "$1"),
				 folderName = regex_replace(src.m_path, regex("^(.+\\\\)(.+)\\\\$"), "$2");

			// Create all sub-directories.
			for (auto const &i : dirs)
			{
				auto newDstPath = dst.m_path + strTrimLeft(i, srcParentPath);
				CreateDir(newDstPath);
			}
			// Copy files.
			for (auto const &i : files)
			{
				auto newDstFullpath = dstPath + strTrimLeft(i, srcParentPath);
				CopyFile(i.c_str(), newDstFullpath.c_str(), FALSE);
			}
		}
		else
		{ /* Bad combination */ }
	}
	else
	{ /* Bad combination */ }

	return true;
}
bool CreateDir(const PathParser &path)
{
	string toCreate;
	for (auto const &i : strSplit(strTrimRight(path.m_path, "\\"), '\\'))
	{
		toCreate += i + "\\";
		CreateDirectory(toCreate.c_str(), nullptr);
	}

	return true;
}
bool Del(const PathParser &dst)
{
	// 
	list<string> fileToDel, dirToDel;
	(dst.m_type != PathParser::Type::Dir ? fileToDel : dirToDel).push_back(dst.m_path);

	for (list<string>::iterator it = dirToDel.begin(); it != dirToDel.end(); ++it)
	{
		// 
		WIN32_FIND_DATA wfd = {};
		auto hFind = FindFirstFile((*it + "*").c_str(), &wfd);
		if (hFind != INVALID_HANDLE_VALUE)
		{
			do 
			{
				if (string(wfd.cFileName) != "."
					&& string(wfd.cFileName) != "..")
				{
					string newDst = *it + wfd.cFileName;
					if (fn_isDir(newDst))
					{
						// New dir.
						string path = strMakeRight(newDst, "\\");
						dirToDel.push_back(path);
					}
					else
					{
						// New file.
						fileToDel.push_back(newDst);
					}
				}
			} while (FindNextFile(hFind, &wfd));

			FindClose(hFind);
		}
	}

	// Delete file first.
	for (auto const &i : fileToDel)
	{
		DeleteFile(i.c_str());
	}
	// Delete directory from sub-directory to parent-directory.
	for (auto it = dirToDel.crbegin(); it != dirToDel.crend(); ++it)
	{
		RemoveDirectory(it->c_str());
	}

	return true;
}