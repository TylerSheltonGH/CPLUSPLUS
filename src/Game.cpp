#include "Game.h"
#include "GL/glew.h"
#include "SDL.h"
#include "Log.h"
#include "Texture.h"
#include "ResourceManager.h"


Game::Game() :
	m_GameState(GameState::RUN),
	m_Update(true),
	m_Render(true),
	m_Input(nullptr),
	m_Time(nullptr),
	m_SpriteBatch(nullptr),
	m_Camera(nullptr),
	m_ApplicationFutures(nullptr),
	m_Random(nullptr)
{
}

Game::~Game()
{
}

void Game::Init()
{
	m_Map.Load(0, "map0");

	m_Player.Init(0, "Player", glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), 1.0f);
	m_Player.GetGameProjectiles(&m_Projectiles);
	m_Player.GetGameInput(m_Input);
	m_Player.GetGameCamera(m_Camera);
	m_Player.Info();
}

void Game::Run()
{
	PollEvents();

	Update();

	Render();
}

void Game::Loop()
{
	PollEvents();

	Update();

	Render();
}

void Game::PollEvents()
{
	m_Player.PollEvents();
}

void Game::Update()
{
	if (m_Update) {
		m_Map.Update(m_Time->GetPreviousFrameTimeMilliseconds());
	}

	m_Player.Update(m_Time->GetPreviousFrameTimeMilliseconds());

	for (int i = 0; i < m_Projectiles.size(); i++) {
		m_Projectiles[i].Update(m_Time->GetPreviousFrameTimeMilliseconds());
		if (m_Projectiles[i].GetDuration() <= 0.0f) {
			m_Projectiles.erase(m_Projectiles.begin() + i);
		}
	}

	//VOID_INFO("Projectle count: " + m_Projectiles.size());

	m_Camera->SetPosition(m_Player.GetPosition());
	m_Camera->Update();
}

void Game::Render()
{
	if (m_Render) {
		m_Map.Render();

		m_Player.Render(*m_SpriteBatch);

		for (int i = 0; i < m_Projectiles.size(); i++) {
			m_Projectiles[i].Render(*m_SpriteBatch);
		}
	}
}

void Game::Enable()
{
	m_Update = true;
	m_Render = true;
}

void Game::Disable()
{
	m_Update = false;
	m_Render = false;
}

void Game::GetApplicationData(Time* Time, Input* Input, Camera* Camera, Random* Random, SpriteBatch* SpriteBatch)
{
	m_Time = Time;
	m_Input = Input;
	m_Camera = Camera;
	m_Random = Random;
	m_SpriteBatch = SpriteBatch;
}