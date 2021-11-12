#include "Window/Window.h"
#include "OpenGL/OpenGL.h"
#include "Render/Renderer.h"
#include "Physics/ParticleSystem.h"
#include "Physics/PhysicsSolver2D.h"
#include "Input.h"

#include "GLFW/include/GLFW/glfw3.h"

#include <thread>
#include <chrono>

#include <map>

#define RANDOMFLOAT(min, max) min + (float)rand() / (float)RAND_MAX * (max - min)

PhysicsSolver2D physic;

void LoadGL()
{
	std::cout << gladLoadGL() << std::endl;
}

static void CreateCloth(PhysicsSolver2D& physicsSolver)
{
	const glm::vec2 startPos = { -0.85f, 1.0f };
	const glm::vec2 endPos = { 0.85f, 1.0f };
	const uint64_t partInRow = 100;
	const uint64_t countOfRows = 70;
	const float restLength = 0.01f;
	const float elogation = 100.2f;

	const glm::vec2 deltaPos = { (glm::length(endPos - startPos)) / partInRow, -(glm::length(endPos - startPos)) / partInRow };

	bool isMovable = false;

	for (size_t i = 0; i < countOfRows; i++)
	{
		if (i > 0) isMovable = true;

		for (size_t j = 0; j < partInRow; j++)
		{
			physicsSolver.CreateParticle(startPos + deltaPos * glm::vec2((float)j, (float)i), isMovable);
		}
	}

	for (size_t i = 0; i < countOfRows; i++)
	{
		for (size_t j = 0; j < partInRow; j++)
		{
			if (i != 0) physicsSolver.CreateStick(j + i * partInRow, j + (i - 1) * partInRow, elogation);
			if (j != partInRow - 1) physicsSolver.CreateStick(j + i * partInRow, j + i * partInRow + 1, elogation);
		}
	}
}

int main()
{
	Window* win = Window::Create();
	win->MakeContextCurrent();

	LoadGL();

	Renderer::Init("res/main.vert.glsl", "res/main.frag.glsl");

	/*physic.CreateParticle({0.0f, 1.0f}, false);
	physic.CreateParticle({ 0.0f, 0.0f });
	physic.CreateStick(0, 1, 3.2f);*/
	CreateCloth(physic);

	win->SetMouseButtonCallback(&Input::MouseCallback);
	win->SetCursorCallback(&Input::CursorCallback);

	while (!glfwWindowShouldClose((GLFWwindow*)win->GetNativeWindow()))
	{
		Renderer::ClearScreen({ 0.577f, 0.577f, 0.577f, 1.0f });

		auto& part = physic.GetParticles();

		for (size_t i = 0; i < part.size(); i++)
		{
			Renderer::DrawQuad(part[i].GetPosition(), { 0.0005f, 0.0005f }, {0.0f, 0.0f, 0.0f, 0.0f});
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