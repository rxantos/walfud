

// Brightness.h
//

#ifndef W_BRIGHTNESS_H
#define W_BRIGHTNESS_H

#define _USE_MATH_DEFINES

#include <ctime>
#include <string>
#include <vector>

class Brightness
{
protected:
	// data.

public:
	virtual ~Brightness() {}

public:
	// Interface.
	virtual unsigned getVal() = 0;		// Get the corresponding brightness value.

protected:
	// logic.
};

class MyBrightness : public Brightness
{
	// data.

public:
	MyBrightness();
	virtual ~MyBrightness();

public:
	// Interface.
	virtual unsigned getVal();

private:
	// logic.
	time_t getSecond();
};

#endif // W_BRIGHTNESS_H