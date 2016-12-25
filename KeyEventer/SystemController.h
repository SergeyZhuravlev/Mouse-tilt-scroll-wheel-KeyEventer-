#pragma once
#include "ISystemController.h"
class SystemController :
	public ISystemController
{
public:
	SystemController(HWND applicationHWindow, HINSTANCE applicationHInstance);
	~SystemController();
	void ExitApplication() override;
	HWND ApplicationHWindow() override;
	HINSTANCE ApplicationHInstance() override;
	void SetMouseWheelTiltMode(bool arrowKeys) override;
	bool GetMouseWheelTiltMode() override;

private:
	HWND _applicationHWindow;
	HINSTANCE _applicationHInstance;
	bool _mouseWheelTiltMode=true;
};

