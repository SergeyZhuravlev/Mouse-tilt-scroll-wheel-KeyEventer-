#pragma once
#include "ITimer.h"

struct IRepeatableKeySender: public virtual ITimer
{
	struct Key
	{
		char key;
		bool singleSending;
	};
	using Keys = std::vector<Key>;
	virtual void SetSendingKeys(Keys&& keys) = 0;
	virtual ~IRepeatableKeySender() = default;
};