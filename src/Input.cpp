#include "Input.h"

#include "Physics/PhysicsSolver2D.h"

#include <vector>

extern PhysicsSolver2D physic;

struct Coordinate
{
	double x = 0.0f;
	double y = 0.0f;
};

struct Line
{
	Coordinate leftPnt;
	Coordinate rightPnt;
};

bool Input::LMBPressed = false;
bool Input::RMBPressed = false;

std::vector<uint64_t> FindCollisions(Line current, std::vector<Line>& vecLines)
{
	std::vector<uint64_t> ind;

	for (size_t i = 0; i < vecLines.size(); i++)
	{
		Line& line = vecLines[i];

		float bezierT = ((current.leftPnt.x - line.leftPnt.x) * (line.leftPnt.y - line.rightPnt.y) -
						(current.leftPnt.y - line.leftPnt.y) * (line.leftPnt.x - line.rightPnt.x)) / 
						((current.leftPnt.x - current.rightPnt.x) * (line.leftPnt.y - line.rightPnt.y) - 
						(current.leftPnt.y - current.rightPnt.y) * (line.leftPnt.x - line.rightPnt.x));

		float bezierU = ((current.leftPnt.x - line.leftPnt.x) * (current.leftPnt.y - current.rightPnt.y) -
							(current.leftPnt.y - line.leftPnt.y) * (current.leftPnt.x - current.rightPnt.x)) /
							((current.leftPnt.x - current.rightPnt.x) * (line.leftPnt.y - line.rightPnt.y) -
							(current.leftPnt.y - current.rightPnt.y) * (line.leftPnt.x - line.rightPnt.x));

		if (bezierT <= 0.0f || bezierT >= 1.0f || bezierU <= 0.0f || bezierU >= 1.0f) continue;

		ind.push_back(i);
	}

	return ind;
}

void Input::MouseCallback(eKey key, eKeyAction action, double xPos, double yPos, Window* window)
{
	if (key == eKey::KEY_UNKNOWN || action == eKeyAction::KEY_REPEAT) return;

	if (key == eKey::KEY_MOUSE_BUTTON_LEFT) Input::LMBPressed = action == eKeyAction::KEY_PRESS ? true : false;

	if (key == eKey::KEY_MOUSE_BUTTON_RIGHT) Input::RMBPressed = action == eKeyAction::KEY_PRESS ? true : false;
}

void Input::CursorCallback(double xPos, double yPos, Window* window)
{
	static Coordinate prevCoord;

	xPos = (2.0f * xPos / window->GetWidth() - 1);
	yPos = -(2.0f * yPos / window->GetHeight() - 1);

	Coordinate current = { xPos, yPos };

	if (LMBPressed)
	{
		auto sticks = physic.GetSticks();

		glm::vec2 lPos, rPos;
		std::vector<Line> coords;
		for (StickConstraint& s : sticks)
		{
			s.GetPositions(lPos, rPos);
			coords.push_back({ {lPos.x, lPos.y}, {rPos.x, rPos.y} });
		}
		auto collisions = FindCollisions({ prevCoord, current }, coords);
		for (size_t i = 0; i < collisions.size(); i++)
		{
			physic.DeleteStick(collisions[i]);
		}
	}

	prevCoord = current;
}