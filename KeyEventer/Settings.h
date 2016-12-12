#pragma once
#include "ISettings.h"
class Settings :
	public ISettings
{
public:
	Settings();
	~Settings();
	void Load() override;
};

