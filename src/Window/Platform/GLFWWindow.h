#pragma once

#include <Windows.h>

#include "src/Window/Window.h"

#include "GLFW/glfw3.h"

#pragma comment(lib, "RayCasting/vendor/GLFW/include/GLFW/glfw3.lib")

class GLFWWindow : public Window
{
public:

	GLFWWindow(WinProps props);

	virtual ~GLFWWindow();

	void OnUpdate() override;

	void Shutdown() override;

	int GetWidth() override;

	int GetHeight() override;

	void SetUserPointer(void* pointer) override;

	void* GetNativeWindow() override { return m_wndHandle; }

private:

	GLFWwindow* m_wndHandle;
};

