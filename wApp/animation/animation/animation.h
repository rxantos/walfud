

// animation.h
//

#ifndef ANIMATION_H
#define ANIMATION_H

#include "graph.h"
#include "track.h"
#include "speed.h"
#include <mutex>
#include <condition_variable>
#include <windows.h>

class Animation
{
public:
	virtual ~Animation() = 0 {}

public:
	// Interface.
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual void pause() = 0;
};

class MyAnimation : public Animation
{
	// data.
	MyGraph m_graph1, m_graph2;
	MyTrack2 m_track1, m_track2;
	MySpeed2 m_speed;

	std::once_flag m_initFlag, m_distanceFlag;
	std::condition_variable m_cv1, m_cv2;
	std::mutex m_lock;
	bool m_b1, m_b2;

public:
	MyAnimation();

public:
	// Interface.
	void setBoard(HWND drawHWnd);

	// impl.
	virtual void start() override;
	virtual void stop() override;
	virtual void pause() override;

	void init();
	void animation1();
	void animation2();
	void animationBase(MyGraph &g, MyTrack &t, Speed &s, 
					   std::mutex &l, bool &b, std::condition_variable &cv);
};

#endif // ANIMATION_H