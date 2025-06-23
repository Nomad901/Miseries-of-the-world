#include "SingleOrSequence.h"

void Sequence::shoot(SDL_Rect pCharRect, SDL_Rect pWeaponRect, bool pWasReload)
{
	static int32_t tmpBreakingWeapon = getFireStat().mOriginalQuantityBullets - 5;
	if (pWasReload)
	{
		tmpBreakingWeapon = getFireStat().mOriginalQuantityBullets - 5;
		setQuantityBullets(getFireStat().mOriginalQuantityBullets);
		setQuantitySets(getFireStat().mQuantitySets - 1);
	}
	if (getFireStat().mQuantitySets != 0)
	{
		if (mTimer.isRunning())
		{
			if (manageDelay())
				return;
		}
		
		mRotateMachine.calculateDegrees(getFireStat().mPos, InputManager::getInstance().getMousePos());

		mBulletsPool->makeBulletActive();
		mBulletsPool->manageLastBulletInside()->setSpeed(getFireStat().mSpeed);
		auto tmpPos = getFireStat().mPos;
		mBulletsPool->manageLastBulletInside()->shootBullet({ tmpPos.mX + getFireStat().mW - 40, tmpPos.mY }, InputManager::getInstance().getMousePos(),
															  pWeaponRect, mRotateMachine.getAngle(), { static_cast<float>(pWeaponRect.w / 2 - 10),-5 },
															  pCharRect.w, pCharRect.h);
		if (tmpBreakingWeapon > getFireStat().mQuantityBullets)
		{
			setShouldBreakWeapon(true);
			tmpBreakingWeapon -= 5;
		}
		setQuantityBullets(getFireStat().mQuantityBullets - 1);
		mTimer.startTimer();
	}
}

void Sequence::update(SDL_Renderer* pRenderer, const Vector2f& pPos)
{
	if (mBulletsPool->getSizeBullets() <= 2)
	{
		mBulletsPool->init(getFireStat().mCapacity, pRenderer, getFireStat().mPath, pPos,
						   getFireStat().mW, getFireStat().mH, getFireStat().mSpeed);
	}
	FireMode::getFireStat().mPos = pPos;
}

bool Sequence::manageDelay()
{
	if (!mTimer.isRunning())
		mTimer.startTimer();
	if (mTimer.getDeltaTime(false) >= getFireStat().mDelay)
	{
		mTimer.stopTimer();
		return false;
	}
	return true;
}

void Sequence::setAsSpecial()
{
	if (mMode == Mode::SEQUENCE) {
		setDelay(20);
		setQuantityBullets(40);
		setQuantitySets(6);
	}
	else
	{
		setDelay(300);
		setQuantityBullets(15);
		setQuantitySets(15);
	}
}

void Sequence::setMode(Mode pMode)
{
	mMode = pMode;
}
