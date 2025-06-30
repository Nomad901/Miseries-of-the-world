#pragma once
#include <vector>

#include <SDL.h>

#include "Timer.h"
#include "AnimatedTexture.h"
#include "AnimateStateMachine.h"
#include "FactoryOfFonts.h"

class ReloadLogic
{
public:
	// if pShowReloadingQuote will be false - then the game will show just numbers'
	// Reloading time - in seconds
	ReloadLogic(SDL_Renderer* pRenderer, SDL_Rect pCharRect,
				int16_t pReloadingTime, bool pShowReloadingQuote,
				SDL_Color pColorNumbers = { 255,255,255,255 },
				int32_t pSizeNumbers = 25);

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
	SDL_Renderer* mRenderer{};

	bool mShowingQuote{ false };
	bool mIsReloading{ false };
	bool mNeedToSubtract{ false };

	int16_t mReloadingTime{};
	int16_t mCurrentReloadingTime{};
	int16_t mCounterTimer{1};

	SDL_Color mColor{};
	SDL_Rect mRectNumbers{};

	Timer mTimerReload;
	std::unique_ptr<AnimateStateMachine> mAnimateStateMachine;

};

