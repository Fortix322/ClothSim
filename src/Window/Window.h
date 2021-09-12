#include <iostream>

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

	virtual ~Window() {}
};