#include <thread>

#include "Window/Window.h"
#include "OpenGL/OpenGL.h"
#include "Render/BatchRenderer.h"
#include "GLFW/glfw3.h"
#include "Physics/ParticleSystem.h"

void LoadGL()
{
	std::cout << gladLoadGL() << std::endl;
}

std::vector<Vertex> CreateParticles(std::vector<glm::vec3> positions)
{
	std::vector<Vertex> particles;

	for (size_t i = 0; i < positions.size(); i++)
	{
		Vertex v1;
		v1.position[0] = positions[i].x - 0.01f;
		v1.position[1] = positions[i].y - 0.01f;
		v1.position[2] = positions[i].z;


		Vertex v2;
		v2.position[0] = positions[i].x + 0.01f;
		v2.position[1] = positions[i].y - 0.01f;
		v2.position[2] = positions[i].z;


		Vertex v3;
		v3.position[0] = positions[i].x - 0.01f;
		v3.position[1] = positions[i].y + 0.01f;
		v3.position[2] = positions[i].z;

		Vertex v4;
		v4.position[0] = positions[i].x + 0.01f;
		v4.position[1] = positions[i].y + 0.01f;
		v4.position[2] = positions[i].z;

		particles.push_back(v1);
		particles.push_back(v2);
		particles.push_back(v3);
		particles.push_back(v4);

	}

	return particles;
}

int main()
{
	Window* win = Window::Create();
	win->MakeContextCurrent();

	LoadGL();

	BatchRenderer render("res/test.vert.glsl", "res/test.frag.glsl");
	ParticleSystem particles;

	/*float quad[] =
	{
		-0.8f, -0.5f, 0.0f,
		-0.4f, -0.5f, 0.0f,
		-0.8f,  0.5f, 0.0f,
		-0.4f,  0.5f, 0.0f,

		 0.8f, -0.5f, 0.0f,
		 0.4f, -0.5f, 0.0f,
		 0.8f,  0.5f, 0.0f,
		 0.4f,  0.5f, 0.0f
	};*/

	render.SetLayout(Vertex::GetLayout());

	while (!glfwWindowShouldClose((GLFWwindow*)win->GetNativeWindow())) 
	{
		auto test = CreateParticles(particles.GetPositions());
		render.StreamData(test.data(), test.size() * sizeof(Vertex));
		render.Draw();
		win->OnUpdate();
		render.Flush();
		particles.Timestep();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	win->Shutdown();

	delete win;
}