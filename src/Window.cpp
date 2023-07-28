#include "Window.h"
#include "Log.h"

Window::Window() :
	m_Window(nullptr),
	m_GLContext(nullptr),
	m_Position(glm::vec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED)),
	m_Resolution(glm::vec2(800.0f, 600.0f)),
	m_Flags(NULL),
	m_Width(800),
	m_Height(600)
{
}

Window::~Window()
{
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Window::Init(std::string Title, glm::vec2 Position, glm::vec2 Resolution, Uint32 Flags)
{
	m_Title = Title;
	m_Position = Position;
	m_Resolution = Resolution;
	m_Flags = Flags;

	//create window
	m_Window = SDL_CreateWindow(m_Title.c_str(), m_Position.x, m_Position.y, m_Resolution.x, m_Resolution.y, m_Flags);
	if (m_Window == nullptr) {
		VOID_CORE_CRITICAL("Failed to create window.");
	}
	
	//create opengl context
	m_GLContext = SDL_GL_CreateContext(m_Window);
	if (m_GLContext == nullptr) {
		VOID_CORE_CRITICAL("Failed to create gl context.");
	}

	if (glewInit() != GLEW_OK) {
		VOID_CORE_CRITICAL("Failed to initialize glew.");
	}
	
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//VSYNC: 0 = OFF, 1 = ON
	SDL_GL_SetSwapInterval(0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glClearDepth(1.0);

	VOID_TRACE("OpenGL {}", glGetString(GL_VERSION));
}

void Window::Clear()
{
	glClearDepth(1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Update()
{
	SDL_GetWindowSize(m_Window, &m_Width, &m_Height);
}

void Window::Render()
{
	SDL_GL_SwapWindow(m_Window);
}

void Window::SwapWindow()
{
	SDL_GL_SwapWindow(m_Window);
}
