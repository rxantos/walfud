

// wSync.cc
//

#include "wSync.h"
using namespace std;

namespace w
{

Mutex::Mutex(const string &name)
{
	m_mutexHandle = CreateMutex(nullptr, FALSE, name.c_str());
}
Mutex::~Mutex()
{
	CloseHandle(m_mutexHandle);
}

// Interface.
void Mutex::p(unsigned timeout)
{ WaitForSingleObject(m_mutexHandle, timeout); }
void Mutex::v()
{ ReleaseMutex(m_mutexHandle); }

}