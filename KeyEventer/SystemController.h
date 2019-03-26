#pragma once
#include "ISystemController.h"
#include <optional>
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
	void SetStref(std::optional<bool> forward) override;
	bool GetIsForwardStref() const override;
	bool GetIsBackwardStref() const override;

private:
	HWND _applicationHWindow;
	HINSTANCE _applicationHInstance;
	bool _mouseWheelTiltMode=true;
	std::optional<bool> _strefIsForward;

};

