#pragma once

#include <vector>

#include "vendor/glm/glm/vec3.hpp"

class ParticleSystem
{
public:

	ParticleSystem();
	
	~ParticleSystem();

	void Timestep();

	const std::vector<glm::vec3>& GetPositions() const { return m_ParticlesPos; }

private:

	void CalculatePositions();

	void ApplyForces();

private:

	std::vector<glm::vec3> m_ParticlesPos;
	std::vector<glm::vec3> m_OldParticlesPos;
	std::vector<glm::vec3> m_Forces;

	/*float additionalForce = 0.0f;*/

	float m_Deltatime;

	static const uint32_t s_MaxParticles = 20;
	const float s_Gravity = -10.0f;
};

