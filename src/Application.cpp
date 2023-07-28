#include "Application.h"
#include "IOManager.h"

Application::Application() :
	m_ApplicationState(ApplicationState::RUN),
	m_EditMode(false)
{
}

Application::~Application()
{
}

void Application::Init()
{
	Log::Init();

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		VOID_CORE_CRITICAL("Failed to initialize SDL!");
	}

	m_Random.Seed();

	m_Window.Init("Void", glm::vec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED), glm::vec2(800, 600), SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	m_Camera.Init(m_Window.GetSize());

	m_Game.GetApplicationData(&m_Time, &m_Input, &m_Camera, &m_Random, &m_SpriteBatch);

	m_Game.Init();

	std::string vertex;
	std::string fragment;

	if (IOManager::ReadFileToString("Shaders/Basic.vertex", vertex) && IOManager::ReadFileToString("Shaders/Basic.fragment", fragment)) {
		m_Shader.Create(vertex, fragment);
		m_Shader.AddAttribute("vertexPosition");
		m_Shader.AddAttribute("vertexColor");
		m_Shader.AddAttribute("vertexUV");
		m_Shader.Link();

		m_SpriteBatch.Init();
	}
	else {
		VOID_CORE_CRITICAL("Failed to read shader files.");
	}

	m_MapEditor.GetApplicationData(&m_Input, &m_Camera);
}

void Application::Run()
{
	Loop();
}

void Application::PollEvents()
{
	SDL_Event evnt;

	SDL_PollEvent(&evnt);

	switch (evnt.type) {
	case SDL_MOUSEMOTION:
		m_Input.SetMousePosition(glm::vec2(evnt.motion.x, evnt.motion.y));
		break;
	case SDL_KEYDOWN:
		m_Input.KeyPress(evnt.key.keysym.sym);
		if (evnt.key.keysym.sym == SDLK_F10) {
			if (m_EditMode) {
				m_Game.Enable();

				m_EditMode = false;
			}
			else {
				m_Game.Disable();

				m_EditMode = true;

				m_MapEditor.LoadMap(0, "NULL");
			}
		}
		break;
	case SDL_KEYUP:
		m_Input.KeyRelease(evnt.key.keysym.sym);
		break;
	case SDL_MOUSEBUTTONDOWN:
		m_Input.KeyPress(evnt.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		m_Input.KeyRelease(evnt.button.button);
		break;
	case SDL_MOUSEWHEEL:
		if (evnt.wheel.y > 0)
		{
			m_Camera.SetScale(m_Camera.GetScale() + m_Camera.GetZoomSpeed());
			if (m_Camera.GetScale() > 10.0f) {
				m_Camera.SetScale(10.0f);
			}
		}
		else if (evnt.wheel.y < 0)
		{
			m_Camera.SetScale(m_Camera.GetScale() - m_Camera.GetZoomSpeed());
			if (m_Camera.GetScale() < 1.0f) {
				m_Camera.SetScale(1.0f);
			}
		}
		break;
	case SDL_QUIT:
		m_ApplicationState = ApplicationState::EXIT;
		break;
	}

	m_Game.PollEvents();

	/*if (m_Input.IsKeyPressed(SDLK_F10)) {
		if (m_EditMode) {
			m_Game.Disable();

			m_EditMode = false;
		}
		else {
			m_Game.Enable();

			m_EditMode = true;

			m_MapEditor.LoadMap(0, "NULL");
		}
	}*/

	if (m_EditMode) {
		m_MapEditor.PollEvents();
	}
}

void Application::Update()
{
	m_Window.Update();
	m_Camera.SetScreenSize(m_Window.GetSize());
	m_Camera.Update();
	m_Game.Update();

	if (m_EditMode) {
		m_MapEditor.Update();
	}
}

void Application::Render()
{
	m_Window.Clear();

	m_Shader.Use();

	glActiveTexture(GL_TEXTURE0);

	glUniform1i(m_Shader.GetUniformLocation("mySampler"), 0);

	glm::mat4 projectionMatrix = m_Camera.GetMatrix();

	glUniformMatrix4fv(m_Shader.GetUniformLocation("P"), 1, GL_FALSE, &projectionMatrix[0][0]);

	m_SpriteBatch.Begin();

	m_Game.Render();

	m_SpriteBatch.End();

	m_SpriteBatch.Render();

	if (m_EditMode) {
		m_MapEditor.Render();
	}

	m_Shader.Unuse();

	m_Window.SwapWindow();
}

void Application::Loop()
{
	while (m_ApplicationState == ApplicationState::RUN) {
		m_Time.Start();

		PollEvents();
		Update();
		Render();

		m_Time.End();
	}
}