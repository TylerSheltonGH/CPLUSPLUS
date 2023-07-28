#include "Player.h"
#include "SDL_mouse.h"
#include "SDL_keycode.h"
#include "Log.h"

Player::Player() :
	m_Input(nullptr),
	m_Projectiles(nullptr),
	m_Camera(nullptr),
	m_ProjectileLockout(64.0f)
{
}

Player::~Player()
{
}

void Player::PollEvents()
{
	m_Direction = glm::vec2(0.0f, 0.0f);

	if (m_ProjectileLockout <= 0.0f) {
		if (m_Input->IsKeyPressed(SDL_BUTTON_LEFT)) {
			glm::vec2 mousePosition = m_Input->GetMousePosition();

			glm::vec2 direction = m_Camera->ConvertScreenToWorld(mousePosition) - m_Position;
			direction = glm::normalize(direction);

			m_Projectiles->emplace_back(Projectile(2, "Projectile", m_Position, direction, 0.1f, 5000.0f));

			m_ProjectileLockout = 64.0f;
		}
	}

	if (m_Input->IsKeyPressed(SDLK_w)) {
		m_Direction += glm::vec2(0.0f, 1.0f);
	}
	if (m_Input->IsKeyPressed(SDLK_a)) {
		m_Direction += glm::vec2(-1.0f, 0.0f);
	}
	if (m_Input->IsKeyPressed(SDLK_s)) {
		m_Direction += glm::vec2(0.0f, -1.0f);
	}
	if (m_Input->IsKeyPressed(SDLK_d)) {
		m_Direction += glm::vec2(1.0f, 0.0f);
	}

	glm::normalize(m_Direction);
}

void Player::Update(float DeltaTime)
{
	m_Position += (m_Speed * m_Direction) * DeltaTime;

	m_ProjectileLockout -= DeltaTime;
}

void Player::GetGameInput(Input* Input)
{
	m_Input = Input;
}

void Player::GetGameProjectiles(std::vector<Projectile>* Projectiles)
{
	m_Projectiles = Projectiles;
}

void Player::GetGameCamera(Camera* Camera)
{
	m_Camera = Camera;
}