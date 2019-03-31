#pragma once
#include "Timer.h"
#include "IRepeatableKeySender.h"

class RepeatableKeySender :
	public Timer, public IRepeatableKeySender
{
public:
	RepeatableKeySender(DWORD periodInMilliseconds, DWORD keySpanInMilliseconds, std::function<HWND()>&& windowHandleGetter);
	void SetSendingKeys(Keys&& keys);

protected:
	void Handler() override;

private:
	void SendKey(char virtualKey);
	Keys _keysForSending;
	std::mutex _taskProtector;
	DWORD _keySpanInMilliseconds;
};

