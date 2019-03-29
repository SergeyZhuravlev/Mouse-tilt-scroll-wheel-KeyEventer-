#pragma once
#include <atomic>
#include <mutex>
#include "Disposable.h"
#include "ITimer.h"

struct TimerContext
{
	class Timer* timerThis;
};

class TimerGlobalContext
{
public:
	Disposable<UINT_PTR> AllocateTimerId();
	TimerContext& GetContext(UINT_PTR idTimer);
	void DeallocateTimerId(UINT_PTR idTimer);

private:
	std::mutex _protectContext;
	std::atomic<UINT_PTR> _lastIdTimer = {};
	std::unordered_map<UINT_PTR, TimerContext> _idTimerToTimerContext;
};

#pragma warning(disable: 4250)
class Timer: public virtual ITimer
{
public:
	Timer(DWORD periodInMilliseconds, std::function<HWND()>&& windowHandleGetter);
	void Start() override;
	virtual ~Timer() = default;

protected:
	virtual void Handler() = 0 {};

private:
	friend class TimerGlobalContext;
	static Disposable<UINT_PTR> MakeTimer(HWND windowHandle, DWORD periodInMilliseconds, Timer* const this_);
	static TimerGlobalContext& GetTimerContext();
	static std::remove_pointer_t<TIMERPROC> WinApiTimerHandler;

	DWORD _periodInMilliseconds = {};
	std::function<HWND()> _windowHandleGetter;
	Disposable<UINT_PTR> _timerHandle;
};