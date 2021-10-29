#pragma once

#include "src/Window/Window.h"

#include <Windows.h>

// Work in progress
//TODO: Manage wndClass 
class WindowsWindow : public Window
{
public:
	
	WindowsWindow(WinProps props);
	
	virtual ~WindowsWindow();

	void OnUpdate() override;

	int GetWidth() override;

	int GetHeight() override;

	void SetUserPointer(void* pointer) override;

private:


	static LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private:

	HWND m_hwnd;
	ATOM m_wndClass;

};

