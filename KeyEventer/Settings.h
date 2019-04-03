#pragma once
#include "ISettings.h"
class Settings :
	public ISettings
{
public:
	Settings(HINSTANCE hInstance);
	~Settings();
	UINT GetKeyRepeatPeriodInMilliseconds() const override;
	UINT GetKeySpanInMilliseconds() const override;
	bool GetTiltModeEnabled() const override;
	bool GetLegacyModeEnabled() const override;

private:
	std::string ExeDirectory() const;
	std::string SettingsPath() const;

	void Load() /*override*/;
	void MakeDefaultFile() const;

	HINSTANCE _hInstance;

	UINT KeyRepeatPeriodInMilliseconds = 400;
	UINT KeySpanInMilliseconds = 100;
	bool TiltModeEnabled = true;
	bool LegacyModeEnabled = true;
};

