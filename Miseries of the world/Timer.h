#pragma once
#include <mutex>
#include <chrono>

#include "SDL.h"
#include "Loging.h"

#define LOG(msg) Loging::log(msg, __FILE__, __LINE__)

enum class Dimension{MILISECONDS, SECONDS, MINUTES};

class Timer
{
public:
	Timer() = default;
	
	void startTimer();
	void stopTimer();
	void setProperFPS(const float pDelay);
	
	// MILISECONDS, SECONDS, MINUTES
	void setDimensionOfTime(const Dimension pType);

	inline bool isRunning() const;
	
	float getDeltaTime() const;
	std::chrono::time_point<std::chrono::high_resolution_clock> getCurrentTimeOfTimer() const;

private:
	bool mRunning { false };
	std::chrono::time_point<std::chrono::high_resolution_clock> mStartTime, mEndTime;
	std::mutex mMtx;
	
	Dimension mDimension{ Dimension::MILISECONDS };
};

