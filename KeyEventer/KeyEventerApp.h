#pragma once
#include<memory>
#include"ISettings.h"
#include"IEventer.h"
#include"ISystemEventer.h"
#include"IExecuter.h"
#include"IEventMapper.h"
#include "IRepeatableKeySender.h"
class KeyEventerApp
{
public:
	KeyEventerApp();
	~KeyEventerApp();
	int Execute();

private:
	bool IsAppDuplicate();
	std::shared_ptr<ISystemController> SystemControllerGetter() const;//[&] {return _systemEventer->SystemController();})
	std::shared_ptr<ISettings> _settings;
	std::shared_ptr<IExecuter> _executer;
	std::shared_ptr<IRepeatableKeySender> _keySender;
	std::shared_ptr<IEventMapper> _eventMapper;
	std::shared_ptr<ISystemEventer> _systemEventer;
	std::shared_ptr<IEventer> _trayEventer;
	std::shared_ptr<IEventer> _keyboardEventer;
	std::shared_ptr<IEventer> _mouseEventer;
};

