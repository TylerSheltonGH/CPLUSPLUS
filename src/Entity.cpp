#include "Entity.h"
#include "ResourceManager.h"
#include "Log.h"

Entity::Entity(int ID, std::string Name, glm::vec2 Position, glm::vec2 Direction, float Speed) :
	m_ID(ID),
	m_Name(Name),
	m_Position(Position),
	m_Direction(Direction),
	m_Speed(Speed)
{
}

Entity::~Entity()
{
}

void Entity::Init(int ID, std::string Name, glm::vec2 Position, glm::vec2 Direction, float Speed)
{
	m_ID = ID;
	m_Name = Name;
	m_Position = Position;
	m_Direction = Direction;
	m_Speed = Speed;
}


void Entity::Render(SpriteBatch& SpriteBatch)
{
	SpriteBatch.Add(glm::vec4(m_Position.x, m_Position.y, 32.0f, 32.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		ResourceManager::GetTexture("Textures/" + m_Name + ".png").id,
		0.0f, Color());
}

void Entity::Info()
{
	VOID_CORE_TRACE("ID: {}, NAME: {}, POSITION: (X: {}, Y: {}), DIRECTION: (X: {}, Y: {}), SPEED: {}",
		m_ID, m_Name, m_Position.x, m_Position.y, m_Direction.x, m_Direction.y, m_Speed);
}

void Entity::SetID(int ID)
{
	m_ID = ID;
}

void Entity::SetName(std::string Name)
{
	m_Name = Name;
}

void Entity::SetPosition(glm::vec2 Position)
{
	m_Position = Position;
}

void Entity::SetDirection(glm::vec2 Direction)
{
	m_Direction = Direction;
}

void Entity::SetSpeed(float Speed)
{
	m_Speed = Speed;
}