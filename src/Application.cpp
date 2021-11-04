#include "Window/Window.h"
#include "OpenGL/OpenGL.h"
#include "Render/Renderer.h"
#include "Physics/ParticleSystem.h"
#include "Physics/PhysicsSolver2D.h"

#include "GLFW/include/GLFW/glfw3.h"

#include <thread>
#include <chrono>

#include <map>

#define RANDOMFLOAT(min, max) min + (float)rand() / (float)RAND_MAX * (max - min)

void LoadGL()
{
	std::cout << gladLoadGL() << std::endl;
}

void KeyCallback(eKey key, int test, eKeyAction action)
{
	std::cout << "Key: " << (int)key << "Action: " << (int)action << std::endl;
}

int main()
{
	Window* win = Window::Create();
	win->MakeContextCurrent();

	LoadGL();

	Renderer::Init("res/test.vert.glsl", "res/test.frag.glsl");
	PhysicsSolver2D physic;

	//
	const int partCount = 10;

	physic.CreateParticle({ 0.0f, 1.0f }, false);

	for (size_t i = 0; i < partCount; i++)
	{
		physic.CreateParticle({0.0f, 0.9f - (i + 1)  * 0.09f});									// FOR TESTS
	}

	for (size_t i = 0; i < partCount; i++)
	{
		physic.CreateStick(i, i + 1, 3.2f);
	}
	//

	win->SetKeyCallback(KeyCallback);

	while (!glfwWindowShouldClose((GLFWwindow*)win->GetNativeWindow()))
	{
		Renderer::ClearScreen({ 0.577f, 0.577f, 0.577f, 1.0f });

		auto& part = physic.GetParticles();

		for (size_t i = 0; i < part.size(); i++)
		{
			Renderer::DrawQuad(part[i].GetPosition(), { 0.05f, 0.05f }, {0.0f, 0.0f, 0.0f, 0.0f});
		}

		auto& sticks = physic.GetSticks();

		{
			glm::vec2 lPos, rPos;
			for (size_t i = 0; i < sticks.size(); i++)
			{
				if (sticks[i].IsBroken()) continue;
				
				sticks[i].GetPositions(lPos, rPos);
				Renderer::DrawLine(lPos, rPos, { 0.0f, 0.0f, 0.0f, 0.0f });
			}
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