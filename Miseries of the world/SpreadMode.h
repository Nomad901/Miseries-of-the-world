#pragma once
#include "FireMode.h"
#include "Randomizer.h"

//just a mode for shotguns!

class SpreadMode : public FireMode
{
public:
	SpreadMode();
	~SpreadMode() override = default;

	void shoot(SDL_Rect pCharRect, SDL_Rect pWeaponRect, bool pWasReload) override;
	void update(SDL_Renderer* pRenderer, const Vector2f& pPos) override;
	void render();

	void setAsSpecial() override;
	void setQuantityBulletsPerTime(int32_t pQuantityBullets);

	void setRangeOfSpread(int32_t pRange);

protected:
	bool manageDelay() override;

	void manageReload(int32_t& pTmpBreakingWeapon, bool pWasReload);
	void subtractionBullets(int32_t& pTmpBreakingWeapon);

private:
	int32_t mQuantityBulletsPerTime{ 0 };
	
	Randomizer mRandomizer{ 10,100 };
	RotateMachine mRotateMachine;
	Timer mTimer;
};
