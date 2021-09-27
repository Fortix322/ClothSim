#include <thread>

#include "Window/Window.h"
#include "OpenGL/OpenGL.h"
#include "Render/Renderer.h"
#include "Physics/ParticleSystem.h"

#include "GLFW/include/GLFW/glfw3.h"

void LoadGL()
{
	std::cout << gladLoadGL() << std::endl;
}

//std::vector<Vertex> CreateParticles(std::vector<glm::vec3> positions)
//{
//	std::vector<Vertex> particles;
//
//	for (size_t i = 0; i < positions.size(); i++)
//	{
//		Vertex v1;
//		v1.position[0] = positions[i].x - 0.01f;
//		v1.position[1] = positions[i].y - 0.01f;
//		v1.position[2] = positions[i].z;
//
//
//		Vertex v2;
//		v2.position[0] = positions[i].x + 0.01f;
//		v2.position[1] = positions[i].y - 0.01f;
//		v2.position[2] = positions[i].z;
//
//
//		Vertex v3;
//		v3.position[0] = positions[i].x - 0.01f;
//		v3.position[1] = positions[i].y + 0.01f;
//		v3.position[2] = positions[i].z;
//
//		Vertex v4;
//		v4.position[0] = positions[i].x + 0.01f;
//		v4.position[1] = positions[i].y + 0.01f;
//		v4.position[2] = positions[i].z;
//
//		particles.push_back(v1);
//		particles.push_back(v2);
//		particles.push_back(v3);
//		particles.push_back(v4);
//
//	}
//
//	return particles;
//}

int main()
{
	Window* win = Window::Create();
	win->MakeContextCurrent();

	LoadGL();

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

	Renderer::Init("res/test.vert.glsl", "res/test.frag.glsl");

	while (!glfwWindowShouldClose((GLFWwindow*)win->GetNativeWindow())) 
	{
		Renderer::DrawQuad({ 0.0f, 0.0f }, { 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f });
		Renderer::DrawSubmit();
		win->OnUpdate();
		Renderer::Flush();
		particles.Timestep();
		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}

	Renderer::Shutdown();
	win->Shutdown();

	delete win;
}