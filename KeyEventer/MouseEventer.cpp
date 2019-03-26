#include "stdafx.h"
#include "MouseEventer.h"
#include <sstream>

using namespace std;

MouseEventer::MouseEventer(std::shared_ptr<ISettings> settings, std::shared_ptr<ISystemEventer> systemEventer, std::shared_ptr<IEventMapper> eventMapper)
	: _settings(settings)
	, _systemEventer(systemEventer)
	, _eventMapper(eventMapper)
{
}

MouseEventer::~MouseEventer()
{
}

bool MouseEventer::SetHooks()
{
	RAWINPUTDEVICE Rid;

	Rid.usUsagePage = 0x01;
	Rid.usUsage = 0x02;
	Rid.dwFlags = RIDEV_INPUTSINK;
	Rid.hwndTarget = _systemEventer->SystemController()->ApplicationHWindow();

	_systemEventer->RegisterEventer(shared_from_this());

	if (RegisterRawInputDevices(&Rid, 1, sizeof(Rid)) == FALSE) {
		return false;
	}
	return true;
}

std::pair<LRESULT, bool> MouseEventer::SystemEventsHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INPUT:
	{
		size_t dwSize;
		if (GetRawInputData((HRAWINPUT)lParam,
			RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER)) == -1)
			break;
		if (dwSize%sizeof(RAWINPUT) != 0)
			break;
		vector<char> rawInputBuffer(dwSize, 0);
		RAWINPUT* rawInput = (RAWINPUT*)rawInputBuffer.data();
		if (GetRawInputData((HRAWINPUT)lParam,
			RID_INPUT, rawInput, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			break;
		if (rawInput->header.dwSize != sizeof(RAWINPUT))
			break;
		if (rawInput->header.dwType == RIM_TYPEMOUSE)
		{
			MouseHandler(rawInput);
			return{ 0, true };
		};
	}; break;
	default:;
	}
	return{ 0, false };
}

void MouseEventer::MouseHandler(RAWINPUT* rawInput)
{
	const auto& mouse = rawInput->data.mouse;
	/*std::stringstream ss;
	ss << __FUNCDNAME__ << std::endl;
	ss << "{" << std::endl;
	ss << "mouse.usFlags" << mouse.usFlags << std::endl;
	ss << "mouse.ulButtons" << mouse.ulButtons << std::endl;
	ss << "mouse.usButtonFlags" << mouse.usButtonFlags << std::endl;
	ss << "mouse.usButtonData" << mouse.usButtonData << std::endl;
	ss << "mouse.ulRawButtons" << mouse.ulRawButtons << std::endl;
	ss << "mouse.lLastX" << mouse.lLastX << std::endl;
	ss << "mouse.lLastY" << mouse.lLastY << std::endl;
	ss << "mouse.ulExtraInformation" << mouse.ulExtraInformation << std::endl;
	ss << "}" << std::endl;
	OutputDebugString(ss.str().c_str());*/
	_eventMapper->raiseMouseEvent(mouse.ulButtons, mouse.usButtonFlags, mouse.usButtonData);
}
