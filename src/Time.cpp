#include "Time.h"
#include "SDL_timer.h"
#include "Log.h"

Time::Time() :
    m_Elapsed(0.0f),
    m_StartTime(std::chrono::steady_clock::now()),
    m_EndTime(std::chrono::steady_clock::now()),
    m_CurrentFrameTime(0.0f),
    m_PreviousFrameTime(0.0f),
    m_FPS(0.0f),
    m_FrameTimes(0.0f),
    m_FrameCount(0)
{
}

Time::~Time()
{
}

void Time::Update()
{
    m_PreviousFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(m_EndTime - m_StartTime).count();
    m_Elapsed += m_PreviousFrameTime;
}

void Time::Start()
{
    m_StartTime = std::chrono::steady_clock::now();
}

void Time::End()
{
	m_EndTime = std::chrono::steady_clock::now();

    m_PreviousFrameTime = std::chrono::duration_cast<std::chrono::nanoseconds>(m_EndTime - m_StartTime).count();
    m_Elapsed += m_PreviousFrameTime;

    CalculateFPS();
}

void Time::CalculateFPS()
{

}