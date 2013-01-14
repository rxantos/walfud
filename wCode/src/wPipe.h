

// wPipe.h
//

#ifndef W_PIPE_H
#define W_PIPE_H

#include "wCppExt.h"

namespace w
{

class Pipe
{
public:
	Pipe();
	virtual ~Pipe();
public:
	// Interface.
	virtual unsigned read(void *buf, unsigned size) = 0;
	virtual unsigned write(void *buf, unsigned size) = 0;
};


/*
 *
 *	Feature:
 *		1. Each pipe is unique. Use 'DuplicateHandle()' to get handle.
 *		2. Only support Synchronous I/O.
 *		3. Only support local communication.
 *
 */
	//////////////////////////////////
	// read.exe
	//////////////////////////////////

	//w::AnonymousPipe ap;

	//STARTUPINFO si = {};
	//si.cb = sizeof(STARTUPINFO); 
	//si.hStdOutput = ap.getWritePipe();
	//si.hStdInput = ap.getReadPipe();
	//si.dwFlags |= STARTF_USESTDHANDLES;
	//PROCESS_INFORMATION pi = {};
	//int r = CreateProcess("write.exe", nullptr, nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi);

	//while (true)
	//{
	//	char buf[1024] = {};
	//	ap.read(buf, 6);
	//	cout <<"read: " <<buf <<endl;
	//}

	//////////////////////////////////
	// write.exe
	//////////////////////////////////
	//HANDLE read = GetStdHandle(STD_INPUT_HANDLE),
	//	   write = GetStdHandle(STD_OUTPUT_HANDLE);

	//w::AnonymousPipe ap(read, write);
	//while (true)
	//{
	//	ap.write("12345", 6);
	//	OutputDebugString(".");

	//	Sleep(1000);
	//}
class AnonymousPipe : public Pipe
{
	// data.
	HANDLE m_read, m_write;

public:
	AnonymousPipe();								// Creator.
	AnonymousPipe(HANDLE read, HANDLE write);		// Connector.
	virtual ~AnonymousPipe();
private:
	AnonymousPipe(const AnonymousPipe &other);
	AnonymousPipe &operator=(const AnonymousPipe &other);
public:
	// Interface.
	virtual unsigned read(void *buf, unsigned size);
	virtual unsigned write(void *buf, unsigned size);

	HANDLE getReadPipe() const;
	HANDLE getWritePipe() const;

private:
	// logic.
};


/*
 *
 *	Feature:
 *		Pipe names are NOT case sensitive. And can NOT contains '\'.
 *		Create message type can be read by both message type and byte type; create byte type only can be read as byte type.
 *
 *	Note:
 *		Message mode is read and write as different unit; byte mode treats all data in buffer as a whole stream. See my blog: TODO: .
 *
 */
class NamedPipe
{
protected:
	// data.
	HANDLE m_pipe;
	static const unsigned ms_maxBufSize = 4 * 1024;

public:
	NamedPipe(const std::string &name, bool isClient = false, bool messageMode = false, bool async = false);
	virtual ~NamedPipe();
public:
	// Interface.
	virtual unsigned read(void *buf, unsigned size) = 0;
	virtual unsigned write(void *buf, unsigned size) = 0;
};

class SyncPipe : public NamedPipe
{
public:
	SyncPipe(const std::string &name, bool isClient = false, bool messageMode = false);
	virtual ~SyncPipe();
public:
	// Interface.
	virtual unsigned read(void *buf, unsigned size);
	virtual unsigned write(void *buf, unsigned size);
};

class ASyncPipe : public NamedPipe
{
	// data.
	std::packaged_task<void (void *)> m_readWorker, m_writeWorker;
	std::function<void (void *)> m_connectCallback, m_readCallback, m_writeCallback;

	bool m_quit;

public:
	ASyncPipe(const std::string &name, bool isClient = false, bool messageMode = false,
			  std::function<void (void *)> connectCallback = nullptr,
			  std::function<void (void *)> readCallback = nullptr, std::function<void (void *)> writeCallback = nullptr);
	virtual ~ASyncPipe();
public:
	// Interface.
	virtual unsigned read(void *buf, unsigned size);
	virtual unsigned write(void *buf, unsigned size);
};
























//class SyncPipe : public NamedPipe
//{
//public:
//	SyncPipe(const std::string &name, bool create = true, bool messageMode = false);
//	virtual ~SyncPipe();
//public:
//	// Interface.
//	virtual unsigned read(void *buf, unsigned size);
//	virtual unsigned write(void *buf, unsigned size);
//};
//
//class ASyncPipe : public NamedPipe
//{
//	// data.
//	std::function<void (void *)> m_connectCallback, m_readCallback, m_writeCallback;
//
//public:
//	ASyncPipe(const std::string &name, bool create = true, bool messageMode = false, 
//			  const std::function<void (void *)> &connectCallback = nullptr, 
//			  const std::function<void (void *)> &readCallback = nullptr, const std::function<void (void *)> &writeCallback = nullptr);
//	virtual ~ASyncPipe();
//public:
//	// Interface.
//	virtual unsigned read(void *buf, unsigned size);
//	virtual unsigned write(void *buf, unsigned size);
//};

}

#endif // W_PIPE_H