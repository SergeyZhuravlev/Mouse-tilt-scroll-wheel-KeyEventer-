#pragma once
class ISettings
{
public:
	ISettings();
	virtual ~ISettings();
	virtual void Load() = 0;	
};

