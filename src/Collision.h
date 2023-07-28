#pragma once
#include "glm.hpp"

struct CollisionData {
	glm::vec2 position;
	glm::vec2 size;
};

class Collision
{
public:
	static bool CheckBox(CollisionData A, CollisionData B);
};