// KeyEventer.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "KeyEventer.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);
	KeyEventerApp app(hInstance);
	return app.Execute();
}