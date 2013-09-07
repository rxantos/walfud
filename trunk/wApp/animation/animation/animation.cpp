

// animation.cpp
//

#include "animation.h"
#include <future>
using namespace std;
using namespace this_thread;
using namespace chrono;

// MyAnimation.
MyAnimation::MyAnimation() 
	: m_board(nullptr),
	  m_dc(nullptr),
	  m_init(false),
	  m_cv1(), m_cv2(), m_lock(), m_b1(false), m_b2(false),
	  m_quit(false)
{}
MyAnimation::~MyAnimation() { stop(); }

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
	if (!m_init)
	{
		m_quit = false;
		m_b1 = false;
		m_w1 = async(&MyAnimation::animation1, this);
		m_b2 = false;
		m_w2 = async(&MyAnimation::animation2, this);
	}

	// Start line 1.
	{
		lock_guard<mutex> lg(m_lock);
		m_b1 = true;
	}
	m_cv1.notify_one();

	// Wait.
	if (!m_init)
	{
		sleep_for(seconds(1));
	}

	// Start line 2.
	{
		lock_guard<mutex> lg(m_lock);
		m_b2 = true;
	}
	m_cv2.notify_one();

	// Refresh status.
	m_init = true;
}
void MyAnimation::stop()
{
	if (m_init)
	{
		// Clean board.
		InvalidateRect(m_board, nullptr, TRUE);

		// Quit working thread.
		m_quit = true;
		{
			lock_guard<mutex> lg(m_lock);
			m_b1 = true;
		}
		m_cv1.notify_one();
		m_w1.wait();
		{
			lock_guard<mutex> lg(m_lock);
			m_b2 = true;
		}
		m_cv2.notify_one();
		m_w2.wait();

		// Refresh status.
		m_init = false;
	}
}
void MyAnimation::pause()
{
	// Pause animate.
	{
		lock_guard<mutex> lg(m_lock);
		m_b1 = m_b2 = false;
	}
}

void MyAnimation::animation1()
{
	// Animation 1.
	animationBase(shared_ptr<Graph<Coordinate_2D>>(new MyGraph(m_dc, RGB(123, 62, 200))), 
				  shared_ptr<Track<Coordinate_2D>>(new MyTrack2), 
				  shared_ptr<Speed>(new MySpeed2), 
				  m_lock, m_b1, m_cv1, m_quit);
}
void MyAnimation::animation2()
{
	// Animation 2.
	animationBase(shared_ptr<Graph<Coordinate_2D>>(new MyGraph(m_dc, RGB(240, 240, 240))), 
				  shared_ptr<Track<Coordinate_2D>>(new MyTrack2), 
				  shared_ptr<Speed>(new MySpeed2), 
				  m_lock, m_b2, m_cv2, m_quit);
}
void MyAnimation::animationBase(shared_ptr<Graph<Coordinate_2D>> g, shared_ptr<Track<Coordinate_2D>> mt, shared_ptr<Speed> s, 
								mutex &l, bool &b, condition_variable &cv, atomic<bool> &q)
{
	while (true)
	{
		{
			unique_lock<mutex> ul(l);
			cv.wait(ul, [&b](){ return b; });
		}
		if (q)
		{
			// thread quit.
			break;
		}

		Coordinate_2D pos = mt->next();
		g->setCoordinate(pos);

		g->draw();

		sleep_for(milliseconds(s->next()));
	}
}

// MyAnimation2.