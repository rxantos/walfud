

// animation.cpp
//

#include "animation.h"
#include <future>
using namespace std;
using namespace this_thread;
using namespace chrono;

// MyAnimation.
MyAnimation::MyAnimation() 
	: m_graph1(nullptr, RGB(123, 62, 200)), m_graph2(nullptr, RGB(240, 240, 240)), 
	  m_track1(), m_track2(),
	  m_speed(),
	  m_cv1(), m_cv2(), m_lock(), m_b1(false), m_b2(false)
{}

// Interface.
void MyAnimation::setBoard(HWND drawHWnd) 
{
	m_graph1.setDC(GetDC(drawHWnd));
	m_graph2.setDC(GetDC(drawHWnd));
}

// impl.
void MyAnimation::start()
{
	call_once(m_initFlag, &MyAnimation::init, this);

	// Start animate.
	{
		lock_guard<mutex> lg(m_lock);
		m_b1 = true;
	}
	m_cv1.notify_one();

	call_once(m_distanceFlag, []{ sleep_for(seconds(1)); });

	{
		lock_guard<mutex> lg(m_lock);
		m_b2 = true;
	}
	m_cv2.notify_one();
}
void MyAnimation::stop()
{
	// TODO: Clear board.
}
void MyAnimation::pause()
{
	// Pause animate.
	{
		lock_guard<mutex> lg(m_lock);
		m_b1 = m_b2 = false;
	}
}

void MyAnimation::init()
{
	async(&MyAnimation::animation1, this);
	async(&MyAnimation::animation2, this);
}
void MyAnimation::animation1()
{
	// Animation 1.
	animationBase(m_graph1, m_track1, m_speed, m_lock, m_b1, m_cv1);
}
void MyAnimation::animation2()
{
	// Animation 2.
	animationBase(m_graph2, m_track2, m_speed, m_lock, m_b2, m_cv2);
}
void MyAnimation::animationBase(MyGraph &g, MyTrack &mt, Speed &s, mutex &l, bool &b, condition_variable &cv)
{
	while (true)
	{
		{
			unique_lock<mutex> ul(l);
			cv.wait(ul, [&b](){ return b; });
		}

		Coordinate_2D pos = mt.next();
		g.setCoordinate(pos);

		g.draw();

		sleep_for(milliseconds(s.next()));
	}
}