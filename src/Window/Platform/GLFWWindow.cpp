#include "GLFWWindow.h"

static uint8_t s_glfwInstances = 0;

Window* Window::Create(WinProps props)
{
    return new GLFWWindow(props);
}

GLFWWindow::GLFWWindow(WinProps props)
{
    if (s_glfwInstances == 0) 
    {
        if (!glfwInit()) 
        {
            __debugbreak();
        }
    }

    m_wndHandle = glfwCreateWindow(props.width, props.height, props.name, NULL, NULL);
    s_glfwInstances++;
}

GLFWWindow::~GLFWWindow()
{
    if (m_wndHandle) Shutdown();

    s_glfwInstances--;
    if (s_glfwInstances == 0)
    {
        glfwTerminate();
    }

}

void GLFWWindow::OnUpdate()
{
    glfwPollEvents();
    glfwSwapBuffers(m_wndHandle);
}

void GLFWWindow::Shutdown() 
{
    glfwDestroyWindow(m_wndHandle);
    m_wndHandle = 0;
}

int GLFWWindow::GetWidth()
{
    int height, width;

    glfwGetFramebufferSize(m_wndHandle, &width, &height);

    return width;
}

int GLFWWindow::GetHeight()
{
    int height, width;

    glfwGetFramebufferSize(m_wndHandle, &width, &height);

    return height;
}

void GLFWWindow::SetUserPointer(void* pointer)
{
}
