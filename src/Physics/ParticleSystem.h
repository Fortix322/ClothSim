#pragma once

#include <vector>
#include <thread>

#include <chrono>
#include <iostream>

#include "glm/glm/vec3.hpp"
#include "glm/glm/geometric.hpp"

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

class ParticleSystem
{
public:

	ParticleSystem();
	
	~ParticleSystem();

	void Timestep();

	void CreateJoins(uint32_t count, const Joint* pairsIndices);

	bool CreateParticles(uint32_t count, const glm::vec3* data);

	const std::vector<glm::vec3>& GetPositions() const { return m_ParticlesPos; }

	const std::vector<Joint>& GetJoins() const { return m_Joins; }

private:

	void CalculatePositions();

	void ApplyForces();

	void SatisfyConstraints();

private:

	std::vector<glm::vec3> m_ParticlesPos;
	std::vector<glm::vec3> m_OldParticlesPos;
	std::vector<glm::vec3> m_Forces;

	std::vector<Joint> m_Joins;

	uint32_t m_ParticlesCount = 0;
	float m_Deltatime;

	static const uint32_t s_MaxParticles = 100000;
	const float s_Gravity = -10.0f;

};

