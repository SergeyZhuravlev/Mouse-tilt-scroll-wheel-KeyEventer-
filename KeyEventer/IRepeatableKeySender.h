#pragma once
#include "ITimer.h"

struct IRepeatableKeySender: public virtual ITimer
{
	using Keys = std::vector<char>;
	virtual void SetSendingKeys(Keys&& keys) = 0;
	virtual ~IRepeatableKeySender() = default;
};