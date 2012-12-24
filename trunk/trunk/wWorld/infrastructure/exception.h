

// exception.h
// 

#ifndef EXCEPTION_H
#define EXCEPTION_H

#include "infrastructureConst.h"
#include <string>
#include "../utils/convert.h"

class exception
{
public:
	exception() : exception("unknown.") {}
	exception(const std::string &reason) : m_reason(reason) {}
	virtual ~exception(){}
public:
	// Interface.
	std::string why() const { return m_reason; }

protected:
	// data.
	std::string m_reason;
};

////////////////////////////////////////////////////////////////////////////////
class exception_memory : public exception
{
public:
	exception_memory(){}
	~exception_memory(){}
};

class exception_overflow : public exception
{
public:
	exception_overflow(){}
	~exception_overflow(){}
	exception_overflow(const int num)
		: exception() 
	{ m_reason = std::string("overflow: '") + intToStr(num, 10) + "'."; }
	exception_overflow(const std::string &num) 
		: exception("overflow: '" + num + "'.") {}
};

class exception_range : public exception
{
public:
	exception_range(){}
	~exception_range(){}
	exception_range(const int num, const int lowerBound, const int upperBound)
		: exception() 
	{ m_reason = std::string("range: '") + intToStr(num, 10) + "' out of [" 
				 + intToStr(lowerBound, 10) + ", "  + intToStr(upperBound, 10) 
				 + ")."; }
};

class exception_argument : public exception
{
public:
	exception_argument(){}
	~exception_argument(){}
	exception_argument(const std::string &reason)
		: exception("invalid argument: '" + reason + "'.") {}
};

#endif // EXCEPTION_H
