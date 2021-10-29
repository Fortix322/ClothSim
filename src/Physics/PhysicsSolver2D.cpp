#include "PhysicsSolver2D.h"

#include <algorithm>
#include <iostream>

static glm::vec2 vmin(const glm::vec2& lvec, const glm::vec2& rvec)
{
	return glm::vec2(fmin(lvec.x, rvec.x), fmin(lvec.y, rvec.y));
}

static glm::vec2 vmax(const glm::vec2& lvec, const glm::vec2& rvec)
{
	return glm::vec2(fmax(lvec.x, rvec.x), fmax(lvec.y, rvec.y));
}

static glm::vec2 clamp(const glm::vec2& vec, const glm::vec2& min, const glm::vec2& max)
{
	return vmin(vmax(vec, min), max);
}

PhysicsSolver2D::PhysicsSolver2D()
{
}

PhysicsSolver2D::~PhysicsSolver2D()
{
}

void PhysicsSolver2D::Solve()
{
	static const uint32_t s_Iterations = 1;

	float frequency = 60.0f;
	float deltaTime = 1.0f / frequency;

	auto t = std::chrono::high_resolution_clock::now();

	for (Particle& p : m_Particles)
	{
		p.Solve(deltaTime);
	}

	std::cout << "Calculate positions (SINGLE): " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t).count() << std::endl;

	t = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < s_Iterations; i++)
	{
		for(Stick& s : m_Sticks)
			m_Sticks[i].Solve();
	}
}

const std::vector<Particle>& PhysicsSolver2D::GetParticles() const
{
	return m_Particles;
}

void PhysicsSolver2D::AddParticles(Particle* data, uint64_t count)
{
	for (uint64_t i = 0; i < count; i++)
	{
		m_Particles.push_back(data[i]);
	}
}
