#include "stdafx.h"
#include "KeyboardEventer.h"

KeyboardEventer::KeyboardEventer(std::shared_ptr<ISettings> settings, std::shared_ptr<IEventMapper> eventMapper)
	: _settings(settings)
	, _eventMapper(eventMapper)
{
}

KeyboardEventer::~KeyboardEventer()
{
}

bool KeyboardEventer::SetHooks()
{
	//_systemEventer->RegisterEventer(shared_from_this());
	return true;
}

std::pair<LRESULT, bool> KeyboardEventer::SystemEventsHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return{ 0, false };
}