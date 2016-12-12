#pragma once
#include "IEventer.h"
#include "ISettings.h"
#include "ISystemEventer.h"
#include "IEventMapper.h"

class MouseEventer :
	public IEventer
{
public:
	MouseEventer(std::shared_ptr<ISettings> settings, std::shared_ptr<ISystemEventer> systemEventer, std::shared_ptr<IEventMapper> eventMapper);
	~MouseEventer();
	bool SetHooks() override;
	std::pair<LRESULT, bool> SystemEventsHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	void MouseHandler(RAWINPUT* rawInput);
	std::shared_ptr<ISettings> _settings;
	std::shared_ptr<ISystemEventer> _systemEventer;
	std::shared_ptr<IEventMapper> _eventMapper;
};

