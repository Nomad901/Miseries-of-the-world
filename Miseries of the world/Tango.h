#pragma once
#include "Gun.h"
#include "AnimateStateMachine.h"
#include "BurstMode.h"

/*
	This is the secret weapon of the game. Project TANGO
*/

class Tango : public Gun
{
public:
	Tango() = default;

	void initTango(SDL_Renderer* pRenderer, SDL_FRect pCharRect, const Config::ReloadConfig& pReloadConfig,
				   const Config::BulletsConfig& pBulletsConfig, const Config::WeaponConfig& pWeaponConfig);
	void initTangoAutomaticaly(SDL_Renderer* pRenderer, SDL_FRect pCharRect);

	void updateBullets(SDL_Renderer* pRenderer);
	std::pair<int32_t, bool> manageDamage(SDL_FRect pEnemyRect);

	BurstMode& getFireMode();

	void shoot() override;
	void reload() override;
	bool checkDamage(SDL_FRect pEnemyRect) override;
	void setAsASpecialWeapon() override;

	void setBulletsPerShot(int32_t pQuantity);
	void setRangeOfBullets(int32_t pRange);
	void setDelayOfStoraging(int32_t pDelay);

	void renderCharge(SDL_Renderer* pRenderer);
	
private:
	bool mWasReload{ false };

	FireModeFactory mFireModeFactory;
	FactoryObjects mFactoryObjects;
};

