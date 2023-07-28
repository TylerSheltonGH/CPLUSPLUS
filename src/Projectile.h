#pragma once
#include "Entity.h"

class Projectile : public Entity
{
public:
	Projectile(int ID = -1,
		std::string Name = "NULL", 
		glm::vec2 Position = glm::vec2(0.0f, 0.0f), 
		glm::vec2 Direction = glm::vec2(0.0f, 0.0f), 
		float Speed = 0.0f, 
		float Duration = 0.0f);

	~Projectile();

	void Update(float DeltaTime) override;

	float GetDuration() const { return m_Duration; }

private:
	float m_Duration;
};

