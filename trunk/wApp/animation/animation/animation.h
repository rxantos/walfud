

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
#include <future>
#include <functional>
#include <windows.h>

class Animation
{
public:
	virtual ~Animation() = 0 {}

public:
	// Interface.
	virtual void start() = 0;
	virtual void stop(bool waitDone = true) = 0;
	virtual void pause() = 0;

	virtual void clear() = 0;
};

class MyAnimation : public Animation
{
protected:
	// data.
	HWND m_board;
	HDC m_dc;
	std::shared_ptr<Graph<Coordinate_2D>> m_g;
	std::shared_ptr<Track2<Coordinate_2D>> m_t;
	std::shared_ptr<Speed> m_s;

	std::future<void> m_w;
	std::condition_variable m_cv;
	std::mutex m_lock;
	bool m_b;
	std::atomic<bool> m_quit;

public:
	MyAnimation();
	~MyAnimation();

public:
	// Interface.
	// You must set `Board/Graph/Track/Speed` before `start` the animation.
	void setBoard(HWND drawHWnd);
	void setGraph(std::shared_ptr<Graph<Coordinate_2D>> g) { m_g = g; }
	void setTrack(std::shared_ptr<Track2<Coordinate_2D>> t) { m_t = t; } 
	void setSpeed(std::shared_ptr<Speed> s) { m_s = s; }

	// impl.
	virtual void start() override;
	virtual void stop(bool waitDone = true) override;
	virtual void pause() override;

	virtual void clear() override;

protected:
	// logic.
	virtual void animation();
};

/*
 *
 *		This class is enhanced `MyAnimation`, containing
 *	notification when a cycle of animation done.
 *
 */
class MyAnimation2 : public MyAnimation
{
protected:
	// data.
	std::function<void (void *)> m_cycleDoneCallback;
	void *m_cbParam;

public:
	// Interface.
	void setDoneCallback(std::function<void (void *)> cb, void *param = nullptr);

protected:
	// logic.
	virtual void animation() override;
};

#endif // ANIMATION_H