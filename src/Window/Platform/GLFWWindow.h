#pragma once

#include <Windows.h>

#include "src/Window/Window.h"

#include "glad/glad.h"

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

	void MakeContextCurrent() override;

	void* GetNativeWindow() override { return m_WndHandle; }

private:

	static void ResizeCallback(GLFWwindow* window, int width, int height);

private:

	GLFWwindow* m_WndHandle;
};

