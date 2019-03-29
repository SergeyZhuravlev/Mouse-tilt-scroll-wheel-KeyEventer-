#include "stdafx.h"
#include "Timer.h"

Disposable<UINT_PTR> TimerGlobalContext::AllocateTimerId()
{
	return { ++_lastIdTimer, [](UINT_PTR idTimer) { Timer::GetTimerContext().DeallocateTimerId(idTimer); } };
}

TimerContext& TimerGlobalContext::GetContext(UINT_PTR idTimer)
{
	std::lock_guard<std::mutex> lock(_protectContext);
	return _idTimerToTimerContext[idTimer];
}

void TimerGlobalContext::DeallocateTimerId(UINT_PTR idTimer)
{
	std::lock_guard<std::mutex> lock(_protectContext);
	_idTimerToTimerContext.erase(idTimer);
}

Timer::Timer(DWORD periodInMilliseconds, std::function<HWND()>&& windowHandleGetter)
	: _periodInMilliseconds(periodInMilliseconds)
	, _windowHandleGetter(std::move(windowHandleGetter))
{
}

TimerGlobalContext& Timer::GetTimerContext()
{
	static TimerGlobalContext globalÑontext;
	return globalÑontext;
}

VOID CALLBACK Timer::WinApiTimerHandler(HWND windowHandle, UINT, UINT_PTR idTimer, DWORD)
{
	auto this_ = Timer::GetTimerContext().GetContext(idTimer).timerThis;
	if (this_ == nullptr)
		throw std::logic_error("idTimer is null");
	this_->Handler();
}

Disposable<UINT_PTR> Timer::MakeTimer(HWND windowHandle, DWORD periodInMilliseconds, Timer* const this_)
{
	if(windowHandle == nullptr)
		throw std::invalid_argument("windowHandle is null");
	if (this_ == nullptr)
		throw std::invalid_argument("this_ is null");
	auto result = Timer::GetTimerContext().AllocateTimerId();
	auto setTimerResult = SetTimer(windowHandle, result.get(), periodInMilliseconds, &Timer::WinApiTimerHandler);
	if (!setTimerResult)
		throw std::runtime_error("Failed making timer");
	if(setTimerResult != result.get())
		throw std::logic_error("Timer wrongly implemented");
	Timer::GetTimerContext().GetContext(result.get()).timerThis = this_;
	return Disposable<UINT_PTR> 
	(
		std::move(result),
		[=] (typename Disposable<UINT_PTR>::Deleter&& timerContextDeleter)
		{ 
			return [=, oldDeleter = std::move(timerContextDeleter)] (UINT_PTR idTimer)
			{
				KillTimer(windowHandle, idTimer);
				oldDeleter(idTimer); 
			};
		}
	);
}

void Timer::Start()
{
	if(!_timerHandle.get_deleter())
		_timerHandle = Timer::MakeTimer(_windowHandleGetter(), _periodInMilliseconds, this);
}
