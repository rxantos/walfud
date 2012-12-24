

// bit.h
//

#ifndef BIT_H
#define BIT_H

#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <functional>
#include "infrastructureConst.h"
#include "exception.h"


/*
 *
 *	'Base' == 2 means binary bit.
 *
 *
 * */
template <unsigned Base>
class bit_base
{
public:
	bit_base() : bit_base(0){}
	explicit bit_base(const int &val) noexcept : m_val(val) {}
	virtual ~bit_base() = default;

	bit_base(const bit_base &other) noexcept 
		: m_val(other.m_val) {}
	bit_base(bit_base &&other) noexcept 
		: m_val(std::move(other.m_val)) {}
	auto operator=(const bit_base &other) noexcept -> bit_base &
	{
		if (this != &other)
		{
			bit_base tmp(other);
			*this = std::move(tmp);
		}

		return *this;
	}
	auto operator=(bit_base &&other) noexcept -> bit_base &
	{
		if (this != &other)
		{
			std::swap(m_val, other.m_val);
		}

		return *this;
	}
public:
	// Interface.
	
	// Basic mathmatic.
	auto add(const bit_base &y) -> bit_base &
	{ 
		m_val = (m_val + y.m_val) % static_cast<int>(Base); 

		return *this;
	}
	auto sub(const bit_base &y) -> bit_base &
	{ 
		m_val = (m_val - y.m_val) % static_cast<int>(Base); 

		return *this;
	}
	auto mul(const bit_base &y) -> bit_base &
	{ 
		m_val = (m_val * y.m_val) % static_cast<int>(Base); 

		return *this;
	}
	auto div(const bit_base &y) -> bit_base &
	{ 
		m_val = (m_val / y.m_val) % static_cast<int>(Base); 

		return *this;
	}
	auto flip() -> bit_base &
	{ 
		m_val = -m_val; 

		return *this;
	}

	// Convert.
	auto toInt() const -> int
	{ return m_val; }

private:
	// logic.
	
public:
	// data.
	int m_val;
};
template <unsigned Base>
auto operator+(const bit_base<Base> &x, 
			   const bit_base<Base> &y) -> bit_base<Base> 
{ 
	bit_base<Base> z(x);
	z.add(y); 
	
	return z;
}
template <unsigned Base>
auto operator-(const bit_base<Base> &x, 
			   const bit_base<Base> &y) -> bit_base<Base> 
{ 
	bit_base<Base> z(x);
	z.sub(y); 
	
	return z;
}
template <unsigned Base>
auto operator*(const bit_base<Base> &x, 
			   const bit_base<Base> &y) -> bit_base<Base> 
{ 
	bit_base<Base> z(x);
	z.mul(y); 
	
	return z;
}
template <unsigned Base>
auto operator/(const bit_base<Base> &x, 
			   const bit_base<Base> &y) -> bit_base<Base> 
{ 
	bit_base<Base> z(x);
	z.div(y); 
	
	return z;
}

template <unsigned Base>
auto operator+=(bit_base<Base> &x, const bit_base<Base> &y) -> bit_base<Base>
{ return x.add(y); }
template <unsigned Base>
auto operator-=(bit_base<Base> &x, const bit_base<Base> &y) -> bit_base<Base>
{ return x.sub(y); }
template <unsigned Base>
auto operator*=(bit_base<Base> &x, const bit_base<Base> &y) -> bit_base<Base>
{ return x.mul(y); }
template <unsigned Base>
auto operator/=(bit_base<Base> &x, const bit_base<Base> &y) -> bit_base<Base>
{ return x.div(y); }


class bit : public bit_base<gc_bitBase>
{
public:
	bit() noexcept : bit_base() {}
	bit(const int &num) noexcept : bit_base()
	{
		std::ostringstream o;

		switch (num)
		{
		case -1:
			m_val = -1;
			break;
		case 0:
			m_val = 0;
			break;
		case 1:
			m_val = 1;
			break;
		default:
			o <<m_val;
			throw exception_overflow(o.str());
			break;
		}
	}
	bit(const char c) noexcept : bit_base()
	{
		std::ostringstream o;

		switch (c)
		{
		case '-':
			m_val = -1;
			break;
		case '0':
			m_val = 0;
			break;
		case '+':
			m_val = 1;
			break;
		default:
			o <<c;
			throw exception_argument(o.str());
			break;
		}
	}
	bit(const bit_base &base) noexcept : bit_base(base) {}
	virtual ~bit() noexcept = default;
	bit(const bit &other) noexcept : bit_base(other) {}
	bit(bit &&other) noexcept 
		: bit_base(std::forward<bit_base>(other)) {}
	auto operator=(const bit &other) -> bit &
	{ 
		bit tmp(other);
		return *this = std::move(tmp);
	}
	auto operator=(bit &&other) -> bit &
	{ 
		bit_base::operator=(std::forward<bit>(other));

		return *this; 
	}

public:
	// Interface.
	auto print(std::ostream &o) const -> std::ostream &
	{
		char c = '\0';
		switch (m_val)
		{
		case -1:
			c = '-';
			break;
		case 0:
			c = '0';
			break;
		case 1:
			c = '+';
			break;
		default:
			//thorw;
			break;
		}

		return o <<c;
	}

private:
	// logic.
private:
	// data.
};

