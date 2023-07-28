#include "Input.h"

Input::Input() :
	m_MousePosition(glm::vec2(0.0f, 0.0f))
{
}

Input::~Input()
{
}

void Input::KeyPress(unsigned int ID)
{
	m_KeyMap[ID] = true;
}

void Input::KeyRelease(unsigned int ID)
{
	m_KeyMap[ID] = false;
}

bool Input::IsKeyPressed(unsigned int ID)
{
	auto it = m_KeyMap.find(ID);

	if (it != m_KeyMap.end()) {
		return it->second;
	}
	else {
		return false;
	}
}

void Input::SetMousePosition(glm::vec2 Position)
{
	m_MousePosition = Position;
}