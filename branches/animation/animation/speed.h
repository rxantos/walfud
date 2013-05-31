

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

protected:
	// logic.
};

#endif // SPEED_H