#include "GLFWWindow.h"

static uint8_t s_GlfwInstances = 0;

Window* Window::Create(WinProps props)
{
    return new GLFWWindow(props);
}

GLFWWindow::GLFWWindow(WinProps props)
{
    if (s_GlfwInstances == 0)
    {
        if (!glfwInit()) 
        {
            __debugbreak();
        }
    }

    m_WndHandle = glfwCreateWindow(props.width, props.height, props.name, NULL, NULL);
    s_GlfwInstances++;

    glfwSetWindowSizeCallback(m_WndHandle, GLFWWindow::ResizeCallback);
}

GLFWWindow::~GLFWWindow()
{
    if (m_WndHandle) Shutdown();

    s_GlfwInstances--;
    if (s_GlfwInstances == 0)
    {
        glfwTerminate();
    }

}

void GLFWWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_WndHandle);
}

void GLFWWindow::Shutdown() 
{
    glfwDestroyWindow(m_WndHandle);
    m_WndHandle = 0;
}

int GLFWWindow::GetWidth()
{
    int height, width;

    glfwGetFramebufferSize(m_WndHandle, &width, &height);

    return width;
}

int GLFWWindow::GetHeight()
{
    int height, width;

    glfwGetFramebufferSize(m_WndHandle, &width, &height);

    return height;
}

void GLFWWindow::SetUserPointer(void* pointer)
{
    glfwSetWindowUserPointer(m_WndHandle, pointer);
}

void GLFWWindow::MakeContextCurrent()
{
    glfwMakeContextCurrent(m_WndHandle);
}

void GLFWWindow::ResizeCallback(GLFWwindow* window, int width, int height)
{
    if(window == glfwGetCurrentContext())
        glViewport(0, 0, width, height);
}
