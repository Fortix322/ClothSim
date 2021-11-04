#include "GLFWWindow.h"

std::map<int, eKey> GLFWWindow::s_KeyMap;
std::map<int, eKeyAction> GLFWWindow::s_KeyActionMap;

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

		InitKeyMap();
    }

    m_WndHandle = glfwCreateWindow(props.width, props.height, props.name, NULL, NULL);
    s_GlfwInstances++;

	glfwSetWindowUserPointer(m_WndHandle, this);
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
	m_UserPointer = pointer;
}

void GLFWWindow::SetKeyCallback(KEYCALLBACK callback)
{
    m_KeyCallback = callback;
    glfwSetKeyCallback(m_WndHandle, &GLFWWindow::AdaptKeyCallback);
}

void GLFWWindow::MakeContextCurrent()
{
    glfwMakeContextCurrent(m_WndHandle);
}

void GLFWWindow::ResizeCallback(GLFWwindow* window, int width, int height)
{
    if (window == glfwGetCurrentContext())
    {
        glViewport(0, 0, width, height);
    }
}

void GLFWWindow::InitKeyMap()
{
	s_KeyMap[GLFW_KEY_Q] =				eKey::KEY_W;
	s_KeyMap[GLFW_KEY_W] =				eKey::KEY_W;
	s_KeyMap[GLFW_KEY_E] =				eKey::KEY_E;
	s_KeyMap[GLFW_KEY_R] =				eKey::KEY_R;
	s_KeyMap[GLFW_KEY_T] =				eKey::KEY_T;
	s_KeyMap[GLFW_KEY_Y] =				eKey::KEY_Y;
	s_KeyMap[GLFW_KEY_U] =				eKey::KEY_U;
	s_KeyMap[GLFW_KEY_I] =				eKey::KEY_I;
	s_KeyMap[GLFW_KEY_O] =				eKey::KEY_O;
	s_KeyMap[GLFW_KEY_P] =				eKey::KEY_P;
	s_KeyMap[GLFW_KEY_A] =				eKey::KEY_A;
	s_KeyMap[GLFW_KEY_S] =				eKey::KEY_S;
	s_KeyMap[GLFW_KEY_D] =				eKey::KEY_D;
	s_KeyMap[GLFW_KEY_F] =				eKey::KEY_F;
	s_KeyMap[GLFW_KEY_G] =				eKey::KEY_G;
	s_KeyMap[GLFW_KEY_H] =				eKey::KEY_H;
	s_KeyMap[GLFW_KEY_J] =				eKey::KEY_J;
	s_KeyMap[GLFW_KEY_K] =				eKey::KEY_K;
	s_KeyMap[GLFW_KEY_L] =				eKey::KEY_L;
	s_KeyMap[GLFW_KEY_Z] =				eKey::KEY_Z;
	s_KeyMap[GLFW_KEY_X] =				eKey::KEY_X;
	s_KeyMap[GLFW_KEY_C] =				eKey::KEY_C;
	s_KeyMap[GLFW_KEY_V] =				eKey::KEY_V;
	s_KeyMap[GLFW_KEY_B] =				eKey::KEY_B;
	s_KeyMap[GLFW_KEY_N] =				eKey::KEY_N;
	s_KeyMap[GLFW_KEY_M] =				eKey::KEY_M;

	s_KeyMap[GLFW_KEY_1] =				eKey::KEY_1;
	s_KeyMap[GLFW_KEY_2] =				eKey::KEY_2;
	s_KeyMap[GLFW_KEY_3] =				eKey::KEY_3;
	s_KeyMap[GLFW_KEY_4] =				eKey::KEY_4;
	s_KeyMap[GLFW_KEY_5] =				eKey::KEY_5;
	s_KeyMap[GLFW_KEY_6] =				eKey::KEY_6;
	s_KeyMap[GLFW_KEY_7] =				eKey::KEY_7;
	s_KeyMap[GLFW_KEY_8] =				eKey::KEY_8;
	s_KeyMap[GLFW_KEY_9] =				eKey::KEY_9;
	s_KeyMap[GLFW_KEY_0] =				eKey::KEY_0;

	s_KeyMap[GLFW_KEY_F1] =				eKey::KEY_F1;
	s_KeyMap[GLFW_KEY_F2] =				eKey::KEY_F2;
	s_KeyMap[GLFW_KEY_F3] =				eKey::KEY_F3;
	s_KeyMap[GLFW_KEY_F4] =				eKey::KEY_F4;
	s_KeyMap[GLFW_KEY_F5] =				eKey::KEY_F5;
	s_KeyMap[GLFW_KEY_F6] =				eKey::KEY_F6;
	s_KeyMap[GLFW_KEY_F7] =				eKey::KEY_F7;
	s_KeyMap[GLFW_KEY_F8] =				eKey::KEY_F8;
	s_KeyMap[GLFW_KEY_F9] =				eKey::KEY_F9;
	s_KeyMap[GLFW_KEY_F10] =			eKey::KEY_F10;
	s_KeyMap[GLFW_KEY_F11] =			eKey::KEY_F11;
	s_KeyMap[GLFW_KEY_F12] =			eKey::KEY_F12;

	s_KeyMap[GLFW_KEY_LEFT_BRACKET]	=	eKey::KEY_LEFT_BRACKET;
	s_KeyMap[GLFW_KEY_RIGHT_BRACKET] =	eKey::KEY_RIGHT_BRACKET;
	s_KeyMap[GLFW_KEY_SEMICOLON] =		eKey::KEY_SEMICOLON;
	s_KeyMap[GLFW_KEY_APOSTROPHE] =		eKey::KEY_APOSTROPHE;
	s_KeyMap[GLFW_KEY_BACKSLASH] =		eKey::KEY_BACKSLASH;
	s_KeyMap[GLFW_KEY_SLASH] =			eKey::KEY_SLASH;
	s_KeyMap[GLFW_KEY_COMMA] =			eKey::KEY_COMMA;
	s_KeyMap[GLFW_KEY_PERIOD] =			eKey::KEY_PERIOD;

	s_KeyMap[GLFW_KEY_TAB] =			eKey::KEY_TAB;
	s_KeyMap[GLFW_KEY_LEFT_SHIFT] =		eKey::KEY_SHIFT;
	s_KeyMap[GLFW_KEY_LEFT_CONTROL] =	eKey::KEY_CONTROL;
	s_KeyMap[GLFW_KEY_LEFT_ALT] =		eKey::KEY_ALT;
	s_KeyMap[GLFW_KEY_ESCAPE] =			eKey::KEY_ESCAPE;
	s_KeyMap[GLFW_KEY_ENTER] =			eKey::KEY_ENTER;

	s_KeyActionMap[GLFW_PRESS] =		eKeyAction::KEY_PRESS;
	s_KeyActionMap[GLFW_RELEASE] =		eKeyAction::KEY_RELEASE;
	s_KeyActionMap[GLFW_REPEAT] =		eKeyAction::KEY_REPEAT;
}

void GLFWWindow::AdaptKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	GLFWWindow* owner = (GLFWWindow*)glfwGetWindowUserPointer(window);

	if (owner == NULL) __debugbreak();

	owner->m_KeyCallback(s_KeyMap[key], mods, s_KeyActionMap[action]);
}
