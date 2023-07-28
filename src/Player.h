#pragma once
#include "Entity.h"
#include "Input.h"
#include "Projectile.h"
#include "Camera.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void PollEvents();

	void Update(float DeltaTime) override;

	void GetGameInput(Input* Input);

	void GetGameProjectiles(std::vector<Projectile>* Projectiles);

	void GetGameCamera(Camera* Camera);

private:
	Input* m_Input;

	std::vector<Projectile>* m_Projectiles;

	Camera* m_Camera;

	float m_ProjectileLockout;
};