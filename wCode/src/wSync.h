

// wSync.h
//

#ifndef W_SYNC_H
#define W_SYNC_H

#include "wCppExt.h"

namespace w
{

/*
 *
 *	Note:
 *		Empty string for default constructor is anonymous mutex.(Each mutex is different)
 *
 */
class Mutex
{
	// data.
	HANDLE m_mutexHandle;

public:
	Mutex(const std::string &name = "");
	~Mutex();
private:
	Mutex(const Mutex &other);
	Mutex &operator=(const Mutex &other);
public:
	// Interface.
	void p(unsigned timeout = INFINITE);
	void v();

private:
	// logic.
};

}

#endif // W_SYNC_H