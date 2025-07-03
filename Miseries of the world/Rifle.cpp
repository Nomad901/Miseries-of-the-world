#include "Rifle.h"
#include "Irregular.h"
#include "SingleOrSequence.h"

void Rifle::initRifle(SDL_Renderer* pRenderer, RifleType pType, SDL_FRect pCharRect,
					  const Config::ReloadConfig& pReloadConfig, 
					  const Config::BulletsConfig& pBulletsConfig, 
					  const Config::WeaponConfig& pWeaponConfig)
{

}

void Rifle::initRifleAutomaticaly(SDL_Renderer* pRenderer, RifleType pType, SDL_FRect pCharRect)
{

}

void Rifle::updateBullets(SDL_Renderer* pRenderer)
{
	mFireModeFactory.getMode().value().get().render();
	mFireModeFactory.getMode().value().get().update(pRenderer, Weapon::getWeaponStats().mPos);
	if (mFireModeFactory.getMode().value().get().shouldBreakWeapon())
	{
		Gun::manageRobustness();
		mFireModeFactory.getMode().value().get().setShouldBreakWeapon(false);
	}
}

std::pair<int32_t, bool> Rifle::manageDamage(SDL_FRect pEnemyRect)
{
	checkDamage(pEnemyRect);
	auto tmpFireMode = mFireModeFactory.getMode();
	if (!tmpFireMode)
	{
		LOG("Unproper value!");
		return std::make_pair(0, false);
	}
	if (tmpFireMode.value().get().wasDamage())
		return std::make_pair(Weapon::getPower(), true);
	return std::make_pair(0, false);
}

void Rifle::shoot()
{

}

void Rifle::reload()
{

}

bool Rifle::checkDamage(SDL_FRect pEnemyRect)
{
	auto result = mFireModeFactory.getMode();
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

void Rifle::setAsASpecialWeapon()
{
	std::pair<int32_t, int32_t> tmpPower;
	
	mFireModeFactory.getMode().value().get().setAsSpecial();
	Weapon::setAllParameteres(Weapon::getWeaponStats().mPos, Weapon::getWeaponStats().mW,
							  Weapon::getWeaponStats().mH, 100, std::make_pair(2, 5), 10);
}

void Rifle::seterModes()
{
	switch (mRifleType)
	{
	case RifleType::DEFAULT:
		mFireModeFactory.appendMode("SingleOrSequence", std::make_unique<SingleOrSequence>());
		mFireModeFactory.setMode("SingleOrSequence");
		mFireModeFactory.getExactMode<SingleOrSequence>().value().get().setMode(Mode::SEQUENCE);
		break;
	case RifleType::SNIPER:
		mFireModeFactory.appendMode("SingleOrSequence", std::make_unique<SingleOrSequence>());
		mFireModeFactory.setMode("SingleOrSequence");
		mFireModeFactory.getExactMode<SingleOrSequence>().value().get().setMode(Mode::SINGLE);
		break;
	case RifleType::IRREGULAR:
		mFireModeFactory.appendMode("Irregular", std::make_unique<Irregular>());
		mFireModeFactory.setMode("Irregular");
		break;
	}
	
}
