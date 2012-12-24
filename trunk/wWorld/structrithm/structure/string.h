

// string.h
//

#ifndef STRING_H
#define STRING_H

#include <ostream>
#include <vector>

/*
 *
 * Note:
 * 		All index operation begin with zero.
 *
 * **/
class string
{
	char *m_str = nullptr;
	unsigned m_len = 0;
public:
	string();
	~string();
	string(const string &other);
	string(string &&other);
	auto operator=(const string &other) -> string &;
	auto operator=(string &&other) -> string &;

	string(const char c);
	string(const char *str);
	string(const char *beg, const char *end);
	string(const int num);
	string(const double num);
protected:
	string(const char *str, const unsigned len);

	auto copy(const char *str, const unsigned len) noexcept -> void;
	auto swap(char *&str, unsigned &len) noexcept -> void;

public:
	// Interface.

	// Basic operation.
	auto pushFront(const char c) -> string &;
	auto pushFront(const int num) -> string &;
	auto pushFront(const double num) -> string &;
	auto pushFront(const string &toAdd) -> string &;
	auto insert(const unsigned from, const char c) -> string &;
	auto insert(const unsigned from, const int num) -> string &;
	auto insert(const unsigned from, const double num) -> string &;
	auto insert(const unsigned from, const string &toAdd) -> string &;
	auto pushBack(const char c) -> string &;
	auto pushBack(const int num) -> string &;
	auto pushBack(const double num) -> string &;
	auto pushBack(const string &toAdd) -> string &;

	auto erase(const unsigned from, const unsigned to) -> string &;
	auto trimLeft(const string &toDel) -> string &;
	auto trimRight(const string &toDel) -> string &;
	auto replace(const string &oldStr, const string &newStr) -> string &;

	auto find(const char c) const -> unsigned;
	auto find(unsigned from, const char c) const -> unsigned;
	auto find(const string &subStr) const -> unsigned;
	auto find(unsigned from, const string &subStr) const -> unsigned;

	auto reverse() -> string &;

	auto subStr(const unsigned from, const unsigned to) const -> string;
	auto split(const string &delim) const -> std::vector<string>;

	auto alloc(const unsigned byteLen) -> void;
	auto clear() -> void;

	// State.
	auto isEmpty() const -> bool;
	auto len() const -> unsigned;

	// Output.
	auto print(std::ostream &o) const -> std::ostream &;
	
private:
	// logic.
	auto doInsert(const unsigned from, 
				  const char *str, const unsigned len) -> string &;
};

////////////////////////////////////////////////////////////////////////////////
auto operator+(const string &x, const string &y) -> string;
auto operator+=(string &x, const string &y) -> string &;

auto operator<<(std::ostream &o, const string &str) -> std::ostream &;

#endif // STRING_H
