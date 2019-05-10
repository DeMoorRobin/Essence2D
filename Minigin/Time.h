#pragma once
#include "Singleton.h"
#include <chrono>
#include <deque>

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:

		void EnterNextFrame();

		float GetDeltaTime() { return m_DeltaTime; };
		int GetFrameCounter() { return m_FrameCounter;  };
		float GetFPS() { return m_FPS; };

		void SetFpsCalcDuration(size_t frames) { m_AmountOfFramesForAverage = frames; };

	private:
		std::deque<float> m_FrameTimes;
		std::chrono::steady_clock::time_point m_PrevFrame;
		size_t m_AmountOfFramesForAverage = 5;

		float m_FPS;
		float m_DeltaTime;
		int m_FrameCounter;

	};


}
