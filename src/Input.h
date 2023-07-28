#pragma once

#include <unordered_map>
#include <map>
#include <glm.hpp>

class Input
{
public:
	Input();

	~Input();

	void KeyPress(unsigned int ID);

	void KeyRelease(unsigned int ID);

	bool IsKeyPressed(unsigned int ID);

	glm::vec2 GetMousePosition() const { return m_MousePosition; }

	void SetMousePosition(glm::vec2 Position);

private:
	std::unordered_map<unsigned int, bool> m_KeyMap;

	glm::vec2 m_MousePosition;
};

