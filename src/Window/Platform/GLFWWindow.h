#pragma once

#include "Window/Window.h"

#include "Glad/include/glad/glad.h"
#include "GLFW/include/GLFW/glfw3.h"

#include <map>

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

	void SetKeyCallback(KEYCALLBACK callback) override;

	void MakeContextCurrent() override;

	void* GetNativeWindow() override { return m_WndHandle; }

private:

	static void ResizeCallback(GLFWwindow* window, int width, int height);

	static void InitKeyMap();

	static void AdaptKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:

	GLFWwindow* m_WndHandle;

	KEYCALLBACK m_KeyCallback;

	void* m_UserPointer;

	static std::map<int, eKey> s_KeyMap;
	static std::map<int, eKeyAction> s_KeyActionMap;
};

