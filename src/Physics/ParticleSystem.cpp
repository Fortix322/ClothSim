#include "ParticleSystem.h"

static const uint16_t s_ThreadCount = std::thread::hardware_concurrency();

static glm::vec3 vmin(const glm::vec3& lvec, const glm::vec3& rvec)
{
	return glm::vec3(fmin(lvec.x, rvec.x), fmin(lvec.y, rvec.y), fmin(lvec.z, rvec.z));
}

static glm::vec3 vmax(const glm::vec3& lvec, const glm::vec3& rvec)
{
	return glm::vec3(fmax(lvec.x, rvec.x), fmax(lvec.y, rvec.y), fmax(lvec.z, rvec.z));
}

static glm::vec3 clamp(const glm::vec3& vec, const glm::vec3& min, const glm::vec3& max)
{
	return vmin(vmax(vec, min), max);
}

ParticleSystem::ParticleSystem()
{
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
	SatisfyConstraints();
}

bool ParticleSystem::CreateParticles(uint32_t count, const glm::vec3* data)
{
	if (count + m_ParticlesCount > s_MaxParticles) return false;

	for (uint32_t i = 0; i < count; i++)
	{
		m_ParticlesPos.push_back(data[i]);
		m_Forces.push_back({0.0f, 0.0f, 0.0f});
	}

	m_OldParticlesPos = m_ParticlesPos;

	m_ParticlesCount += count;

	return true;
}

void ParticleSystem::CreateJoins(uint32_t count, const Joint* pairsIndices)
{
	for (uint32_t i = 0; i < count; i++)
	{
		m_Joins.push_back(pairsIndices[i]);
	}
}

void ParticleSystem::CalculatePositions()
{
	auto t = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < m_ParticlesCount; i++)
	{
		auto prevPos = m_ParticlesPos[i];
		m_ParticlesPos[i] = 2.0f * m_ParticlesPos[i] - m_OldParticlesPos[i] + m_Forces[i] * m_Deltatime * m_Deltatime;
		m_OldParticlesPos[i] = prevPos;
	}

	std::cout << "Calculate positions (SINGLE): " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t).count() << std::endl;
}

void ParticleSystem::ApplyForces()
{
	for (size_t i = 0; i < m_ParticlesCount; i++)
	{
		m_Forces[i].x = 0.0f;
		m_Forces[i].y = s_Gravity;
		m_Forces[i].z = 0.0f;
	}
}

void ParticleSystem::SatisfyConstraints()
{
	static const uint16_t s_MaxIterations = 10;

	auto t = std::chrono::high_resolution_clock::now();

	for (size_t i = 0; i < s_MaxIterations; i++)
	{
		for (size_t i = 0; i < m_ParticlesCount; i++)
		{
			m_ParticlesPos[i] = clamp(m_ParticlesPos[i], glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
		}

		for (size_t i = 0; i < m_Joins.size(); i++)
		{
			glm::vec3 delta = m_ParticlesPos[m_Joins[i].rPointInd] - m_ParticlesPos[m_Joins[i].lPointInd];
			float deltaLen = sqrt(glm::dot(delta, delta));
			float diff = (deltaLen - m_Joins[i].distance) / deltaLen;
			m_ParticlesPos[m_Joins[i].lPointInd] += delta * 0.5f * diff;
			m_ParticlesPos[m_Joins[i].rPointInd] -= delta * 0.5f * diff;
		}

		if (m_ParticlesCount >= 1) m_ParticlesPos[0] = {0.0f, 1.0f, 0.0f};
	}

	std::cout << "Solve constraints (SINGLE) : " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - t).count() << std::endl;

}
