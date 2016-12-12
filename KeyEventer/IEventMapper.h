#pragma once
class IEventMapper
{
public:
	IEventMapper();
	virtual ~IEventMapper();
	using MouseButtonsState = ULONG;
	using TrayEvent = ULONG;
	virtual void raiseMouseEvent(MouseButtonsState mouseButtonState) = 0;
	virtual void raiseTrayEvent(TrayEvent trayEvent) = 0;
};

