#include <thread>

#include "Window/Window.h"

#include "GLFW/glfw3.h"

int main()
{
	Window* win = Window::Create();

	while (!glfwWindowShouldClose((GLFWwindow*)win->GetNativeWindow()))
	{
		win->OnUpdate();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	win->Shutdown();
	delete win;
}