auto operator<<(std::ostream &o, const bit &b) -> std::ostream & 
{ return b.print(o); }



////////////////////////////////////////////////////////////////////////////
/*
 *
 *		'bits' is a basic arithmethic unit.
 *
 **/
template <unsigned N>
class bits
{
public:
	bits() noexcept = default;
	explicit bits(int num) noexcept
	{
		// We treat positive number,
		// if 'num' is negative, just flip the result.
		bool needFlipRes = false;
		if (num < 0)
		{
			num = -num;
			needFlipRes = true;
		}

		for (unsigned i = 0; i < N; ++i)
		{
			m_bits[N-1-i] = (num >> i) & 1;
		}

		if (needFlipRes)
		{
			std::for_each(m_bits, m_bits + N, 
						  [](bit &b) -> void { b.flip(); });
		}

		overflowCheck(this->toInt());
	}
	explicit bits(const std::string &b) noexcept
	{
		unsigned i = 0;
		for (std::string::const_reverse_iterator it = b.rbegin(); 
			 it != b.rend() && i < N; ++it, ++i)
		{
			m_bits[N-1-i] = bit(*it);
		}

		overflowCheck(this->toInt());
	}
	~bits() noexcept = default;
	bits(const bits &other) noexcept
		: m_bits(other.m_bits)
	{}
	bits(bits &&other) noexcept
	{
		// Shift resources.
		std::move(other.m_bits, other.m_bits + N, m_bits);
	}
	auto operator=(const bits &other) noexcept -> bits &
	{
		if (this != &other)
		{
			bits tmp(other);
			*this = std::move(tmp);
		}
		
		return *this;
	}
	auto operator=(bits &&other) noexcept -> bits &
	{
		if (this != &other)
		{
			for (unsigned i = 0; i < N; ++i)
			{
				std::swap(m_bits[i], other.m_bits[i]);
			}
		}

		return *this;
	}
private:
	bits(const bit (&b)[N]) noexcept
	{
		std::copy(b, b + N, m_bits);
	}

public:
	// Interface.

	// Arithmetic.
	auto add(const bits &addend) -> bits &
	{ return *this = bits(overflowCheck(this->toInt() + addend.toInt())); }
	auto sub(const bits &subtrahend) -> bits &
	{ return *this = bits(overflowCheck(this->toInt() - subtrahend.toInt())); }
	auto mul(const bits &multiplier) -> bits &
	{ return *this = bits(overflowCheck(this->toInt() * multiplier.toInt())); }
	auto div(const bits &divisor) -> bits &
	{ return *this = bits(overflowCheck(this->toInt() / divisor.toInt())); }
	
	auto flip() -> void
	{ return *this = bits(-this->toInt()); }

	// Convert.
	auto toInt() const -> int
	{
		int res = 0;

		int power = 1;
		for (unsigned i = 0; i < N; ++i, power *= gc_bitBase)
		{
			res += m_bits[N-1-i].toInt() * power;
		}

		return res;
	}
	auto toStr() const -> std::string
	{
		char num[gc_byteCharsCnt] = L"";
		return std::string(itoa(toInt(), num, 10));
	}

	// Output.
	auto print(std::ostream &o) const -> std::ostream &
	{
		std::for_each(m_bits, m_bits + N, 
				 [&o](const bit &b) -> void { o <<b; });

		return o;
	}

private:
	// logic.
	inline int overflowCheck(const int num)
	{
		if (num <= -static_cast<int>(gc_byteMaxVal)
			|| static_cast<int>(gc_byteMaxVal) <= num)
		{
			throw exception_overflow(num);
		}

		return num;
	}
	
private:
	// data.
	bit m_bits[N];
};

/***/
using byte = bits<gc_byteBitsCnt>;
auto operator+(const byte &x, const byte &y) -> byte
{
	byte z(x);
	z.add(y);

	return z;
}
auto operator-(const byte &x, const byte &y) -> byte
{
	byte z(x);
	z.sub(y);

	return z;
}
auto operator*(const byte &x, const byte &y) -> byte
{
	byte z(x);
	z.mul(y);

	return z;
}
auto operator/(const byte &x, const byte &y) -> byte
{
	byte z(x);
	z.div(y);

	return z;
}

auto operator+=(byte &x, const byte &y) -> byte
{ return x.add(y); }
auto operator-=(byte &x, const byte &y) -> byte
{ return x.sub(y); }
auto operator*=(byte &x, const byte &y) -> byte
{ return x.mul(y); }
auto operator/=(byte &x, const byte &y) -> byte
{ return x.div(y); }

auto operator<<(std::ostream &o, const byte &b) -> std::ostream &
{ return b.print(o); }

#endif // BIT_H
