#pragma once

#include "Particle.h"

class StickConstraint
{
public:

	StickConstraint(Particle* lParticle, Particle* rParticle, float restLength, float elogationRatio);

	~StickConstraint() = default;

	void Satisfy();

	bool IsBroken() const;

	bool GetPositions(glm::vec2& lPos, glm::vec2& rPos) const;

private:

	Particle* m_lParticle;
	Particle* m_rParticle;

	float m_RestLength;
	float m_ElogationRatio;

	bool m_Broken;
};

