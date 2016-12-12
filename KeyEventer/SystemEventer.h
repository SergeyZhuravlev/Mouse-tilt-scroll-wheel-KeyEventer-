#pragma once
#include "ISystemEventer.h"
#include "ISettings.h"
#include "IEventMapper.h"
#include "ISystemController.h"

//todo: split SystemEventer and window
class SystemEventer :
	public ISystemEventer
{
public:
	SystemEventer(std::shared_ptr<ISettings> settings, std::shared_ptr<IEventMapper> eventMapper);
	~SystemEventer();
	bool SetHooks() override;
	int Run() override;
	std::shared_ptr<ISystemController> SystemController() override;
	void RegisterEventer(std::shared_ptr<IEventer> eventer) override;
	const char* const WindowClassName() override;
	const char* const WindowName() override;

private:
	std::pair<LRESULT, bool> SystemEventsHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) override;
	ATOM RegisterWindowClass();
	bool InitWindow();
	LRESULT static CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	LRESULT CALLBACK WindowProc(/*bool initialized,*/ HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static SystemEventer* _This;
	HWND _hWindow;
	HINSTANCE _applicationHInstance;
	std::shared_ptr<ISettings> _settings;
	std::shared_ptr<IEventMapper> _eventMapper;
	std::shared_ptr<ISystemController> _systemController;
	std::vector<std::shared_ptr<IEventer>> _registeredEventers;
};

