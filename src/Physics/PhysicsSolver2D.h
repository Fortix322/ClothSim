#pragma once

#include "Particle.h"

#include "glm/glm/vec2.hpp"

#include <vector>

class PhysicsSolver2D
{
public:

	PhysicsSolver2D();

	~PhysicsSolver2D();

	void Solve();

	const std::vector<Particle>& GetParticles() const;

	void AddParticles(Particle* data, uint64_t count);

private:

	std::vector<Particle> m_Particles;
};