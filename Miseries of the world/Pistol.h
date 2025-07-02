#pragma once
#include <SDL.h>

#include "Gun.h"

class SingleOrSequence;

class Pistol : public Gun
{
public:
	Pistol() = default;

	/*
	* init Weapon - FireMode - Gun classes at once
	struct WeaponConfig { float mRobustness{}; int16_t mWeight{}; std::pair<int32_t, int32_t> mPower{}; int32_t mW{}, mH{}; Vector2f mPosWeapon{ 0.0f,0.0f }; }
	struct BulletsConfig { int32_t mCapacityBullets{}; PATH mPathBullets = std::filesystem::current_path(); int32_t mDelayBullets{};
						   int32_t mQuantityBullets{}; int32_t mQuantitySetsBullets{}; int32_t mW{}, mH{}; int32_t mSpeedBullets{}; Vector2f mPosBullets{ 0.0f,0.0f }; }
	struct ReloadConfig { bool mShowReloadingQuote{ false }; int16_t mReloadingTime{}; int32_t mSizeNumbersReload{ 25 }; SDL_Color mColorNumbersReload{ 255,255,255,255 };}
	*/
	void initPistol(SDL_Renderer* pRenderer, SDL_FRect pCharRect, const Config::ReloadConfig& pReloadConfig,
				    const Config::BulletsConfig& pBulletsConfig, const Config::WeaponConfig& pWeaponConfig);

	void shoot() override;
	void reload() override;
	void checkDamage() override;
	void setAsASpecialWeapon() override;
	
	void updateBullets(SDL_Renderer* pRenderer);
private:
	bool mWasReload{ false };
	FireModeFactory mFireModeFactory;
	FactoryObjects mFactoryObjects;

};

//#include <SDL.h>
//
//#include "Weapon.h"
//#include "AnimatedTexture.h"
//#include "FactoryOfFonts.h"
//#include "FactoryObjects.h"
//#include "RotateMachine.h"
//
//class Timer;
//class BulletsPool;
//
//class Pistol : public Weapon
//{
//public:
//	Pistol(SDL_Renderer* pRenderer,
//		   const Vector2f& pPos, int pW, int pH, std::pair<int32_t,int32_t> pPower,
//		   int32_t pQuantityBullets, int32_t pQuantityOfSets, int32_t pReloadingTime, 
//		   const PATH& pStaticPath, const PATH& pBrokenWeaponPath, const PATH& pReloadingPath, const PATH& pShootingPath, 
//		   SDL_Rect pChar);
//
//	void adjustReloadAnim(const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, float pIntensity);
//	void adjustShootAnim(const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, float pIntensity);
//
//	bool WeaponIsInView(SDL_Rect pCharCollision) override;
//
//	void render(SDL_Renderer* pRenderer) override;
//	void update() override;
//	
//	void setAsADefaultWeapon() override;
//	void setAsASpecialWeapon() override;
//	
//	std::vector<int> isShot(const std::vector<SDL_Rect>& pRects) override;
//	bool checkRobustness() override;
//	int32_t checkDamage() override;
//
//	int32_t getSpeedOfChar(int32_t pHisSpeed) override;
//
//	void manageRotate();
//
//private:
//
//	bool manageDelay();
//	void defaultParametersPistol();
//	void brokenChecker(SDL_Renderer* pRenderer);
//
//private:
//	int32_t mReloadCounter{ 0 };
//
//	SDL_Renderer* mRenderer{ nullptr };
//
//	RotateMachine mRotateMachine;
//	AnimatedTexture mReloadTexture;
//	AnimatedTexture mShootingTexture;
//	FactoryObjects mFactoryObjects;
//	Timer mTimer;
//	Timer mTimerForShooting;
//	Timer mTimerOfSets;
//	Randomizer mForRobustness{ 3,6 };
//
//	std::unique_ptr<BulletsPool> mBullets{ nullptr };
//};
