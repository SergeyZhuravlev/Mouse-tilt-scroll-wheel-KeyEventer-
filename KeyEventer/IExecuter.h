#pragma once
class IExecuter
{
public:
	IExecuter();
	virtual ~IExecuter();
	//virtual void SendKey(char virtualKey) = 0;
	virtual void SwapMouseButtons() = 0;
	virtual void ExitApplication() = 0;
	virtual void SwitchMouseWheelTiltMode() = 0;
};

