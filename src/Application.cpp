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

	float quad[] =
	{
		-0.25f, -0.25f, 0.0f,
		 0.25f, -0.25f, 0.0f,
		-0.25f,  0.25f, 0.0f,
		 0.25f,  0.25f, 0.0f
	};
	unsigned int ind[] =
	{
		0, 1, 2,
		1, 2, 3
	};

	VertexLayout layout;
	layout.Push<float>(3);

	render.SetLayout(layout);

	while (!glfwWindowShouldClose((GLFWwindow*)win->GetNativeWindow()))
	{
		render.StreamData(quad, sizeof(quad));
		render.Draw();
		win->OnUpdate();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	win->Shutdown();
	delete win;
}