

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
NamedPipe::NamedPipe(const string &name, bool isClient, bool messageMode, bool async)
{
	const string pipeName = "\\\\.\\pipe\\" + name;			// TODO: R"(\\.\pipe\)".

	DWORD mode = 0;

	if (isClient)
	{
		m_pipe = CreateFile(pipeName.c_str(), 
							GENERIC_READ | GENERIC_WRITE, 
							FILE_SHARE_READ | FILE_SHARE_WRITE, 
							nullptr, 
							OPEN_EXISTING, 
							0, 
							nullptr);

		mode = (messageMode ? PIPE_READMODE_MESSAGE : PIPE_READMODE_BYTE)
			   | PIPE_WAIT;
		SetNamedPipeHandleState(m_pipe, &mode, nullptr, nullptr);
	}
	else
	{
		mode = (messageMode ? PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE : PIPE_TYPE_BYTE | PIPE_READMODE_BYTE)
			   | PIPE_WAIT;
		m_pipe = CreateNamedPipe(pipeName.c_str(), 
								 PIPE_ACCESS_DUPLEX | (async ? FILE_FLAG_OVERLAPPED : 0), 
								 mode, 
								 PIPE_UNLIMITED_INSTANCES, 
								 ms_maxBufSize, ms_maxBufSize,
								 INFINITE, 
								 nullptr);
	}
}
NamedPipe::~NamedPipe()
{
	//FlushFileBuffers(m_pipe);		// Do NOT wait client to read finish.
	DisconnectNamedPipe(m_pipe);
	CloseHandle(m_pipe);
}

// SyncPipe.
SyncPipe::SyncPipe(const string &name, bool isClient, bool messageMode)
	: NamedPipe(name, isClient, messageMode, false)
{
	if (!isClient)
	{
		ConnectNamedPipe(m_pipe, nullptr);
	}
}
SyncPipe::~SyncPipe()
{}

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

// ASyncPipe.
ASyncPipe::ASyncPipe(const string &name, bool isClient, bool messageMode, 
					 function<void (void *)> connectCallback, 
					 function<void (void *)> readCallback, function<void (void *)> writeCallback)
	: NamedPipe(name, isClient, messageMode, false),
	  m_readWorker(nullptr), m_writeWorker(nullptr),
	  m_connectCallback(connectCallback), m_readCallback(readCallback), m_writeCallback(writeCallback),
	  m_quit(false)
{
	// Setup worker.
	m_readWorker = packaged_task<void (void *)>([](void *param) -> void
	{
		ASyncPipe *p = reinterpret_cast<ASyncPipe *>(param);

		
	});
	//m_writeWorker = [](void *param) -> void
	//{};

	if (!isClient)
	{
		ConnectNamedPipe(m_pipe, nullptr);
	}
}
ASyncPipe::~ASyncPipe()
{}

// Interface.
unsigned ASyncPipe::read(void *buf, unsigned size)
{
	return 0;
}
unsigned ASyncPipe::write(void *buf, unsigned size)
{
	return 0;
}









//
//// ASyncPipe.
//ASyncPipe::ASyncPipe(const string &name, bool create, bool messageMode, 
//					 const function<void (void *)> &connectCallback, 
//					 const function<void (void *)> &readCallback, const function<void (void *)> &writeCallback)
//	: NamedPipe(name, create, messageMode, true), 
//	  m_connectCallback(connectCallback), m_readCallback(readCallback), m_writeCallback(writeCallback)
//{
//	async([](ASyncPipe *param) -> void
//		{
//			ConnectNamedPipe(param->m_pipe, nullptr);
//
//			if (param->m_connectCallback)
//			{
//				param->m_connectCallback(nullptr);
//			}
//		}, this);
//}
//ASyncPipe::~ASyncPipe()
//{}
//
//// Interface.
//unsigned ASyncPipe::read(void *buf, unsigned size)
//{
//	DWORD readSize = 0;
//
//	async(
//		[this, &buf, &size, &readSize]() -> void
//		{
//			ReadFile(m_pipe, buf, size, &readSize, nullptr);
//
//			if (m_readCallback)
//			{
//				m_readCallback(const_cast<pair<void *, unsigned> *>(&make_pair(buf, static_cast<unsigned>(readSize))));
//			}
//		});
//
//	return 0;
//}
//unsigned ASyncPipe::write(void *buf, unsigned size)
//{
//	DWORD writeSize = 0;
//
//	thread t(
//		[this, &buf, &size, &writeSize]() -> void
//		{
//			WriteFile(m_pipe, buf, size, &writeSize, nullptr);
//
//			if (m_readCallback)
//			{
//				m_writeCallback(const_cast<pair<void *, unsigned> *>(&make_pair(buf, static_cast<unsigned>(writeSize))));
//			}
//		});
//	t.detach();
//
//	return static_cast<unsigned>(writeSize);
//}

}