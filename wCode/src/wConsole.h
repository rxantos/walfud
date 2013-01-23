

// wConsole.h
// 

#ifndef W_CONSOLE_H
#define W_CONSOLE_H

#include "wCppExt.h"

namespace w
{

class Console
{
	// data.
	std::map<std::string, std::pair<std::function<void (void *)>, void *>> m_insFunc;		// Instruction-Function map.
	std::map<std::string, std::pair<std::string, std::string>> m_insExec;						// Instruction-Executable map.

public:
	Console();
	virtual ~Console();
private:
	Console(Console const &other);
	Console &operator=(Console const &other);
	Console(Console &&other);
	Console &operator=(Console &&other);
public:
	// Interface.
	void add(std::string const &ins, std::function<void (void *)> func, void *param = nullptr);
	void add(std::string const &ins, std::string const &exec, std::string const &param = "");
	void remove(std::string const &ins);

	virtual void parse(std::string const &line);

	void run();
	
protected:
	// logic.
	virtual bool isRunning() const;

	void call(std::string const &ins, bool sync = true);
};

class MyConsole : public Console
{
	// data.
	bool m_running;

public:
	MyConsole();
	virtual ~MyConsole();
public:
	// Interface.
	virtual void parse(std::string const &line) override;

	void quit();

protected:
	// logic.
	virtual bool isRunning() const override;
};

}

#endif // W_CONSOLE_H