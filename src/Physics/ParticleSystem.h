#pragma once

#include <vector>

#include "glm/glm/vec3.hpp"
#include "glm/glm/geometric.hpp"

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

	void SatisfyConstraints();

private:

	struct Joint
	{
		unsigned int rPointInd, lPointInd;
		float distance;

		Joint(unsigned int rInd, unsigned int lInd, float dist = 0)
		{
			rPointInd = rInd;
			lPointInd = lInd;
			distance = dist;
		}
	};

	std::vector<glm::vec3> m_ParticlesPos;
	std::vector<glm::vec3> m_OldParticlesPos;
	std::vector<glm::vec3> m_Forces;
	std::vector<float> m_Mass;

	std::vector<Joint> m_Joins;

	float m_Deltatime;

	static const uint32_t s_MaxParticles = 2;
	const float s_Gravity = -10.0f;

};

