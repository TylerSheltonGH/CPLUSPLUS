#include "Camera.h"

Camera::Camera() :
	m_NeedsMatrixUpdate(true),
	m_Scale(1.0f),
	m_Position(0.0f, 0.0f),
	m_CameraMatrix(1.0f),
	m_OrthographicMatrix(1.0f),
	m_ScreenSize(800.0f, 600.0f),
	m_ZoomSpeed(0.5f)
{
}

Camera::~Camera()
{
}

void Camera::Init(glm::vec2 ScreenSize)
{
	m_ScreenSize = ScreenSize;
	m_OrthographicMatrix = glm::ortho(0.0f, m_ScreenSize.x, 0.0f, m_ScreenSize.y);
}

void Camera::Update()
{
	if (m_NeedsMatrixUpdate) {
		glm::vec3 translate(-m_Position.x + m_ScreenSize.x / 2, -m_Position.y + m_ScreenSize.y / 2, 0.0f);
		m_CameraMatrix = glm::translate(m_OrthographicMatrix, translate);

		glm::vec3 scale(m_Scale, m_Scale, 0.0f);
		m_CameraMatrix = glm::scale(glm::mat4(1.0f), scale) * m_CameraMatrix;

		m_NeedsMatrixUpdate = false;
	}
}

glm::vec2 Camera::ConvertScreenToWorld(glm::vec2 Coordinates)
{
	Coordinates.y = m_ScreenSize.y - Coordinates.y;

	Coordinates -= glm::vec2(m_ScreenSize.x / 2, m_ScreenSize.y / 2);

	Coordinates /= m_Scale;

	Coordinates += m_Position;

	return Coordinates;
}

void Camera::SetPosition(const glm::vec2& Position)
{
	m_Position = Position;
	m_NeedsMatrixUpdate = true;
}

void Camera::SetScale(float Scale)
{
	m_Scale = Scale;
	m_NeedsMatrixUpdate = true;
}

void Camera::SetZoomSpeed(float Speed)
{
	m_ZoomSpeed = Speed;
}

void Camera::SetScreenSize(glm::vec2 ScreenSize)
{
	if (m_ScreenSize != ScreenSize) {
		m_ScreenSize = ScreenSize;
		m_NeedsMatrixUpdate = true;
	}
}
