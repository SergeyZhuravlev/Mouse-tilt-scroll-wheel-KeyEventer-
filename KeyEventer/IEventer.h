#pragma once
#include <memory>
class IEventer: public std::enable_shared_from_this<IEventer>
{
public:
	IEventer();
	virtual ~IEventer();
	virtual bool SetHooks() = 0;
	virtual std::pair<LRESULT, bool> SystemEventsHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual void WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void WindowClose(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

