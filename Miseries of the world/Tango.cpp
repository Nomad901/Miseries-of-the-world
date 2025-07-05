#include "Tango.h"

void Tango::initTango(SDL_Renderer* pRenderer, SDL_FRect pCharRect, const Config::ReloadConfig& pReloadConfig, 
					  const Config::BulletsConfig& pBulletsConfig, const Config::WeaponConfig& pWeaponConfig)
{
	Weapon::setAllParameteres(pWeaponConfig.mPosWeapon, pWeaponConfig.mW, pWeaponConfig.mH,
		pWeaponConfig.mRobustness, pWeaponConfig.mPower, pWeaponConfig.mWeight);
	Gun::initGun(pRenderer, pReloadConfig, pCharRect);

	mFireModeFactory.appendMode("SpreadMode", std::make_unique<BurstMode>(pRenderer));
	auto tmpMode = mFireModeFactory.getExactMode<BurstMode>().value();
	tmpMode.get().init(pRenderer, pBulletsConfig.mCapacityBullets, pBulletsConfig.mPathBullets, pBulletsConfig.mDelayBullets,
					   pBulletsConfig.mQuantityBullets, pBulletsConfig.mQuantitySetsBullets, pBulletsConfig.mPosBullets,
					   pBulletsConfig.mW, pBulletsConfig.mH, pBulletsConfig.mSpeedBullets);
}

void Tango::initTangoAutomaticaly(SDL_Renderer* pRenderer, SDL_FRect pCharRect)
{
	initTango(pRenderer, pCharRect,
			  Gun::Config::ReloadConfig{ false, 6, 25, {255,255,255,255} },
			  Gun::Config::BulletsConfig{ 500, std::filesystem::current_path() / "Assets" / "photos and ttf" / "tangoBullet.png", 100,
			  							60,6,30,30,3,getWeaponStats().mPos },
			  Gun::Config::WeaponConfig{ 100,20, std::make_pair(3, 5),100,100, getWeaponStats().mPos });
	Weapon::setPaths(std::filesystem::current_path() / "Assets" / "photos and ttf" / "tango.png",
					 std::filesystem::current_path() / "Assets" / "photos and ttf" / "brokenTango.png");
	Weapon::setShootPath(std::filesystem::current_path() / "Assets" / "photos and ttf" / "shootTango.png",
						{ {SideOfChar::RIGHT, {0,1,2}} }, 50, 100);
	Weapon::setReloadPath(std::filesystem::current_path() / "Assets" / "photos and ttf" / "reloadTango.png",
						 { {SideOfChar::RIGHT, {0,1,2,3}} }, 10, 200);
	mFireModeFactory.getExactMode<BurstMode>()->get().loadAnim(pRenderer, Weapon::getWeaponStats().mPos, Weapon::getWeaponStats().mW, Weapon::getWeaponStats().mH,
															   std::filesystem::current_path() / "Assets" / "photos and ttf" / "chargingTango.png",
															   { {SideOfChar::RIGHT, {0,1,2,3,4,5,6,7,8,9}} }, 10, 300,
															   std::filesystem::current_path() / "Assets" / "photos and ttf" / "chargedTango.png",
															   { {SideOfChar::RIGHT, {0,1,2,3}} }, 5, 300);

	Gun::setReloadAnimationEndless(true);
	setAsASpecialWeapon();
}

void Tango::updateBullets(SDL_Renderer* pRenderer)
{
	mFireModeFactory.getExactMode<BurstMode>().value().get().render();
	mFireModeFactory.getExactMode<BurstMode>().value().get().update(pRenderer, Weapon::getWeaponStats().mPos);
	if (mFireModeFactory.getExactMode<BurstMode>().value().get().shouldBreakWeapon())
	{
		Gun::manageRobustness();
		mFireModeFactory.getExactMode<BurstMode>().value().get().setShouldBreakWeapon(false);
	}
}

std::pair<int32_t, bool> Tango::manageDamage(SDL_FRect pEnemyRect)
{
	checkDamage(pEnemyRect);
	auto tmpFireMode = mFireModeFactory.getExactMode<BurstMode>();
	if (!tmpFireMode)
	{
		LOG("Unproper value!");
		return std::make_pair(0, false);
	}
	if (tmpFireMode.value().get().wasDamage())
		return std::make_pair(Weapon::getPower(), true);
	return std::make_pair(0, false);
}

BurstMode& Tango::getFireMode() 
{
	return mFireModeFactory.getExactMode<BurstMode>().value().get();
}

void Tango::shoot()
{
	auto tmpFireMode = mFireModeFactory.getExactMode<BurstMode>().value();
	if (!Weapon::getWeaponStates().mRealodingState &&
		!Weapon::getWeaponStates().mIsBroken &&
		!Weapon::getWeaponStates().mIsFreezed)
	{
		tmpFireMode.get().shootChargedBullets(mFactoryObjects.convertFRect(Weapon::getCharCollisions().mChar),
											  mFactoryObjects.convertFRect(Weapon::getCharCollisions().mWeapon));
		Weapon::makeShoot(true);
		mWasReload = false;
	}
	if (tmpFireMode.get().getQuantityBullets() == 0)
	{
		reload();
	}
}

void Tango::reload()
{
	mWasReload = true;
	if (!Weapon::getWeaponStates().mRealodingState)
		Weapon::makeReload(true);
}

bool Tango::checkDamage(SDL_FRect pEnemyRect)
{
	auto result = mFireModeFactory.getExactMode<BurstMode>();
	if (!result)
	{
		LOG("Unproper Value!");
		return false;
	}
	auto& fireMode = result.value();
	auto& bulletsPool = fireMode.get().getBulletsPoolInstance();
	auto intersection = bulletsPool.hasIntersection(mFactoryObjects.convertFRect(pEnemyRect));

	if (intersection.second)
	{
		fireMode.get().setWasDamage(true);
		fireMode.get().getBulletsPoolInstance().destroyBullet(intersection.first);
		return true;
	}
	fireMode.get().setWasDamage(false);
	return false;
}

void Tango::setAsASpecialWeapon()
{
	mFireModeFactory.getExactMode<BurstMode>().value().get().setAsSpecial();
	Weapon::setAllParameteres(Weapon::getWeaponStats().mPos, Weapon::getWeaponStats().mW,
							  Weapon::getWeaponStats().mH, 100, std::make_pair(7, 10), 40);
}

void Tango::setBulletsPerShot(int32_t pQuantity)
{
	mFireModeFactory.getExactMode<BurstMode>()->get().setQuantityBulletsPerTime(pQuantity);
}

void Tango::setRangeOfBullets(int32_t pRange)
{
	mFireModeFactory.getExactMode<BurstMode>()->get().setRangeOfSpread(pRange);
}

void Tango::setDelayOfStoraging(int32_t pDelay)
{
	mFireModeFactory.getExactMode<BurstMode>()->get().setDelayOfStoraging(pDelay);
}

void Tango::renderCharge(SDL_Renderer* pRenderer)
{
	mFireModeFactory.getExactMode<BurstMode>()->get().render();
	mFireModeFactory.getExactMode<BurstMode>()->get().update(pRenderer, 
															 Weapon::getWeaponStats().mPos);
}

