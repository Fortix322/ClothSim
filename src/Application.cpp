#include <thread>

#include "Window/Window.h"
#include "OpenGL/OpenGL.h"
#include "Render/BatchRenderer.h"
#include "GLFW/glfw3.h"

void LoadGL()
{
	std::cout << gladLoadGL() << std::endl;
}

int main()
{
	Window* win = Window::Create();
	win->MakeContextCurrent();

	LoadGL();

	BatchRenderer render("RayCasting/res/test.vert.glsl", "RayCasting/res/test.frag.glsl");

	while (!glfwWindowShouldClose((GLFWwindow*)win->GetNativeWindow()))
	{
		win->OnUpdate();
		render.Draw();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	win->Shutdown();
	delete win;
}