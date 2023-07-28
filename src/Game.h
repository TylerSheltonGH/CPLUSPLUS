#pragma once
#include "Input.h"
#include "Time.h"
#include "SpriteBatch.h"
#include "Camera.h"
#include "Player.h"
#include "Map.h"
#include "Projectile.h"
#include "Random.h"

#include <thread>
#include <future>

enum class GameState{RUN, EXIT};

class Game
{
public:
	Game();

	~Game();

	void Init();

	void Run();

	void PollEvents();

	void Update();

	void Render();

	void Enable();

	void Disable();

	void GetApplicationData(Time* Time, Input* Input, Camera* Camera, Random* Random, SpriteBatch* SpriteBatch);

private:
	void Loop();

private:
	GameState m_GameState;

	bool m_Update;

	bool m_Render;

	Input* m_Input;

	Time* m_Time;

	SpriteBatch* m_SpriteBatch;

	Camera* m_Camera;

	std::vector<std::future<void>>* m_ApplicationFutures;

	Random* m_Random;

	std::vector<Projectile> m_Projectiles;

	Player m_Player;

	Map m_Map;
};