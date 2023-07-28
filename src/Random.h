#pragma once
#include <random>

class Random
{
public:
	
	Random();

	~Random();

	void Seed();

	float Range(float Min, float Max);

	int Range(int Min, int Max);

private:
	std::random_device m_RD;
	std::mt19937 m_RandomEngine;
};

