#include "MiniginPCH.h"
#include "Time.h"



void dae::Time::EnterNextFrame()
{
	//calculate duration of last frame
	auto t = std::chrono::high_resolution_clock::now();
	m_DeltaTime = double(std::chrono::duration_cast<std::chrono::milliseconds>(t - m_PrevFrame).count());
	m_FrameTimes.push_back(float(m_DeltaTime));
	m_PrevFrame = t;

	if (m_FrameTimes.size() > m_AmountOfFramesForAverage) m_FrameTimes.pop_front();


	//calculate fps
	m_FPS = 0;
	for (const float& time : m_FrameTimes)
	{
		m_FPS += time;
	}
	m_FPS /= float(m_FrameTimes.size());
	m_FPS = 1.0f / m_FPS * 1000.0f;
	

	++m_FrameCounter;
}