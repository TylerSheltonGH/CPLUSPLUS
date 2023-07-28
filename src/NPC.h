#pragma once
#include "Entity.h"


class NPC : public Entity
{
public:
	NPC();

	~NPC();

	void Update(float DeltaTime) override;

private:
	void Move();

private:
	bool m_DestinationReached;
	std::vector<glm::vec2> m_Corners;
};

