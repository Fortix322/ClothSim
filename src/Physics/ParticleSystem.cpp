#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
	: m_Forces(s_MaxParticles), m_ParticlesPos(s_MaxParticles), m_OldParticlesPos(s_MaxParticles)
{
	for (size_t i = 0; i < s_MaxParticles; i++)
	{
		m_ParticlesPos[i] = glm::vec3(-0.99f + 0.1 * i, 1.0f, 0.0f);
		m_OldParticlesPos[i] = glm::vec3(-0.99f + 0.1 * i, 1.0f, 0.0f);
	}
}

ParticleSystem::~ParticleSystem()
{
	
}

void ParticleSystem::Timestep()
{
	float frequency = 60.0f;
	m_Deltatime = 1.0f / frequency;

	ApplyForces();
	CalculatePositions();
}

void ParticleSystem::CalculatePositions()
{
	for (size_t i = 0; i < s_MaxParticles; i++)
	{
		auto prevPos = m_ParticlesPos[i];
		m_ParticlesPos[i] = 2.0f * m_ParticlesPos[i] - m_OldParticlesPos[i] + m_Forces[i] * m_Deltatime * m_Deltatime;
		m_OldParticlesPos[i] = prevPos;

		//additionalForce = 0.0f;

		//if (m_ParticlesPos[i].y < -1.0f)
		//{
		//	//m_ParticlesPos[i].y = 1.0f;
		//	//m_OldParticlesPos[i].y = 1.0f;

		//	additionalForce = 30.0f;
		//}

	}
}

void ParticleSystem::ApplyForces()
{
	for (size_t i = 0; i < s_MaxParticles; i++)
	{
		m_Forces[i].x = 0.0f;
		m_Forces[i].y = s_Gravity/* + additionalForce*/;
		m_Forces[i].z = 0.0f;
	}
}
