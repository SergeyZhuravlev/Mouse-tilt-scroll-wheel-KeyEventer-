#include "stdafx.h"
#include "EventMapper.h"


EventMapper::EventMapper(std::shared_ptr<ISettings> settings, std::shared_ptr<IExecuter> executer, std::function<std::shared_ptr<ISystemController>()> systemControllerGetter)
	: _settings(settings)
	, _executer(executer)
	, _systemController(systemControllerGetter)
{
}

EventMapper::~EventMapper()
{
}

void EventMapper::raiseMouseEvent(MouseButtonsState mouseButtonState)
{
	switch (mouseButtonState)
	{
	case WheelLeft:
		if (_systemController()->GetMouseWheelTiltMode())
			_executer->SendKey(VK_LEFT);
		break;
	case WheelRight:
		if (_systemController()->GetMouseWheelTiltMode())
		_executer->SendKey(VK_RIGHT);
		break;
	default:;
	}
}

void EventMapper::raiseTrayEvent(TrayEvent trayEvent)
{
	switch (trayEvent)
	{
	case ID_EXIT:
		_executer->ExitApplication();
		break;
	case ID_SWAP_MOUSE_BUTTONS:
		_executer->SwapMouseButtons();
		break;
	case ID_SWITCH_MOUSE_WHEEL_TILT_MODE:
		_executer->SwitchMouseWheelTiltMode();
		break;
	default:;
	}
}
