#pragma once
#include <vector>

#include <SDL.h>

#include "Timer.h"
#include "AnimatedTexture.h"
#include "AnimateStateMachine.h"

class ReloadLogic
{
public:
	ReloadLogic(SDL_Renderer* pRenderer, SDL_Rect pCharRect,
			    float pReloadingTime, bool pShowReloadingQuote);

	bool isReloading();
	void startReloading();
	
	void showReloadQuote(bool pShowing);
	void setRelodingTime(float pReloadingTime);
	float getReloadingTime();

	void render(SDL_Renderer* pRenderer);
	void update(SDL_Rect pCharRect);

private:
	bool manageDelay();

private:
	bool mShowingQuote{ true };
	bool mIsReloading{ false };
	float mReloadingTime{};

	Timer mTimerReload;
	std::unique_ptr<AnimateStateMachine> mAnimateStateMachine;
};

