#pragma once

#include "Particle.h"
#include "StickConstraint.h"

#include "glm/glm/vec2.hpp"

#include <vector>

class PhysicsSolver2D
{
public:

	PhysicsSolver2D() = default;

	~PhysicsSolver2D() = default;

	void Solve();

	const std::vector<Particle>& GetParticles() const;

	const std::vector<StickConstraint>& GetSticks() const;

	void CreateParticle(glm::vec2 pos, bool isMovable = true);

	void CreateStick(uint64_t lInd, uint64_t rInd, float elogationRatio);

	void DeleteParticle(uint64_t ind);

	void DeleteStick(uint64_t ind);

private:

	void CalculatePositions(float deltaTime);
	
	void SatisfyConstraints();

private:

	std::vector<Particle> m_Particles;
	std::vector<StickConstraint> m_Sticks;
	//Temp
	std::vector<glm::vec2> m_OldPos;
	std::vector<glm::vec2> m_Forces;

};