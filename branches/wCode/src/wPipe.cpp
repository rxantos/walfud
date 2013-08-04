

// wPipe.cc
//

#include "wPipe.h"
using namespace std;

namespace w
{

Pipe::Pipe()
{}
Pipe::~Pipe()
{}

// AnonymousPipe.
AnonymousPipe::AnonymousPipe()
{
	SECURITY_ATTRIBUTES sa = {};
	sa.nLength = sizeof(sa);
	sa.bInheritHandle = TRUE;

	CreatePipe(&m_read, &m_write, &sa, 0);
}
AnonymousPipe::AnonymousPipe(HANDLE read, HANDLE write)
	: m_read(read), m_write(write)
{}
AnonymousPipe::~AnonymousPipe()
{ CloseHandle(m_read), CloseHandle(m_write); }

// Interface.
unsigned AnonymousPipe::read(void *buf, unsigned size)
{
	DWORD readSize = 0;
	ReadFile(m_read, buf, size, &readSize, nullptr);

	return static_cast<unsigned>(readSize);
}
unsigned AnonymousPipe::write(void *buf, unsigned size)
{
	DWORD writeSize = 0;
	WriteFile(m_write, buf, size, &writeSize, nullptr);

	return static_cast<unsigned>(writeSize);
}

HANDLE AnonymousPipe::getReadPipe() const
{ return m_read; }
HANDLE AnonymousPipe::getWritePipe() const
{ return m_write; }

// NamedPipe.
NamedPipe::NamedPipe() : m_pipe(nullptr) {}
NamedPipe::~NamedPipe() {}

// SyncPipe.
SyncPipe::SyncPipe(const string &name, bool isClient, bool messageMode)
	: NamedPipe()
{
	const string pipeName = "\\\\.\\pipe\\" + name;			// TODO: R"(\\.\pipe\)".

	if (isClient)
	{
		m_pipe = CreateFile(pipeName.c_str(), 
							GENERIC_READ | GENERIC_WRITE, 
							FILE_SHARE_READ | FILE_SHARE_WRITE, 
							nullptr, 
							OPEN_EXISTING, 
							0, 
							nullptr);

		DWORD mode = (messageMode ? PIPE_READMODE_MESSAGE : PIPE_READMODE_BYTE)
					 | PIPE_WAIT;
		SetNamedPipeHandleState(m_pipe, &mode, nullptr, nullptr);
	}
	else
	{
		DWORD mode = (messageMode ? PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE : PIPE_TYPE_BYTE | PIPE_READMODE_BYTE)
					 | PIPE_WAIT;

		m_pipe = CreateNamedPipe(pipeName.c_str(), 
								 PIPE_ACCESS_DUPLEX, 
								 mode, 
								 PIPE_UNLIMITED_INSTANCES, 
								 ms_maxBufSize, ms_maxBufSize,
								 INFINITE, 
								 nullptr);

		ConnectNamedPipe(m_pipe, nullptr);
	}
}
SyncPipe::~SyncPipe()
{
	//FlushFileBuffers(m_pipe);		// Do NOT wait client to read finish.
	DisconnectNamedPipe(m_pipe);
	CloseHandle(m_pipe);
}

// Interface.
unsigned SyncPipe::read(void *buf, unsigned size)
{
	DWORD readSize = 0;
	ReadFile(m_pipe, buf, size, &readSize, nullptr);

	return static_cast<unsigned>(readSize);
}
unsigned SyncPipe::write(void *buf, unsigned size)
{
	DWORD writeSize = 0;
	WriteFile(m_pipe, buf, size, &writeSize, nullptr);

	return static_cast<unsigned>(writeSize);
}

}