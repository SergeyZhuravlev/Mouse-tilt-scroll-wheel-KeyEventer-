#include "stdafx.h"
#include "SystemEventer.h"
#include "SystemController.h"

using namespace std;

SystemEventer::SystemEventer(std::shared_ptr<ISettings> settings, std::shared_ptr<IEventMapper> eventMapper)
	: _settings(settings)
	, _eventMapper(eventMapper)
{
	_This = this;
}

SystemEventer::~SystemEventer()
{
}

bool SystemEventer::SetHooks()
{
	_applicationHInstance = GetModuleHandle(nullptr);
	RegisterWindowClass();
	return InitWindow();
}

int SystemEventer::Run()
{
	MSG msg;

	while (GetMessageA(&msg, nullptr, 0, 0))
	{
		if (!TranslateAcceleratorA(msg.hwnd/*_hWindow*/, nullptr, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessageA(&msg);
		}
	}

	UnregisterClassA(WindowClassName(), _applicationHInstance);

	return (int)msg.wParam;
}

std::shared_ptr<ISystemController> SystemEventer::SystemController()
{
	return _systemController;
}

void SystemEventer::RegisterEventer(std::shared_ptr<IEventer> eventer)
{
	assert(eventer);
	_registeredEventers.push_back(eventer);
}

const char * const SystemEventer::WindowClassName()
{
	return "KeyEventerHandlerWindow";
}

const char * const SystemEventer::WindowName()
{
	return "KeyEventer";
}

std::pair<LRESULT, bool> SystemEventer::SystemEventsHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return{ 0, false };
}

ATOM SystemEventer::RegisterWindowClass()
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = _applicationHInstance;
	wcex.hIcon = LoadIcon(_applicationHInstance, MAKEINTRESOURCE(IDI_KEYEVENTER));
	wcex.hIconSm = LoadIcon(_applicationHInstance, MAKEINTRESOURCE(IDI_SMALL));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = nullptr;
	wcex.lpszClassName = WindowClassName();

	return RegisterClassExA(&wcex);
}

bool SystemEventer::InitWindow()
{
	auto hWindow = CreateWindowA(WindowClassName(), WindowName(), WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _applicationHInstance, nullptr);
	_hWindow = hWindow;
	//SetWindowLongPtrA(hWindow, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));
	_systemController = std::make_shared<::SystemController>(hWindow, _applicationHInstance);
	RegisterEventer(shared_from_this());
	//_hWindow = hWindow;
	return !!_hWindow;
}

LRESULT CALLBACK SystemEventer::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	auto systemEventer = _This;/*= GetWindowLongPtrA(hWnd, GWLP_USERDATA);
	bool initialized = !!systemEventer;*/
	return /*reinterpret_cast<SystemEventer*>(*/systemEventer/*)*/->WindowProc(/*initialized,*/ hWnd, message, wParam, lParam);
}

LRESULT SystemEventer::WindowProc(/*bool initialized,*/ HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		for (auto&& eventer : _registeredEventers)
			eventer->WindowCreate(hWnd, message, wParam, lParam);
		break;
	case WM_CLOSE:
		for (auto&& eventer : _registeredEventers)
			eventer->WindowClose(hWnd, message, wParam, lParam);
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
	{
		/*if (initialized)
		{*/
			LRESULT result;
			bool handled = Linq::from(_registeredEventers).any([&](auto eventer)
			{
				bool handled;
				tie(result, handled) = eventer->SystemEventsHandler(hWnd, message, wParam, lParam);
				return handled;
			});
			if (handled)
				return result;
		//}
	}
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}

SystemEventer* SystemEventer::_This;
