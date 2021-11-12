#pragma once

#include <iostream>

#include "Window/Window.h"

class Input
{
public:

	static void MouseCallback(eKey key, eKeyAction action, double xPos, double yPos, Window* window);

	static void CursorCallback(double xPos, double yPos, Window* window);

private:

	static bool LMBPressed;
	static bool RMBPressed;
};

