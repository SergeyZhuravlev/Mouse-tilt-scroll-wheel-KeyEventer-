#include "stdafx.h"
#include "RepeatableKeySender.h"

RepeatableKeySender::RepeatableKeySender(DWORD periodInMilliseconds, DWORD keySpanInMilliseconds, std::function<HWND()>&& windowHandleGetter)
	: Timer(periodInMilliseconds, std::move(windowHandleGetter))
	, _keySpanInMilliseconds(keySpanInMilliseconds)
{

}

void RepeatableKeySender::SetSendingKeys(Keys && keys)
{
	std::lock_guard lock(_taskProtector);
	_keysForSending = std::move(keys);
}

void RepeatableKeySender::Handler()
{
	Keys keysForSending;
	{
		std::lock_guard lock(_taskProtector);
		keysForSending = _keysForSending;
		_keysForSending.erase(std::remove_if(_keysForSending.begin(), _keysForSending.end(), [](const auto& keyDescription) 
		{
			return keyDescription.singleSending; 
		}), _keysForSending.end());
	}
	for (auto keyDescription : keysForSending)
		SendKey(keyDescription.key);
}

void RepeatableKeySender::SendKey(char virtualKey)
{
	keybd_event(virtualKey, 0, 0, 0);
	Sleep(_keySpanInMilliseconds);
	keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);
}
