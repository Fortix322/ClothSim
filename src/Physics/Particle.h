#pragma once

#include "glm/glm/vec2.hpp"

class Particle
{
public:

	Particle(glm::vec2 pos, bool isMovable = true);

	~Particle();

	void Move(glm::vec2 transform);

	const glm::vec2& GetPosition() const;

	bool IsMovable() const;

private:

	glm::vec2 m_Pos;
	bool m_Movable;
}; 
