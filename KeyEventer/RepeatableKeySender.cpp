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
	}
	for (auto key : keysForSending)
		SendKey(key);
}

void RepeatableKeySender::SendKey(char virtualKey)
{
	keybd_event(virtualKey, 0, 0, 0);
	Sleep(_keySpanInMilliseconds);
	keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);
}
