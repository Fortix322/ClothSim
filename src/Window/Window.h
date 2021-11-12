#pragma once
#include <iostream>

enum class eKey
{
	KEY_UNKNOWN = -1,

	KEY_Q,
	KEY_W,
	KEY_E,
	KEY_R,
	KEY_T,
	KEY_Y,
	KEY_U,
	KEY_I,
	KEY_O,
	KEY_P,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_F,
	KEY_G,
	KEY_H,
	KEY_J,
	KEY_K,
	KEY_L,
	KEY_Z,
	KEY_X,
	KEY_C,
	KEY_V,
	KEY_B,
	KEY_N,
	KEY_M,

	KEY_1,
	KEY_2,
	KEY_3,
	KEY_4,
	KEY_5,
	KEY_6,
	KEY_7,
	KEY_8,
	KEY_9,
	KEY_0,

	KEY_F1,
	KEY_F2,
	KEY_F3,
	KEY_F4,
	KEY_F5,
	KEY_F6,
	KEY_F7,
	KEY_F8,
	KEY_F9,
	KEY_F10,
	KEY_F11,
	KEY_F12,

	KEY_LEFT_BRACKET,
	KEY_RIGHT_BRACKET,
	KEY_SEMICOLON,
	KEY_APOSTROPHE,
	KEY_BACKSLASH,
	KEY_SLASH,
	KEY_COMMA,
	KEY_PERIOD,

	KEY_TAB,
	KEY_SHIFT,
	KEY_CONTROL,
	KEY_ALT,
	KEY_ESCAPE,
	KEY_ENTER,

	KEY_MOUSE_BUTTON_LEFT,
	KEY_MOUSE_BUTTON_RIGHT

};

enum class eKeyAction
{
	KEY_PRESS = 0,
	KEY_RELEASE,
	KEY_REPEAT
};

struct WinProps 
{
	const char* name;
	int width;
	int height;

	WinProps() 
	{
		name = "Window";
		width = 1280;
		height = 720;
	}
};

class Window;

typedef void (*KEYCALLBACK)(eKey scanCode, int specKey, eKeyAction status, Window* window);
typedef void (*MOUSECALLBACK)(eKey scanCode, eKeyAction status, double xPos, double yPos, Window* window);
typedef void (*CURSORCALLBACK)(double xPos, double yPos, Window* window);

class Window
{
public:

	static Window* Create(WinProps props = WinProps());

	virtual void OnUpdate() = 0;

	virtual void Shutdown() = 0;

	virtual int GetWidth() = 0;

	virtual int GetHeight() = 0;

	virtual void SetUserPointer(void* pointer) = 0;

	virtual void MakeContextCurrent() = 0;

	virtual void* GetNativeWindow() = 0;

	virtual void SetKeyCallback(KEYCALLBACK callback) = 0;

	virtual void SetMouseButtonCallback(MOUSECALLBACK callback) = 0;

	virtual void SetCursorCallback(CURSORCALLBACK callback) = 0;

	virtual ~Window() {}
};
