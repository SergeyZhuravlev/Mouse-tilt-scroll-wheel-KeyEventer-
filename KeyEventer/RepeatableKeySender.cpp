#include "stdafx.h"
#include "RepeatableKeySender.h"

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
	Sleep(100);
	keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);
}
