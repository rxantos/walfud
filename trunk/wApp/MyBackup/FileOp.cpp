

// FileOp.cpp
//

#include "stdafx.h"
#include "FileOp.h"
using namespace std;
using namespace w;

bool Copy(const PathParser &src, const PathParser &dst)
{
	if (false)
	{ /* Stub */ }
	else if (src.m_type == PathParser::Type::File)
	{
		auto srcPath = src.m_path, dstPath = dst.m_path;

		if (false)
		{}
		else if (dst.m_type == PathParser::Type::File)
		{
			// File -> File.
		}
		else if (dst.m_type == PathParser::Type::Dir)
		{
			// File -> Dir.
			// Append file name at the end of `dstPath`.
			dstPath += PathFindFileName(srcPath.c_str());
		}
		else
		{}
	}
	else if (src.m_type == PathParser::Type::Dir)
	{
		if (dst.m_type == PathParser::Type::Dir)
		{
			// Dir -> Dir.
		}
	}
	else
	{ /* Bad combination */ }

	return true;
}
bool CreateDir(const PathParser &path)
{
	return true;
}
bool Del(const PathParser &dst)
{
	return true;
}