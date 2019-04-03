#include "stdafx.h"
#include "EventMapper.h"
#include <string>


EventMapper::EventMapper(std::shared_ptr<ISettings> settings, std::shared_ptr<IExecuter> executer, std::shared_ptr<IRepeatableKeySender> keySender, std::function<std::shared_ptr<ISystemController>()> systemControllerGetter)
	: _settings(settings)
	, _executer(executer)
	, _keySender(keySender)
	, _systemController(systemControllerGetter)
{
}

EventMapper::~EventMapper()
{
}

void EventMapper::raiseMouseEvent(MouseAdditionalButtonsState mouseAdditionalButtonState, MouseButtonsState mouseButtonState, MouseWheelState mouseWheelState)
{
	if (0 == mouseAdditionalButtonState && 0 == mouseButtonState && 0 == mouseWheelState)
		return;
	if (!_systemController()->GetMouseWheelTiltMode())
		return;
	//OutputDebugString((std::to_string(mouseAdditionalButtonState)+"\r\n").c_str());
	if(_settings->GetTiltModeEnabled())
	switch (mouseAdditionalButtonState)
	{
	case WheelLeft:
		//_executer->SendKey(VK_LEFT);
		_systemController()->SetStrafingDirection(false);
		//_systemController()->SetStrafingEnabled(true, true);
		break;
	case WheelRight:
		//_executer->SendKey(VK_RIGHT);
		_systemController()->SetStrafingDirection(true);
		//_systemController()->SetStrafingEnabled(true, true);
		break;
	/*case WheelCenter:
		_systemController()->SetStrafingEnabled(false);*/
	default:;
	}
	if (_settings->GetLegacyModeEnabled())
	switch (mouseButtonState)
	{
	case RI_MOUSE_WHEEL:
		if (_systemController()->GetIsForwardStrafing() && mouseWheelState < 0)
			_systemController()->SetStrafingDirection(false);
		if (_systemController()->GetIsBackwardStrafing() && mouseWheelState > 0)
			_systemController()->SetStrafingDirection(true);
		break;
	case RI_MOUSE_MIDDLE_BUTTON_DOWN:
		_systemController()->SetStrafingEnabled(true);
		break;
	case RI_MOUSE_MIDDLE_BUTTON_UP:
		_systemController()->SetStrafingEnabled(false);
		break;
	default:;
	}
	if (_systemController()->GetIsForwardStrafing())
		//_executer->SendKey(VK_RIGHT);
		_keySender->SetSendingKeys({ VK_RIGHT });
	else if (_systemController()->GetIsBackwardStrafing())
		//_executer->SendKey(VK_LEFT);
		_keySender->SetSendingKeys({ VK_LEFT });
	else 
		_keySender->SetSendingKeys({});
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
