

// animation.cpp
//

#include "animation.h"
#include <thread>
#include <chrono>
using namespace std;
using namespace this_thread;
using namespace chrono;

// MyAnimation.
MyAnimation::MyAnimation() 
	: m_board(nullptr),
	  m_dc(nullptr),
	  m_g(nullptr), 
	  m_t(nullptr),
	  m_s(nullptr),
	  m_cv(), m_lock(), m_b(false),
	  m_quit(false)
{}
MyAnimation::~MyAnimation() { stop(true); }

// Interface.
void MyAnimation::setBoard(HWND drawHWnd) 
{
	ReleaseDC(m_board, m_dc);
	m_board = drawHWnd;	
	m_dc = GetDC(drawHWnd);
}

// impl.
void MyAnimation::start()
{
	// Create working thread.
	m_quit = false;
	m_b = false;

	if (!m_w.valid())
	{
		m_w = async(&MyAnimation::animation, this);
	}

	// Start.
	{
		lock_guard<mutex> lg(m_lock);
		m_b = true;
	}
	m_cv.notify_one();
}
void MyAnimation::stop(bool waitDone)
{
	// Quit working thread.
	m_quit = true;
	{
		lock_guard<mutex> lg(m_lock);
		m_b = true;
	}

	m_cv.notify_one();
	if (waitDone)
	{
		// Wait the animation done.
		if (m_w.valid())
		{
			// Reset the animation worker.
			m_w.get();
		}
	}
}
void MyAnimation::pause()
{
	// Pause animate.
	{
		lock_guard<mutex> lg(m_lock);
		m_b = false;
	}
}

void MyAnimation::clear() { InvalidateRect(m_board, nullptr, TRUE); }

void MyAnimation::animation()
{
	// Animation.
	while (true)
	{
		{
			unique_lock<mutex> ul(m_lock);
			m_cv.wait(ul, [&](){ return m_b; });
		}
		if (m_quit)
		{
			// thread quit.
			break;
		}

		Coordinate_2D pos = m_t->next();
		m_g->setCoordinate(pos);

		m_g->draw(m_dc);

		sleep_for(milliseconds(m_s->next()));
	}
}

// MyAnimation2.
void MyAnimation2::setDoneCallback(function<void (void *)> cb, void *param)
{
	m_cycleDoneCallback = cb; 
	m_cbParam = param;
}

// logic.
void MyAnimation2::animation()
{
	// Begin animation.
	while (true)
	{
		{
			unique_lock<mutex> ul(m_lock);
			m_cv.wait(ul, [&](){ return m_b; });
		}
		if (m_quit)
		{
			// Thread quit.
			break;
		}

		// Draw current image.
		Coordinate_2D pos = m_t->next();
		m_g->setCoordinate(pos);
		m_g->draw(m_dc);
		sleep_for(milliseconds(m_s->next()));

		// Cycle done callback.
		if (m_t->isCycleDone())
		{
			// When a cycle is done.
			if (m_cycleDoneCallback)
			{
				m_cycleDoneCallback(m_cbParam);
			}
		}
	}
}