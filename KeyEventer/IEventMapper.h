#pragma once
class IEventMapper
{
public:
	IEventMapper();
	virtual ~IEventMapper();
	using MouseAdditionalButtonsState = ULONG;
	using MouseButtonsState = USHORT;
	using MouseWheelState = SHORT;
	using TrayEvent = ULONG;
	virtual void raiseMouseEvent(MouseAdditionalButtonsState mouseAdditionalButtonState, MouseButtonsState mouseButtonState, MouseWheelState mouseWheelState) = 0;
	virtual void raiseTrayEvent(TrayEvent trayEvent) = 0;
};

