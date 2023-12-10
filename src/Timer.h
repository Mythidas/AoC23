#pragma once

#include <chrono>

class Timer
{
public:
	Timer()
	{
		Reset();
	}

	void Reset()
	{
		m_StartTimepoint = std::chrono::high_resolution_clock::now();
	}

	float Elapsed()
	{
		return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - m_StartTimepoint).count() * 0.001f * 0.001f * 0.001f;
	}

	float ElapsedMill()
	{
		return Elapsed() * 1000.0f;
	}

private:
	std::string m_Name;
	std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};