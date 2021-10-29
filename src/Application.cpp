#include "Window/Window.h"
#include "OpenGL/OpenGL.h"
#include "Render/Renderer.h"
#include "Physics/ParticleSystem.h"
#include "Physics/PhysicsSolver2D.h"

#include "GLFW/include/GLFW/glfw3.h"

#include <thread>
#include <chrono>

#define RANDOMFLOAT(min, max) min + (float)rand() / (float)RAND_MAX * (max - min)

void LoadGL()
{
	std::cout << gladLoadGL() << std::endl;
}

int main()
{
	Window* win = Window::Create();
	win->MakeContextCurrent();

	LoadGL();

	Renderer::Init("res/test.vert.glsl", "res/test.frag.glsl");
	PhysicsSolver2D physic;

	while (!glfwWindowShouldClose((GLFWwindow*)win->GetNativeWindow()))
	{
		Renderer::ClearScreen({ 0.577f, 0.577f, 0.577f, 1.0f });

		Renderer::DrawSubmit();
		Renderer::Flush();

		physic.Solve();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		win->OnUpdate();
	}

	Renderer::Shutdown();
	win->Shutdown();

	delete win;
}