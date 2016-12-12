#include "stdafx.h"
#include "SystemController.h"

SystemController::SystemController(HWND applicationHWindow, HINSTANCE applicationHInstance)
	: _applicationHWindow(applicationHWindow)
	, _applicationHInstance(applicationHInstance)
{
}

SystemController::~SystemController()
{
}

void SystemController::ExitApplication()
{
	PostMessageA(_applicationHWindow, WM_CLOSE, 0, 0);
}

HWND SystemController::ApplicationHWindow()
{
	return _applicationHWindow;
}

HINSTANCE SystemController::ApplicationHInstance()
{
	return _applicationHInstance;
}

void SystemController::SetMouseWheelTiltMode(bool raiseArrowKeys)
{
	_mouseWheelTiltMode = raiseArrowKeys;
}

bool SystemController::GetMouseWheelTiltMode()
{
	return _mouseWheelTiltMode;
}
