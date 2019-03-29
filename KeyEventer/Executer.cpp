#include "stdafx.h"
#include "Executer.h"

Executer::Executer(std::shared_ptr<ISettings> settings, std::function<std::shared_ptr<ISystemController>()> systemControllerGetter)
	: _settings(settings)
	, _systemController(systemControllerGetter)
{
}

Executer::~Executer()
{
}

/*void Executer::SendKey(char virtualKey)
{
	keybd_event(virtualKey, 0, 0, 0);
	Sleep(100);
	keybd_event(virtualKey, 0, KEYEVENTF_KEYUP, 0);
}*/

void Executer::SwapMouseButtons()
{
	_swappedMouseButtons = (_swappedMouseButtons != FALSE ? FALSE : TRUE);
	::SwapMouseButton(_swappedMouseButtons);
}

void Executer::ExitApplication()
{
	_systemController()->ExitApplication();
}

void Executer::SwitchMouseWheelTiltMode()
{
	_systemController()->SetMouseWheelTiltMode(!_systemController()->GetMouseWheelTiltMode());
}
