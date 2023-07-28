#include "Random.h"

Random::Random()
{
}

Random::~Random()
{
}

void Random::Seed()
{
	m_RandomEngine.seed(m_RD());
}

float Random::Range(float Min, float Max)
{
	std::uniform_real_distribution<> dist(Min, Max);

	return dist(m_RandomEngine);
}

int Random::Range(int Min, int Max)
{
	std::uniform_int_distribution<> dist(Min, Max);

	return dist(m_RandomEngine);
}
