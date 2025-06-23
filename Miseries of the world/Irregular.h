#pragma once
#include "FireMode.h"
#include "Randomizer.h"

/* sequence of bullets for guns
   How its working: 
   first {amountOfBullets} are going out of the weapon, then we are waiting
   100 miliseconds (we can set this), forth next {amountOfBullets} are open to shoot
*/

class Irregular : public FireMode
{
public:
	Irregular();
	~Irregular() override = default;

	void shoot(SDL_Rect pCharRect, SDL_Rect pWeaponRect, bool pWasReload) override;

	void update(SDL_Renderer* pRenderer, const Vector2f& pPos) override;

	void setAsSpecial();
	void setQuantityBulletsPerTime(int32_t pQuantityBullets);
	void setBurstCooldown(int32_t pBurstCooldown);

protected:
	bool manageDelay() override;
	bool manageDelaySequence();

	void manageReload(int32_t& pTmpBreakingWeapon, bool pWasReload);
	void subtractionBullets(int32_t& pTmpBreakingWeapon);

private:
	int32_t mCounterBullets{0};
	int32_t mQuantityBulletsPerTime{0};
	int32_t mBurstCooldown{0};

	RotateMachine mRotateMachine;
	Timer mTimer;
	Timer mTimerForBurst;
	Randomizer mRandomizer{ 10,100 };
};

