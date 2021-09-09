#include "WindowsWindow.h"

#include <iostream>

Window* Window::Create(WinProps props) 
{
	return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(WinProps props)
{
	WNDCLASSEX wndClass = {0};

	wndClass.cbSize = sizeof(wndClass);
	wndClass.hInstance = GetModuleHandle(NULL);
	wndClass.lpszClassName = (LPCWSTR)props.name;
	wndClass.lpfnWndProc = (WNDPROC)WindowsWindow::WndProc;
	
	m_wndClass = RegisterClassEx(&wndClass);

	if (m_wndClass == 0)
	{
		std::cout << GetLastError() << std::endl;
		__debugbreak();
	}

}

WindowsWindow::~WindowsWindow()
{
	std::cout << __FUNCTION__ << std::endl;
}

void WindowsWindow::OnUpdate()
{

}

int WindowsWindow::GetWidth()
{
	return 0;
}

int WindowsWindow::GetHeight()
{
	return 0;
}

void WindowsWindow::SetUserPointer(void* pointer)
{
}

LRESULT WindowsWindow::WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) 
{
	return 0;
}
