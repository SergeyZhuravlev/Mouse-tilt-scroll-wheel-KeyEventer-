#pragma once
class ISettings
{
public:
	ISettings();
	virtual ~ISettings();
	//virtual void Load() = 0;

	virtual UINT GetKeyRepeatPeriodInMilliseconds() const = 0;
	virtual UINT GetKeySpanInMilliseconds() const = 0;
	virtual bool GetTiltModeEnabled() const = 0;
	virtual bool GetLegacyModeEnabled() const = 0;
};

