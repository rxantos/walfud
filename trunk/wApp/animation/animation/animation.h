

// animation.h
//

#ifndef ANIMATION_H
#define ANIMATION_H

#include "graph.h"
#include "track.h"
#include "speed.h"
#include <mutex>
#include <future>
#include <condition_variable>
#include <atomic>
#include <memory>
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
	HWND m_board;
	HDC m_dc;

	bool m_init;
	std::future<void> m_w1, m_w2;
	std::condition_variable m_cv1, m_cv2;
	std::mutex m_lock;
	bool m_b1, m_b2;
	std::atomic<bool> m_quit;

public:
	MyAnimation();
	~MyAnimation();

public:
	// Interface.
	void setBoard(HWND drawHWnd);

	// impl.
	virtual void start() override;
	virtual void stop() override;
	virtual void pause() override;

	void animation1();
	void animation2();
	void animationBase(std::shared_ptr<Graph<Coordinate_2D>> g, std::shared_ptr<Track<Coordinate_2D>> mt, std::shared_ptr<Speed> s,
					   std::mutex &l, bool &b, std::condition_variable &cv,
					   std::atomic<bool> &q);
};

#endif // ANIMATION_H