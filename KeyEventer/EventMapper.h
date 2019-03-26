#pragma once
#include "IEventMapper.h"
#include "ISettings.h"
#include "IExecuter.h"
#include "TrayEvents.h"
class EventMapper :
	public IEventMapper
{
public:
	EventMapper(std::shared_ptr<ISettings> settings, std::shared_ptr<IExecuter> executer, std::function<std::shared_ptr<ISystemController>()> systemControllerGetter);
	~EventMapper();
	void raiseMouseEvent(MouseAdditionalButtonsState mouseAdditionalButtonState, MouseButtonsState mouseButtonState, MouseWheelState mouseWheelState) override;
	void raiseTrayEvent(TrayEvent trayEvent) override;

private:
	std::shared_ptr<ISettings> _settings;
	std::shared_ptr<IExecuter> _executer;
	std::function<std::shared_ptr<ISystemController>()> _systemController;

	constexpr static const int WheelLeft = 4287105024;
	constexpr static const int WheelRight = 7866368;
};

