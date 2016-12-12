#pragma once
#include "IEventer.h"
#include "ISettings.h"
#include "ISystemEventer.h"
#include "IEventMapper.h"

class TrayEventer :
	public IEventer
{
public:
	TrayEventer(std::shared_ptr<ISettings> settings, std::shared_ptr<ISystemEventer> systemEventer, std::shared_ptr<IEventMapper> eventMapper);
	~TrayEventer();
	bool SetHooks() override;
	std::pair<LRESULT, bool> SystemEventsHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	void WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	void WindowClose(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;

private:
	void TrayEventer::RemoveTrayIcon(HWND hWnd, UINT uID);
	void TrayEventer::AddTrayIcon(HWND hWnd, UINT uID, UINT uCallbackMsg, UINT uIcon);
	void TrayEventer::ShowPopupMenu(HWND hWnd, POINT *curpos, int wDefaultItem);

	std::shared_ptr<ISettings> _settings;
	std::shared_ptr<ISystemEventer> _systemEventer;
	std::shared_ptr<IEventMapper> _eventMapper;
};

