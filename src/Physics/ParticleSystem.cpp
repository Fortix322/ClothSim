#include "ParticleSystem.h"

static const uint16_t s_ThreadCount = std::thread::hardware_concurrency();

float RandomFloat(float min, float max)
{
	// this  function assumes max > min, you may want 
	// more robust error checking for a non-debug build
	assert(max > min);
	float random = ((float)rand()) / (float)RAND_MAX;

	// generate (in your case) a float between 0 and (4.5-.78)
	// then add .78, giving you a float between .78 and 4.5
	float range = max - min;
	return (random * range) + min;
}

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
	: m_Forces(s_MaxParticles), m_ParticlesPos(s_MaxParticles), m_OldParticlesPos(s_MaxParticles)
{
	for (size_t i = 0; i < s_MaxParticles; i++)
	{
		m_ParticlesPos[i] = glm::vec3(RandomFloat(-1.0f, 1.0f), RandomFloat(-1.0f, 1.0f), 0.0f);
		//m_ParticlesPos[i] = glm::vec3(0.0f, 0.0f, 0.0f);
		m_OldParticlesPos[i] = m_ParticlesPos[i];
	}
	m_ParticlesPos[1] = glm::vec3(0.2f, 0.0f, 0.0f);

	m_Joins.push_back(Joint(0, 1, 0.5f));
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

void ParticleSystem::CalculatePositions()
{
	/*auto lambda = [&](uint32_t index, uint32_t offset)
	{
		for (; offset; offset--)
		{
			auto prevPos = m_ParticlesPos[index];
			m_ParticlesPos[index] = 2.0f * m_ParticlesPos[index] - m_OldParticlesPos[index] + m_Forces[index] * m_Deltatime * m_Deltatime;
			m_OldParticlesPos[index] = prevPos;
			index += s_ThreadCount;
		}
	};*/

#define ASYNC 0

#if ASYNC

	std::vector<std::thread> workers;

	uint32_t offset = m_ParticlesPos.size() / s_ThreadCount;
	uint32_t additionalOffset = m_ParticlesPos.size() % s_ThreadCount;

	for (size_t i = 0; i < s_ThreadCount; i++)
	{
		workers.push_back(std::thread(lambda, i, i < additionalOffset ? offset + 1 : offset));
	}

	for (size_t i = 0; i < s_ThreadCount; i++)
	{
		workers[i].join();
	}

#else

	for (size_t i = 0; i < m_ParticlesPos.size(); i++)
	{
		auto prevPos = m_ParticlesPos[i];
		m_ParticlesPos[i] = 2.0f * m_ParticlesPos[i] - m_OldParticlesPos[i] + m_Forces[i] * m_Deltatime * m_Deltatime;
		m_OldParticlesPos[i] = prevPos;
	}

#endif
}

void ParticleSystem::ApplyForces()
{
	for (size_t i = 0; i < s_MaxParticles; i++)
	{
		m_Forces[i].x = 0.0f;
		m_Forces[i].y = s_Gravity;
		m_Forces[i].z = 0.0f;
	}
}

void ParticleSystem::SatisfyConstraints()
{
	static const uint16_t s_MaxIterations = 10;

	for (size_t i = 0; i < s_MaxIterations; i++)
	{
		for (size_t i = 0; i < m_ParticlesPos.size(); i++)
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

		m_ParticlesPos[0] *= 0.0f;
	}
}
