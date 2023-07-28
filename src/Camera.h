#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Camera
{
public:
	Camera();
	~Camera();

	void Init(glm::vec2 ScreenSize);

	void Update();

	glm::vec2 ConvertScreenToWorld(glm::vec2 Coordinates);

	glm::vec2 GetPosition() const { return m_Position; }
	void SetPosition(const glm::vec2& Position);

	float GetScale() const { return m_Scale; }
	void SetScale(float Scale);

	glm::mat4 GetMatrix() const { return m_CameraMatrix; }

	float GetZoomSpeed() const { return m_ZoomSpeed; }
	void SetZoomSpeed(float Speed);

	void SetScreenSize(glm::vec2 ScreenSize);

private:
	bool m_NeedsMatrixUpdate;

	float m_Scale;

	glm::vec2 m_Position;

	glm::mat4 m_CameraMatrix;
	glm::mat4 m_OrthographicMatrix;

	glm::vec2 m_ScreenSize;

	float m_ZoomSpeed;
};