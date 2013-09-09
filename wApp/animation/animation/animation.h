

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
	virtual void next() = 0;

	virtual void clear() = 0;
};

class MyAnimation : public Animation
{
protected:
	// data.
	HWND m_board;
	HDC m_dc;
	std::unique_ptr<Graph<Coordinate_2D>> m_g;
	std::unique_ptr<Track2<Coordinate_2D>> m_t;
	std::unique_ptr<Speed> m_s;

	std::atomic<bool> m_inited;
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
	void setGraph(const Graph<Coordinate_2D> &g) { m_g.reset(g.clone()); }
	void setTrack(const Track2<Coordinate_2D> &t) { m_t.reset(dynamic_cast<decltype(m_t.release())>(t.clone())); }
	void setSpeed(const Speed &s) { m_s.reset(s.clone()); }

	// impl.
	virtual void start() override;
	virtual void stop(bool waitDone = true) override;
	virtual void pause() override;
	virtual void next() override;

	virtual void clear() override;						// Clear the board.

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
public:
	enum class Status : int
	{
		Default = 0,
		Running,
		Paused,
		Stopped,
	};

protected:
	// data.
	std::function<void (void *)> m_cycleDoneCallback;
	void *m_cbParam;
	std::atomic<Status> m_status;

public:
	MyAnimation2() : m_cycleDoneCallback(), m_cbParam(), m_status(Status::Stopped) {}

public:
	// Interface.
	void setDoneCallback(std::function<void (void *)> cb, void *param = nullptr);
	Status getStatus() const { return m_status; }

protected:
	// logic.
	virtual void animation() override;
};

#endif // ANIMATION_H