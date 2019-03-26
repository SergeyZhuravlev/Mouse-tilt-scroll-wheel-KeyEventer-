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
	void SetStrefEnabled(bool enabled) override;
	void SetStrefDirection(bool forward) override;
	bool GetIsForwardStref() const override;
	bool GetIsBackwardStref() const override;

private:
	HWND _applicationHWindow;
	HINSTANCE _applicationHInstance;
	bool _mouseWheelTiltMode=true;
	bool _strefIsForward=true;
	bool _strefEnabled = false;
};

