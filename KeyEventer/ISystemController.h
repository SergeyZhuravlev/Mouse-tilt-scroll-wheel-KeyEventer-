#pragma once
#include <optional>
class ISystemController
{
public:
	ISystemController();
	virtual ~ISystemController();
	virtual void ExitApplication() = 0;
	virtual HWND ApplicationHWindow() = 0;
	virtual HINSTANCE ApplicationHInstance() = 0;
	virtual void SetMouseWheelTiltMode(bool arrowKeys) = 0;
	virtual bool GetMouseWheelTiltMode() = 0;
	virtual void SetStref(std::optional<bool> forward) = 0;
	virtual bool GetIsForwardStref() const = 0;
	virtual bool GetIsBackwardStref() const = 0;
};

