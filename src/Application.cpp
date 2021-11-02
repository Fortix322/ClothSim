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

	/*Particle test = Particle({ 0.0f, 0.0f });
	Particle test2 = Particle({ 0.25f, 0.0f });
	Particle test3 = Particle({ 0.32f, 0.55f });

	physic.AddParticles(&test, 1);
	physic.AddParticles(&test2, 1);							// FOR TESTS
	physic.AddParticles(&test3, 1);

	physic.CreateStick(0, 1, 1.5f);
	physic.CreateStick(1, 2, 1.5f);
	physic.CreateStick(0, 2, 1.5f);*/

	while (!glfwWindowShouldClose((GLFWwindow*)win->GetNativeWindow()))
	{
		Renderer::ClearScreen({ 0.577f, 0.577f, 0.577f, 1.0f });

		auto& part = physic.GetParticles();

		for (size_t i = 0; i < part.size(); i++)
		{
			Renderer::DrawQuad(part[i].GetPosition(), { 0.05f, 0.05f }, {0.0f, 0.0f, 0.0f, 0.0f});
		}

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