#include "Pistol.h"
#include "SingleOrSequence.h"

void Pistol::initPistol(SDL_Renderer* pRenderer, SDL_FRect pCharRect, const Config::ReloadConfig& pReloadConfig,
					    const Config::BulletsConfig& pBulletsConfig, const Config::WeaponConfig& pWeaponConfig)
{
	Weapon::setAllParameteres(pWeaponConfig.mPosWeapon, pWeaponConfig.mW, pWeaponConfig.mH, 
							  pWeaponConfig.mRobustness, pWeaponConfig.mPower, pWeaponConfig.mWeight);
	Gun::initGun(pRenderer, pReloadConfig, pCharRect);
	mFireModeFactory.appendMode("SingleOrSequence", std::make_unique<SingleOrSequence>());
	auto tmpMode = mFireModeFactory.getExactMode<SingleOrSequence>().value();
	tmpMode.get().init(pRenderer, pBulletsConfig.mCapacityBullets, pBulletsConfig.mPathBullets, pBulletsConfig.mDelayBullets,
					   pBulletsConfig.mQuantityBullets, pBulletsConfig.mQuantitySetsBullets, pBulletsConfig.mPosBullets,
					   pBulletsConfig.mW, pBulletsConfig.mH, pBulletsConfig.mSpeedBullets);
	tmpMode.get().setMode(Mode::SINGLE);
}

void Pistol::initPistolAutomaticaly(SDL_Renderer* pRenderer, SDL_FRect pCharRect)
{
	initPistol(pRenderer, pCharRect,
			   Gun::Config::ReloadConfig{ false, 3, 25, {255,255,255,255} },
			   Gun::Config::BulletsConfig{ 500, std::filesystem::current_path() / "Assets" / "photos and ttf" / "bulletV2.png", 100,
			   60,6,30,30,3,getWeaponStats().mPos },
			   Gun::Config::WeaponConfig{ 100,5, std::make_pair(0, 5),100,100, getWeaponStats().mPos });
	Weapon::setPaths(std::filesystem::current_path() / "Assets" / "photos and ttf" / "Pistol.png", 
					 std::filesystem::current_path() / "Assets" / "photos and ttf" / "brokenPistol.png");
	Weapon::setShootPath(std::filesystem::current_path() / "Assets" / "photos and ttf" / "PistolSh.png", 60, 50,
				      { {SideOfChar::RIGHT, {0,1,2}} }, 50, 300);
	Weapon::setReloadPath(std::filesystem::current_path() / "Assets" / "photos and ttf" / "PistolRel.png", 60, 90,
					   { {SideOfChar::RIGHT, {0,1,2,3,4,5,6,7,8,9,10,11,12}} }, 50, 220);
	setAsASpecialWeapon();
}

void Pistol::shoot()
{
	auto tmpFireMode = mFireModeFactory.getExactMode<SingleOrSequence>().value();
	if (!Weapon::getWeaponStates().mRealodingState &&
		!Weapon::getWeaponStates().mIsBroken &&
		!Weapon::getWeaponStates().mIsFreezed)
	{
		mFireModeFactory.getExactMode<SingleOrSequence>().value().get().shoot(mFactoryObjects.convertFRect(Weapon::getCharCollisions().mChar),
																			  mFactoryObjects.convertFRect(Weapon::getCharCollisions().mWeapon),
																			  mWasReload);
		Weapon::makeShoot(true);
		mWasReload = false;
	}
	if (tmpFireMode.get().getQuantityBullets() == 0)
	{
		reload();
	}
}

void Pistol::reload()
{
	mWasReload = true;
	if (!Weapon::getWeaponStates().mRealodingState)
		Weapon::makeReload(true);
}

bool Pistol::checkDamage(SDL_FRect pEnemyRect)
{
	auto result = mFireModeFactory.getExactMode<SingleOrSequence>();
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

void Pistol::setAsASpecialWeapon()
{
	mFireModeFactory.getExactMode<SingleOrSequence>().value().get().setAsSpecial();
	Weapon::setAllParameteres(Weapon::getWeaponStats().mPos, Weapon::getWeaponStats().mW, 
							  Weapon::getWeaponStats().mH, 100, std::make_pair(2, 5), 5);
}

void Pistol::updateBullets(SDL_Renderer* pRenderer)
{
	mFireModeFactory.getExactMode<SingleOrSequence>().value().get().render();
	mFireModeFactory.getExactMode<SingleOrSequence>().value().get().update(pRenderer, Weapon::getWeaponStats().mPos);
	if (mFireModeFactory.getExactMode<SingleOrSequence>().value().get().shouldBreakWeapon())
	{
		Gun::manageRobustness();
		mFireModeFactory.getExactMode<SingleOrSequence>().value().get().setShouldBreakWeapon(false);
	}

	std::cout << std::format("QuantityBullets: {}\n", mFireModeFactory.getExactMode<SingleOrSequence>().value().get().getQuantityBullets());
	std::cout << std::format("Sets: {}\n", mFireModeFactory.getExactMode<SingleOrSequence>().value().get().getQuantitySets());
	std::cout << std::format("Breaking: {}\n", Gun::getCurrentRobustness());

}

std::pair<int32_t, bool> Pistol::manageDamage(SDL_FRect pEnemyRect)
{
	checkDamage(pEnemyRect);
	auto tmpFireMode = mFireModeFactory.getExactMode<SingleOrSequence>();
	if (!tmpFireMode)
	{
		LOG("Unproper value!"); 
		return std::make_pair(0, false);
	}
	if (tmpFireMode.value().get().wasDamage())
		return std::make_pair(Weapon::getPower(), true);
	return std::make_pair(0, false);
}


