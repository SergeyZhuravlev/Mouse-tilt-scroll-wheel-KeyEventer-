#pragma once
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
	virtual void SetStrafingEnabled(bool enabled) = 0;
	virtual void SetStrafingDirection(bool forward) = 0;
	virtual bool GetIsForwardStrafing() const = 0;
	virtual bool GetIsBackwardStrafing() const = 0;
};

