#pragma once
#include <chrono>

const float MS_PER_SECOND = 1000.0f;
const float NS_PER_SECOND = 1e+9;
const float NS_PER_MS = 1e+6;

class Time
{
public:
	Time();

	~Time();

	void Update();

	void Start();

	void End();

	void CalculateFPS();

	float GetFPS() const { return m_FPS; }

	float GetElapsedSeconds() const { return m_Elapsed / NS_PER_SECOND; }

	float GetElapsed() const { return m_Elapsed; }

	float GetCurrentFrameTime() const { return m_CurrentFrameTime; }

	float GetPreviousFrameTime() const { return m_PreviousFrameTime; }

	float GetPreviousFrameTimeMilliseconds() const { return m_PreviousFrameTime / NS_PER_MS; }

private:
	float m_Elapsed;

	std::chrono::steady_clock::time_point m_StartTime;
	std::chrono::steady_clock::time_point m_EndTime;

	float m_CurrentFrameTime;
	float m_PreviousFrameTime;

	float m_FPS;

	float m_FrameTimes;
	int m_FrameCount;
};