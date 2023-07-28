#pragma once
#include "Log.h"
#include "Window.h"
#include "Input.h"
#include "Game.h"
#include "Shader.h"
#include "Time.h"
#include "SpriteBatch.h"
#include "Camera.h"
#include "MapEditor.h"
#include "Random.h"
#include <future>
#include <thread>

enum class ApplicationState{RUN, EXIT};

class Application
{
public:
	Application();

	~Application();

	void Init();

	void Run();

private:
	void PollEvents();

	void Update();

	void Render();

	void Loop();

private:
	ApplicationState m_ApplicationState;

	bool m_EditMode;

	Window m_Window;
	Game m_Game;
	Input m_Input;
	Shader m_Shader;
	Time m_Time;
	SpriteBatch m_SpriteBatch;
	Camera m_Camera;
	MapEditor m_MapEditor;
	Random m_Random;

	std::vector<std::future<void>> m_Futures;
};