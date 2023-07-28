#pragma once


struct Stat {

	Stat(float Min = 0.0f, float Max = 1.0f) :
		min(Min),
		max(Max),
		current(Max)
	{}

	float min;
	float max;
	float current;
};