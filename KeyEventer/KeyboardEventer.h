#pragma once
#include "IEventer.h"
#include "ISettings.h"
#include "IEventMapper.h"

class KeyboardEventer :
	public IEventer
{
public:
	KeyboardEventer(std::shared_ptr<ISettings> settings, std::shared_ptr<IEventMapper> eventMapper);
	~KeyboardEventer();
	bool SetHooks() override;
	std::pair<LRESULT, bool> SystemEventsHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	

private:
	std::shared_ptr<ISettings> _settings;
	std::shared_ptr<IEventMapper> _eventMapper;
};

