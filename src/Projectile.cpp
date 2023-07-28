#include "Projectile.h"

Projectile::Projectile(int ID, 
	std::string Name, 
	glm::vec2 Position, 
	glm::vec2 Direction, 
	float Speed, 
	float Duration)
{
	m_ID = ID;
	m_Name = Name;
	m_Position = Position;
	m_Direction = Direction;
	m_Speed = Speed;
	m_Duration = Duration;
}

Projectile::~Projectile()
{
}

void Projectile::Update(float DeltaTime)
{
	m_Position += (m_Speed * m_Direction) * DeltaTime;

	m_Duration -= DeltaTime;
}
