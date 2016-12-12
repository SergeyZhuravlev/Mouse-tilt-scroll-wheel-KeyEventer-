#pragma once
#include "IEventer.h"
#include "ISystemController.h"
class ISystemEventer :
	public IEventer
{
public:
	ISystemEventer();
	virtual ~ISystemEventer();
	virtual std::shared_ptr<ISystemController> SystemController() = 0;
	virtual int Run() = 0;
	virtual void RegisterEventer(std::shared_ptr<IEventer>) = 0;
	virtual const char* const WindowClassName() = 0;
	virtual const char* const WindowName() = 0;
};

