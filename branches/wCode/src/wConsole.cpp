

// wConsole.h
// 

#include "wConsole.h"
using namespace std;

namespace w
{

// Console.
Console::Console()
	: m_insFunc(), m_insExec()
{}
Console::~Console()
{}
// Interface.
void Console::add(string const &ins, function<void (void *)> func, void *param)
{ m_insFunc[ins] = make_pair(func, param); }
void Console::add(string const &ins, string const &exec, string const &param)
{ m_insExec[ins] = make_pair(exec, param); }
void Console::remove(string const &ins)
{
	m_insFunc.erase(ins);
	m_insExec.erase(ins);
}

void Console::parse(string const &line)
{ call(line, true); }

void Console::run()
{
	while (isRunning())
	{
		string line;
		getline(cin, line);

		parse(line);
	}
}

// logic.
bool Console::isRunning() const
{ return false; }

void Console::call(string const &ins, bool sync)
{
	auto func = m_insFunc.find(ins);
	if (func != m_insFunc.end())
	{
		auto task = async(func->second.first, func->second.second);

		if (sync)
		{
			task.get();
		}
	}

	auto exec = m_insExec.find(ins);
	if (exec != m_insExec.end())
	{
		auto task = async(system, (exec->second.first + " " + exec->second.second).c_str());

		if (sync)
		{
			task.get();
		}
	}
}

// MyConsole.
MyConsole::MyConsole()
	: m_running(true)
{
	// Steup basic instruction.
	add("quit", bind(&MyConsole::quit, this));
}
MyConsole::~MyConsole()
{}
// Interface.
void MyConsole::parse(string const &line)
{
	Console::call(line, true);
}

void MyConsole::quit()
{ m_running = false; }

// logic.
bool MyConsole::isRunning() const
{ return m_running; }

}