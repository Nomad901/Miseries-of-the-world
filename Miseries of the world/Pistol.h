#pragma once
#include <SDL.h>

#include "Gun.h"

class SingleOrSequence;

class Pistol : public Gun
{
public:
	Pistol() = default;

	// init Weapon - FireMode - Gun classes at once
	void initPistol(SDL_Renderer* pRenderer, SDL_FRect pCharRect, int16_t pReloadingTime,
				    bool pShowReloadingQuote, SDL_Color pColorNumbersReload, int32_t pSizeNumbersReload, 
				    int32_t pCapacityBullets, const PATH& pPathBullets, int32_t pDelayBullets, 
				    int32_t pQuantityBullets, int32_t pQuantitySetsBullets, const Vector2f& pPosBullets, 
				    int32_t pWBullets, int32_t pHBullets, int32_t pSpeedBullets, const Vector2f& pPosWeapon,
				    int32_t pWWeapon, int32_t pHWeapon, float pRobustness, std::pair<int32_t, int32_t> pPower,
				    int16_t pWeight);

	void shoot() override;
	void reload() override;
	void checkRobustness() override;
	void checkDamage() override;
	void setAsASpecialWeapon() override;
	
	void setAsSpecialWeapon();
protected:
	bool manageDelay() override;

private:
	FireModeFactory mFireModeFactory;
	Randomizer mRobustness{ 3,6 };
	Timer mTimer; 

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
