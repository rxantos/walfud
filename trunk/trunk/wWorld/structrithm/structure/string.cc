
// string.cc
//

#include "string.h"
#include "../../infrastructure/exception.h"
#include "../../utils/convert.h"
#include <cstring>
#include <algorithm>

string::string() {}
string::~string()
{
	delete m_str;
	m_str = nullptr;
	m_len = 0;
}
string::string(const string &other)
{
	this->copy(other.m_str, other.m_len);
}
string::string(string &&other)
{
	this->swap(other.m_str, other.m_len);
}
string &string::operator=(const string &other)
{
	if (this != &other)
	{
		this->copy(other.m_str, other.m_len);
	}

	return *this;
}
string &string::operator=(string &&other)
{
	if (this != &other)
	{
		this->swap(other.m_str, other.m_len);
	}

	return *this;
}

string::string(const char c)
	: m_len(1)
{
	m_str = new char[m_len];
	m_str[0] = c;
}
string::string(const char *str)
{ this->copy(str, strlen(str)); }
string::string(const char *beg, const char *end)
{ this->copy(beg, end-beg); }
string::string(const int num)
	: string(intToStr(num, 10).c_str())
{}
string::string(const double num)
	: string(doubleToStr(num, 2).c_str())
{}

auto string::copy(const char *str, unsigned len) noexcept -> void
{
	// Allocate new space.
	char *tmp = new char[len];
	std::copy(str, str + len, tmp);

	// Acquire resource.
	this->swap(tmp, len);

	// Release old resource.
	delete []tmp;
	tmp = nullptr;
}
auto string::swap(char *&str, unsigned &len) noexcept -> void
{
	std::swap(m_str, str);
	std::swap(m_len, len);
}

// Interface.
auto string::pushFront(const string &toAdd) -> string &
{
	return doInsert(0, toAdd.m_str, toAdd.m_len);
}
auto string::insert(const unsigned from, const string &toAdd) -> string &
{
	return doInsert(from, toAdd.m_str, toAdd.m_len);
}
auto string::pushBack(const string &toAdd) -> string &
{
	return doInsert(m_len, toAdd.m_str, toAdd.m_len);
}

auto string::erase(const unsigned from, const unsigned to) -> string &
{
	if (from > to || to > m_len)
	{
		throw exception_range(0, from, to);
	}

	unsigned newLen = m_len - (to - from);
	char *newStr = new char[newLen];
	std::copy(m_str, m_str + from, newStr);
	std::copy(m_str + to, m_str + m_len, newStr + from);

	this->swap(newStr, newLen);

	delete []newStr;
	newStr = nullptr;
	newLen = 0;

	return *this;
}
auto string::trimLeft(const string &toAdd) -> string &
{
	while (find(0, toAdd) == 0)
	{
		erase(0, toAdd.m_len);
	}

	return *this;
}
auto string::trimRight(const string &toAdd) -> string &
{
	while (find(m_len - toAdd.m_len, toAdd) == m_len-toAdd.m_len)
	{
		erase(m_len - toAdd.m_len, m_len);
	}

	return *this;
}
auto string::replace(const string &oldStr, const string &newStr) -> string &
{
	unsigned i = 0;
	while ((i = find(0, oldStr)) != m_len)
	{
		erase(i, i + oldStr.m_len);
		insert(i, newStr);
	}

	return *this;
}

auto string::subStr(const unsigned from, const unsigned to) const -> string
{
	if (from > to || to > m_len)
	{
		throw exception_range(0, from, to);
	}

	return string(m_str + from, m_str + to);
}
auto string::split(const string &delim) const -> std::vector<string> 
{
	std::vector<string> res;

	unsigned i = 0, j = 0;
	do
	{
		j = find(i, delim); 	// From 'i', find the delimiter.
		res.push_back(subStr(i, j));

		i = j + delim.m_len;	// Next place where to begins with 
								// is current delimiter forward the 
								// length of delimiter.
	} while (i < m_len);

	return res;
}

auto string::reverse() -> string &
{
	for (unsigned i = 0; i < m_len/2; ++i)
	{
		std::swap(m_str[i], m_str[m_len-1-i]);
	}

	return *this;
}

auto string::find(const char c) const -> unsigned
{ return find(0, c); }
auto string::find(unsigned from, const char c) const -> unsigned
{
	if (from > m_len)
	{
		// Range exam.
		throw exception_range(from, 0, m_len);
	}

	// If non-exists that character, return the position after tail character.
	// Index goes from zero.
	unsigned pos = m_len;
	for (unsigned i = from; i <= m_len; ++i)
	{
		if (m_str[i] == c)
		{
			pos = i;
			break;
		}
	}
	
	return pos;
}
auto string::find(const string &subStr) const -> unsigned
{ return find(0, subStr); }
auto string::find(unsigned from, const string &subStr) const -> unsigned
{
	if (from > m_len)
	{
		throw exception_range(from, 0, m_len);
	}

	const unsigned subLen = subStr.m_len;
	unsigned pos = m_len;
	for (unsigned i = from; i + subLen <= m_len; ++i)
	{
		if (std::equal(subStr.m_str, subStr.m_str + subLen, m_str + i))
		{
			pos = i;
			break;
		}
	}

	return pos;
}

auto string::alloc(const unsigned byteLen) -> void
{}
auto string::clear() -> void
{
	delete []m_str;
	m_str = nullptr;
	m_len = 0;
}

// State.
auto string::len() const -> unsigned
{ return m_len; }

// Output.
auto string::print(std::ostream &o) const -> std::ostream &
{
	std::for_each(m_str, m_str + m_len, [&](const char c) -> void { o <<c; });
	return o ;
}

// logic.
auto string::doInsert(const unsigned from, 
					  const char *str, const unsigned len) -> string &
{
	if (from > m_len)
	{
		// 'from' should between '[0, from]'.
		throw exception_range(from, 0, m_len);
	}

	unsigned newLen = m_len + len;
	char *newStr = new char[newLen];

	std::copy(m_str, m_str + from, newStr);
	std::copy(str, str + len, newStr + from);
	std::copy(m_str + from, m_str + m_len, newStr + from + len);

	this->swap(newStr, newLen);

	delete []newStr;
	newStr = nullptr;
	newLen = 0;

	return *this;
}

////////////////////////////////////////////////////////////////////////////////
auto operator+(const string &x, const string &y) -> string
{ return string(x).pushBack(y); }
auto operator+=(string &x, const string &y) -> string &
{ return x.pushBack(y); }

auto operator<<(std::ostream &o, const string &str) -> std::ostream &
{ return str.print(o); }
