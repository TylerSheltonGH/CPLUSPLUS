#pragma once
#include "GL/glew.h"
#include "SDL.h"
#include "glm.hpp"
#include <string>

//enum WindowFlags{INVISIBLE = 0x1, FULLSCREEN = 0x2, BORDERLESS = 0x3};

class Window
{
public:
	Window();

	~Window();

	void Init(std::string Title = "Title", 
			  glm::vec2 Position = glm::vec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), 
		      glm::vec2 Resolution = glm::vec2(800.0f, 600.0f),
		      Uint32 Flags = NULL); 

	void Clear();

	void Update();

	void Render();

	void SwapWindow();

	SDL_Window* GetWindow() { return m_Window; }

	//glm::vec2 GetResolution() const { return m_Resolution; }

	glm::vec2 GetSize() { return glm::vec2(m_Width, m_Height); }

private:
	SDL_Window* m_Window;
	SDL_GLContext m_GLContext;

	std::string m_Title;
	glm::vec2 m_Position;
	glm::vec2 m_Resolution;
	Uint32 m_Flags;

	int m_Width, m_Height;
};