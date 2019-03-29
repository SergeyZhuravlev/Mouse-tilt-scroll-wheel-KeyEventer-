#pragma once
#include "IExecuter.h"
class Executer :
	public IExecuter
{
public:
	Executer(std::shared_ptr<ISettings> settings, std::function<std::shared_ptr<ISystemController>()> systemControllerGetter);
	~Executer();

	//void SendKey(char virtualKey) override;
	void SwapMouseButtons() override;
	void ExitApplication() override;
	void SwitchMouseWheelTiltMode() override;

private:
	BOOL _swappedMouseButtons = FALSE;
	std::shared_ptr<ISettings> _settings;
	std::function<std::shared_ptr<ISystemController>()> _systemController;
};

