#pragma once
#include "Timer.h"
#include "IRepeatableKeySender.h"

class RepeatableKeySender :
	public Timer, public IRepeatableKeySender
{
public:
	using Timer::Timer;
	void SetSendingKeys(Keys&& keys);

protected:
	void Handler() override;

private:
	void SendKey(char virtualKey);
	Keys _keysForSending;
	std::mutex _taskProtector;
};

