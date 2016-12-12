#include "stdafx.h"
#include "TrayEventer.h"
#include "TrayEvents.h"

TrayEventer::TrayEventer(std::shared_ptr<ISettings> settings, std::shared_ptr<ISystemEventer> systemEventer, std::shared_ptr<IEventMapper> eventMapper)
	: _settings(settings)
	, _systemEventer(systemEventer)
	, _eventMapper(eventMapper)
{
}

TrayEventer::~TrayEventer()
{
	
}

bool TrayEventer::SetHooks()
{
	_systemEventer->RegisterEventer(shared_from_this());
	return true;
}

void TrayEventer::ShowPopupMenu(HWND hWnd, POINT *curpos, int wDefaultItem)
{
	//ADD MENU ITEMS.------------------------------------------------------------------
	HMENU hPop = CreatePopupMenu();
	int indexMenu = 0;

	InsertMenu(hPop, indexMenu++, MF_BYPOSITION | MF_STRING, ID_DO_NOTHING, "Do &nothing with KeyEventer");
	InsertMenu(hPop, indexMenu++, MF_BYPOSITION | MF_SEPARATOR, 0, nullptr);
	InsertMenu(hPop, indexMenu++, MF_BYPOSITION | MF_STRING, ID_SWITCH_MOUSE_WHEEL_TILT_MODE, "Switch mouse wheel &tilt mode");
	InsertMenu(hPop, indexMenu++, MF_BYPOSITION | MF_STRING, ID_SWAP_MOUSE_BUTTONS, "Swap mouse &buttons");
	InsertMenu(hPop, indexMenu++, MF_BYPOSITION | MF_SEPARATOR, 0, nullptr);
	InsertMenu(hPop, indexMenu++, MF_BYPOSITION | MF_STRING, ID_EXIT, "&Exit");
	
	//CAN DO WITHOUT STUFF.------------------------------------------------------------
	SetMenuDefaultItem(hPop, ID_EXIT, FALSE);
	SetFocus(hWnd);
	SendMessage(hWnd, WM_INITMENUPOPUP, (WPARAM)hPop, 0);

	//SHOW POPUP MENU.-----------------------------------------------------------------
	{
		//GET CURSOR POSITION TO CREATE POPUP THERE.-------------------------------------
		POINT pt;
		if (!curpos) {
			GetCursorPos(&pt);
			curpos = &pt;
		}

		{
			//DISPLAT MENU AND WAIT FOR SELECTION.-----------------------------------------
			WORD cmd = TrackPopupMenu(hPop, TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_RETURNCMD | TPM_NONOTIFY, curpos->x, curpos->y, 0, hWnd, NULL);

			//SEND MESSAGE MAPPED TO SELECTED ITEM.----------------------------------------
			SendMessage(hWnd, WM_COMMAND, cmd, 0);
		}
	}
	
	DestroyMenu(hPop);
}

void TrayEventer::RemoveTrayIcon(HWND hWnd, UINT uID) 
{
	NOTIFYICONDATA  nid = {};
	nid.hWnd = hWnd;
	nid.uID = uID;

	Shell_NotifyIcon(NIM_DELETE, &nid);
}

void TrayEventer::AddTrayIcon(HWND hWnd, UINT uID, UINT uCallbackMsg, UINT uIcon)
{
	//CREATE SYSTEN TRAY ICON.---------------------------------------------------------------------
	NOTIFYICONDATA  nid = {};
	nid.hWnd = hWnd;
	nid.uID = uID;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	nid.uCallbackMessage = uCallbackMsg;
	nid.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_SMALL));

	strcpy_s(nid.szTip, "KeyEventer");

	//SEND MESSAGE TO SYSTEM TRAY TO ADD ICON.--------------------------------------------
	Shell_NotifyIcon(NIM_ADD, &nid);
}

std::pair<LRESULT, bool> TrayEventer::SystemEventsHandler(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		auto trayCommand = LOWORD(wParam);
		switch (trayCommand)
		{
		case ID_SWITCH_MOUSE_WHEEL_TILT_MODE:
		case ID_SWAP_MOUSE_BUTTONS:
		case ID_EXIT:
			_eventMapper->raiseTrayEvent(trayCommand);
		case ID_DO_NOTHING:
			return{ 0, true };
		default:;
		}
	} break;
	case WM_APP:
		switch (lParam) {
		case WM_RBUTTONUP:
		case WM_LBUTTONUP:
		{
			auto hwnd = _systemEventer->SystemController()->ApplicationHWindow();
			//SetForegroundWindow(hWnd);
			ShowPopupMenu(hwnd, NULL, -1);
			PostMessage(hwnd, WM_APP + 1, 0, 0);
			return{ 0, true };
		}
		default:;
		}
	default:;
	}
	return{0, false};
}

void TrayEventer::WindowCreate(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	AddTrayIcon(hWnd, 1, WM_APP, 0);
}

void TrayEventer::WindowClose(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RemoveTrayIcon(hWnd, 1);
}