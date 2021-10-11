#include <thread>

#include "Window/Window.h"
#include "OpenGL/OpenGL.h"
#include "Render/Renderer.h"
#include "Physics/ParticleSystem.h"

#include "GLFW/include/GLFW/glfw3.h"

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

	ParticleSystem particles;

	//TODO
	std::vector<glm::vec3> test;
	std::vector<Joint> test2;

	for (size_t i = 0; i < 2; i++)
	{
		test.push_back({ RANDOMFLOAT(-1, 1), RANDOMFLOAT(-1, 1), 0.0f });
	}

	for (uint32_t i = 0; i < 2 - 1; i++)
	{
		test2.push_back({ i, i + 1, 0.5f });
	}

	particles.CreateParticles(test.size(), test.data());
	particles.CreateJoins(test2.size(), test2.data());
	//

	Renderer::Init("res/test.vert.glsl", "res/test.frag.glsl");
	while (!glfwWindowShouldClose((GLFWwindow*)win->GetNativeWindow()))
	{
		Renderer::ClearScreen({ 0.577f, 0.577f, 0.577f, 1.0f });
		auto& pos = particles.GetPositions();
		auto& joins = particles.GetJoins();

		for (size_t i = 0; i < pos.size(); i++)
		{
			Renderer::DrawQuad({ pos[i].x, pos[i].y }, { 0.025f, 0.025f }, { 1.0f, 1.0f, 1.0f, 1.0f });
		}

		for (size_t i = 0; i < joins.size(); i++)
		{
			Renderer::DrawLine({ pos[joins[i].rPointInd].x, pos[joins[i].rPointInd].y }, { pos[joins[i].lPointInd].x, pos[joins[i].lPointInd].y }, { 1.0f, 1.0f, 1.0f, 1.0f });
		}

		Renderer::DrawSubmit();
		Renderer::Flush();

		particles.Timestep();

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
		win->OnUpdate();
	}

	Renderer::Shutdown();
	win->Shutdown();

	delete win;
}