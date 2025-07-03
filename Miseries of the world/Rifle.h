#pragma once
#include <SDL.h>

#include "Gun.h"

class SingleOrSequence;
class Irregular;

enum class RifleType
{
	DEFAULT = 0,
	SNIPER = 1, 
	IRREGULAR = 2
};

/*
	how to init this with your hands -> look at initRifleAutomaticaly function;
*/

class Rifle : public Gun
{
public:
	Rifle() = default;

	/*
	* init Weapon - FireMode - Gun classes at once
	struct WeaponConfig { float mRobustness{}; int16_t mWeight{}; std::pair<int32_t, int32_t> mPower{}; int32_t mW{}, mH{}; Vector2f mPosWeapon{ 0.0f,0.0f }; }
	struct BulletsConfig { int32_t mCapacityBullets{}; PATH mPathBullets = std::filesystem::current_path(); int32_t mDelayBullets{};
						   int32_t mQuantityBullets{}; int32_t mQuantitySetsBullets{}; int32_t mW{}, mH{}; int32_t mSpeedBullets{}; Vector2f mPosBullets{ 0.0f,0.0f }; }
	struct ReloadConfig { bool mShowReloadingQuote{ false }; int16_t mReloadingTime{}; int32_t mSizeNumbersReload{ 25 }; SDL_Color mColorNumbersReload{ 255,255,255,255 };}
	*/
	void initRifle(SDL_Renderer* pRenderer, RifleType pType, SDL_FRect pCharRect, const Config::ReloadConfig& pReloadConfig,
					const Config::BulletsConfig& pBulletsConfig, const Config::WeaponConfig& pWeaponConfig);
	void initRifleAutomaticaly(SDL_Renderer* pRenderer, RifleType pType, SDL_FRect pCharRect);

	void updateBullets(SDL_Renderer* pRenderer);
	std::pair<int32_t, bool> manageDamage(SDL_FRect pEnemyRect);

	void shoot() override;
	void reload() override;
	bool checkDamage(SDL_FRect pEnemyRect) override;
	void setAsASpecialWeapon() override;
private:
	void seterModes() override;

private:
	bool mWasReload{ false };
	RifleType mRifleType{ RifleType::DEFAULT };
	FireModeFactory mFireModeFactory;
	FactoryObjects mFactoryObjects;

};
