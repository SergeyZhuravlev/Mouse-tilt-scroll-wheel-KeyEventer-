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

void EventMapper::raiseMouseEvent(MouseAdditionalButtonsState mouseAdditionalButtonState, MouseButtonsState mouseButtonState, MouseWheelState mouseWheelState)
{
	if (!_systemController()->GetMouseWheelTiltMode())
		return;
	switch (mouseAdditionalButtonState)
	{
	case WheelLeft:
		_executer->SendKey(VK_LEFT);
		break;
	case WheelRight:
		_executer->SendKey(VK_RIGHT);
		break;
	default:;
	}
	switch (mouseButtonState)
	{
	case RI_MOUSE_WHEEL:
		if (_systemController()->GetIsForwardStref() && mouseWheelState < 0)
			_systemController()->SetStref(false);
		if (_systemController()->GetIsBackwardStref() && mouseWheelState > 0)
			_systemController()->SetStref(true);
		break;
	case RI_MOUSE_MIDDLE_BUTTON_DOWN:
		_systemController()->SetStref(true);
		break;
	case RI_MOUSE_MIDDLE_BUTTON_UP:
		_systemController()->SetStref(false);
		break;
	default:;
	}
	if (_systemController()->GetIsForwardStref())
		_executer->SendKey(VK_RIGHT);
	if (_systemController()->GetIsBackwardStref())
		_executer->SendKey(VK_LEFT);
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
