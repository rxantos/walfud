

// speed.h
//

#ifndef SPEED_H
#define SPEED_H

class Speed
{
protected:
	// data.

public:
	virtual ~Speed() {}

public:
	// Interface.
	virtual unsigned prev() = 0;
	virtual unsigned next() = 0;
	virtual unsigned reset() = 0;

	virtual Speed *clone() const = 0;

protected:
	// logic.
};

class MySpeed : public Speed
{
protected:
	// data.
	unsigned m_var;

public:
	MySpeed();
	virtual ~MySpeed();

public:
	// Interface.
	virtual unsigned prev();
	virtual unsigned next();
	virtual unsigned reset();

	virtual Speed *clone() const override { auto _type(*this); return new decltype(_type)(*this); }

protected:
	// logic.
};

class MySpeed2 : public MySpeed
{
public:
	// Interface.
	virtual unsigned next();

	virtual Speed *clone() const override { auto _type(*this); return new decltype(_type)(*this); }
};

#endif // SPEED_H