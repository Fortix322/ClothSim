#include "StickConstraint.h"

#include "glm/glm/geometric.hpp"

StickConstraint::StickConstraint(Particle* lParticle, Particle* rParticle, float restLength, float elogationRatio)
	: m_lParticle(lParticle), m_rParticle(rParticle), m_RestLength(restLength), m_ElogationRatio(elogationRatio)
{
	m_Broken = false;
}

void StickConstraint::Satisfy()
{
	if (IsBroken()) return;

	glm::vec2 delta = m_rParticle->GetPosition() - m_lParticle->GetPosition();

	float deltaLen = glm::length(delta);

	if (deltaLen < m_RestLength) return;

	if (deltaLen > m_RestLength * m_ElogationRatio)
	{
		m_Broken = true;
		return;
	}

	float diff = (deltaLen - m_RestLength) / deltaLen;

	m_lParticle->Move(delta * 0.5f * diff);
	m_rParticle->Move(-(delta * 0.5f * diff));
}

bool StickConstraint::IsBroken() const
{
	return m_Broken;
}

bool StickConstraint::GetPositions(glm::vec2& lPos, glm::vec2& rPos) const
{
	if (IsBroken())
	{
		return false;
	}
	
	lPos = m_lParticle->GetPosition();
	rPos = m_rParticle->GetPosition();
}

