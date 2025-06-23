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

	void setAsSpecial();
	void setQuantityBulletsPerTime(int32_t pQuantityBullets);
	void setBurstCooldown(int32_t pBurstCooldown);

	void setPercentSpread(int32_t pSpread);

protected:
	bool manageDelay() override;

	void manageReload(int32_t& pTmpBreakingWeapon, bool pWasReload);
	void subtractionBullets(int32_t& pTmpBreakingWeapon);

private:
	int32_t mQuantityBulletsPerTime;
	
	RotateMachine mRotateMachine;
	Randomizer mRandomizer; 
	Timer mTimer;
};

//setDelay(300);
//setQuantityBullets(8);
//setOrigQuantityBullets(8);
//setQuantitySets(8);
//mQuantityBulletsSpread = 5;

//pTmpBreakingWeapon = getFireStat().mOriginalQuantityBullets - 2;
//setQuantityBullets(getFireStat().mOriginalQuantityBullets);
//setQuantitySets(getFireStat().mQuantitySets - 1);


//if (mMode == ModeIrregular::SPREAD)
//{
//	mRandomizer.generateNew();
//	if (i % 2 == 0)
//		mRotateMachine.setAngle(mRotateMachine.getAngle() - mRandomizer.getNumber());
//	else
//		mRotateMachine.setAngle(mRotateMachine.getAngle() + mRandomizer.getNumber());
//}