#include "Timer.h"

void Timer::startTimer()
{
	std::lock_guard<std::mutex> lg(mMtx);
	mRunning = true;
	mStartTime = std::chrono::high_resolution_clock::now();
}
void Timer::stopTimer()
{
	std::lock_guard<std::mutex> lg(mMtx);
	mRunning = false;
	mEndTime = std::chrono::high_resolution_clock::now();
}

void Timer::setProperFPS(const float pDelay)
{
	stopTimer();
	float elapsedTime = getDeltaTime();
	if (elapsedTime < pDelay)
		SDL_Delay(pDelay - elapsedTime);
	else
		SDL_Delay(pDelay);
}

void Timer::setDimensionOfTime(const Dimension pType)
{
	mDimension = pType;
}

inline bool Timer::isRunning() const
{
	return mRunning;
}

float Timer::getDeltaTime() const
{
	using namespace std::chrono;

	if (mRunning)
	{
		LOG("Timer is running, i cant compute the delta time!");
		return 0.0f;
	}
	else
	{
		if (mDimension == Dimension::MILISECONDS)
			return static_cast<float>(duration_cast<milliseconds>(mStartTime - mEndTime).count());
		else if (mDimension == Dimension::SECONDS)
			return static_cast<float>(duration_cast<seconds>(mStartTime - mEndTime).count());
		else if (mDimension == Dimension::MINUTES)
			return static_cast<float>(duration_cast<minutes>(mStartTime - mEndTime).count());
		else
			return 0.0f;
	}
}

std::chrono::time_point<std::chrono::high_resolution_clock> Timer::getCurrentTimeOfTimer() const
{
	if (mRunning)
	{
		std::chrono::time_point<std::chrono::high_resolution_clock> time = std::chrono::high_resolution_clock::now();
		if (mDimension == Dimension::SECONDS)
			return std::chrono::time_point_cast<std::chrono::seconds>(time);
		else if (mDimension == Dimension::MINUTES)
			return std::chrono::time_point_cast<std::chrono::minutes>(time);
		else
			return std::chrono::time_point_cast<std::chrono::milliseconds>(time);
	}
	else
	{
		LOG("Timer isnt running!");
		return std::chrono::high_resolution_clock::now();
	}
}
