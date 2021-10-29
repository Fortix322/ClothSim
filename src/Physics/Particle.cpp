#include "Particle.h"

Particle::Particle(glm::vec2 pos, bool isMovable)
	: m_Pos(pos), m_Movable(isMovable)
{
}

Particle::~Particle()
{
}

void Particle::Move(glm::vec2 transform)
{
	if(IsMovable())
		m_Pos += transform;
}

const glm::vec2& Particle::GetPosition() const
{
	return m_Pos;
}

bool Particle::IsMovable() const
{
	return m_Movable;
}

