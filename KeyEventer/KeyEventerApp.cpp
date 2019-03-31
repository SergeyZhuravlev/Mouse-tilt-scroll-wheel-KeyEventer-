#include "stdafx.h"
#include "KeyEventerApp.h"
#include "KeyboardEventer.h"
#include "SystemEventer.h"
#include "MouseEventer.h"
#include "TrayEventer.h"
#include "Settings.h"
#include "Executer.h"
#include "EventMapper.h"
#include "RepeatableKeySender.h"

KeyEventerApp::KeyEventerApp(HINSTANCE hInstance):
	_settings(std::make_shared<Settings>(hInstance)),
	_executer(std::make_shared<Executer>(_settings, std::bind(&KeyEventerApp::SystemControllerGetter, this))),
	_keySender(std::make_shared<RepeatableKeySender>(_settings->GetKeyRepeatPeriodInMilliseconds(), _settings->GetKeySpanInMilliseconds(), [this] {return this->SystemControllerGetter()->ApplicationHWindow(); })),
	_eventMapper(std::make_shared<EventMapper>(_settings, _executer, _keySender, std::bind(&KeyEventerApp::SystemControllerGetter, this))),
	_keyboardEventer(std::make_shared<KeyboardEventer>(_settings, _eventMapper)),
	_systemEventer(std::make_shared<SystemEventer>(_settings, _eventMapper)),
	_mouseEventer(std::make_shared<MouseEventer>(_settings, _systemEventer, _eventMapper)),
	_trayEventer(std::make_shared<TrayEventer>(_settings, _systemEventer, _eventMapper))
{}

KeyEventerApp::~KeyEventerApp()
{
}

int KeyEventerApp::Execute()
{
	if (IsAppDuplicate())
		return 0;
	//_settings->Load();
	if (!_trayEventer->SetHooks())
		return -1;
	if(!_systemEventer->SetHooks())
		return -1;
	if (!_mouseEventer->SetHooks())
		return -1;
	if (!_keyboardEventer->SetHooks())
		return -1;
	_keySender->Start();
	return _systemEventer->Run();
}

bool KeyEventerApp::IsAppDuplicate()
{
	//CHECK IF PREVIOUS ISTANCE IS RUNNING.-----------------------------------------------------
	HWND hPrev = NULL;
	if (hPrev = FindWindowA(_systemEventer->WindowClassName(), _systemEventer->WindowName())) 
		return true;
	return false;
}

std::shared_ptr<ISystemController> KeyEventerApp::SystemControllerGetter() const
{
	return _systemEventer->SystemController();
}
