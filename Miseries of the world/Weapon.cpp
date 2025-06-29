#include "Weapon.h"
#include "WeaponManager.h"
#include "AnimatedTexture.h"

void Weapon::setAllParameteres(const Vector2f pPos, int32_t pW, int32_t pH,
							   float pRobustness, std::pair<int32_t, int32_t> pPower, 
							   int16_t pWeight)
{
	mWeaponStats.mPos = pPos;
	mWeaponStats.mW = pW;
	mWeaponStats.mH = pH;
	mWeaponStats.mScaleOfRobustness = pRobustness;
	mWeaponStats.mPower.setBeginAndEnd(pPower.first, pPower.second);
	mWeaponStats.mWeight = pWeight;
}

const Weapon::WeaponStates& Weapon::getWeaponStates() const noexcept
{
	return mWeaponStates;
}

const Weapon::WeaponStats& Weapon::getWeaponStats() const noexcept
{
	return mWeaponStats;
}

const Weapon::CharCollision& Weapon::getCharCollisions() const noexcept
{
	return mCharCollision;
}

const Weapon::Textures& Weapon::getTextures() const noexcept
{
	return mTextures;
}

void Weapon::setActive(bool pActive)
{
	mWeaponStates.mIsActive = pActive;
}

void Weapon::setAvailable(bool pAvailable)
{
	mWeaponStates.mIsAvailable = pAvailable;
}

void Weapon::setWasDamage(bool pWasDamage)
{
	mWeaponStates.mWasDamage = pWasDamage;
}

void Weapon::makeFreezed(bool pFreezed)
{
	mWeaponStates.mIsFreezed = pFreezed;
}

void Weapon::setRobustness(float pRobustness)
{
	if (pRobustness > 0.0f)
		mWeaponStats.mScaleOfRobustness = pRobustness;
}

void Weapon::setWeight(int16_t pWeight)
{
	if (pWeight > 0 && pWeight < 100)
		mWeaponStats.mWeight = pWeight;
}

void Weapon::setSize(const int32_t pW, const int32_t pH)
{
	if (pW > 0 && pW < WIN_WIDTH / 2 &&
		pH > 0 && pH < WIN_HEIGHT / 2)
	{
		mWeaponStats.mW = pW;
		mWeaponStats.mH = pH;
	}
}

void Weapon::setPos(const Vector2f& pPos)
{
	if (pPos.mX > 0 && pPos.mX < WIN_WIDTH &&
		pPos.mY > 0 && pPos.mY < WIN_HEIGHT)
		mWeaponStats.mPos = pPos;
}

void Weapon::setPower(std::pair<int32_t, int32_t> pPowerRange)
{
	if (pPowerRange.first >= 0 && pPowerRange.second >= 0)
		mWeaponStats.mPower.setBeginAndEnd(pPowerRange.first, pPowerRange.second);
}

void Weapon::setCharCollision(SDL_Rect pCharCollision)
{
	mCharCollision.mChar = pCharCollision;
}

void Weapon::setPaths(const PATH& pStaticPath, const PATH& pBrokenPath, const PATH& pReloadPath, const PATH& pShootPath)
{
	if (std::filesystem::exists(pStaticPath))
		mTextures.mStaticPath = pStaticPath;
	if (std::filesystem::exists(pBrokenPath))
		mTextures.mStaticPath = pBrokenPath;
	if (std::filesystem::exists(pReloadPath))
		mTextures.mStaticPath = pReloadPath;
	if (std::filesystem::exists(pShootPath))
		mTextures.mStaticPath = pShootPath;
}

int32_t Weapon::wasDamage()
{
	if (mWeaponStates.mWasDamage)
	{
		mWeaponStats.mPower.generateNew();
		return mWeaponStats.mPower.getNumber();
	}
	return 0;
}

int32_t Weapon::getSpeedOfChar(int32_t pHisSpeed)
{
	return pHisSpeed * (1 - (mWeaponStats.mWeight / 100));
}

void Weapon::updatePositions(const Vector2f& pPosChar)
{
	if (pPosChar.mX > 0 && pPosChar.mX < WIN_WIDTH &&
		pPosChar.mY > 0 && pPosChar.mY < WIN_HEIGHT)
	{
		mWeaponStats.mPos = pPosChar;
		mCharCollision.mChar.x = static_cast<int>(pPosChar.mX);
		mCharCollision.mChar.y = static_cast<int>(pPosChar.mY);
	}
}

void Weapon::defaultParametersWeapons()
{
	mWeaponStats.mScaleOfRobustness = 100;
	mWeaponStats.mWeight = 20;
	mWeaponStats.mPower.setBeginAndEnd(0, 5);

	//mBulletsManager.mDelay = 100;
	//mBulletsManager.mQuantityBullets = 60;
	//mBulletsManager.mOriginalQuantityBullets = 60;
	//mBulletsManager.mQuantityOfSets = 3;
}