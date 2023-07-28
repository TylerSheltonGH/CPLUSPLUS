#pragma once
#include "SpriteBatch.h"
#include "glm.hpp"
#include <string>

class Entity
{
public:
	Entity(int ID = -1, std::string Name = "NULL", glm::vec2 Position = glm::vec2(0.0f, 0.0f), glm::vec2 Direction = glm::vec2(0.0f, 0.0f), float Speed = 0.0f);
	~Entity();

	void Init(int ID = -1, std::string Name = "NULL", glm::vec2 Position = glm::vec2(0.0f, 0.0f), glm::vec2 Direction = glm::vec2(0.0f, 0.0f), float Speed = 0.0f);

	//virtual void PollEvents() = 0;

	virtual void Update(float DeltaTime) = 0;

	void Render(SpriteBatch& SpriteBatch);

	void Info();

	void SetID(int ID);

	int GetID() const { return m_ID; }

	void SetName(std::string Name);

	std::string GetName() const { return m_Name; }

	void SetPosition(glm::vec2 Position);

	glm::vec2 GetPosition() const { return m_Position; }

	void SetDirection(glm::vec2 Direction);

	glm::vec2 GetDirection() const { return m_Direction; }

	void SetSpeed(float Speed);

	float GetSpeed() const { return m_Speed; }

protected:
	int m_ID;

	std::string m_Name;

	glm::vec2 m_Position;
	glm::vec2 m_Direction;

	float m_Speed;
};