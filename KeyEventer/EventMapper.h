#pragma once
#include "IEventMapper.h"
#include "ISettings.h"
#include "IExecuter.h"
#include "TrayEvents.h"
#include "IRepeatableKeySender.h"
class EventMapper :
	public IEventMapper
{
public:
	EventMapper(std::shared_ptr<ISettings> settings, std::shared_ptr<IExecuter> executer, std::shared_ptr<IRepeatableKeySender> keySender, std::function<std::shared_ptr<ISystemController>()> systemControllerGetter);
	~EventMapper();
	void raiseMouseEvent(MouseAdditionalButtonsState mouseAdditionalButtonState, MouseButtonsState mouseButtonState, MouseWheelState mouseWheelState) override;
	void raiseTrayEvent(TrayEvent trayEvent) override;

private:
	std::shared_ptr<ISettings> _settings;
	std::shared_ptr<IExecuter> _executer;
	std::shared_ptr<IRepeatableKeySender> _keySender;
	std::function<std::shared_ptr<ISystemController>()> _systemController;

	constexpr static const int WheelLeft = 4287105024;
	constexpr static const int WheelRight = 7866368;
	//constexpr static const int WheelCenter = 0;
};

