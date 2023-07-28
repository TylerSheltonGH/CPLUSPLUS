#pragma once

#include "glm.hpp"

static const float TILE_SIZE = 32.0f;

struct Tile {
	Tile(int ID = -1, glm::vec2 Position = glm::vec2(0.0f, 0.0f)) :
		id(ID),
		position(Position)
	{}

	int id;
	glm::vec2 position;
};