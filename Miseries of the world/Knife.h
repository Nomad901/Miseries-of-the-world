//#pragma once
//#include <SDL.h>
//
//#include "Weapon.h"
//#include "AnimatedTexture.h"
//#include "FactoryOfFonts.h"
//#include "FactoryObjects.h"
//#include "RotateMachine.h"
//
//class Timer;
//
//class Knife : public Weapon
//{
//public:
//	Knife(SDL_Renderer* pRenderer,
//		  const Vector2f& pPos, int pW, int pH, std::pair<int32_t, int32_t> pPower, int16_t pDelay,
//		  const PATH& pStaticPath, const PATH& pBrokenPath, const PATH& pShootingPath,
//		  SDL_Rect pChar, SDL_Rect pHitBoxOfAttack);
//	
//	int16_t getDelay() const noexcept;
//	void setDelay(int16_t pDelay);
//	
//	SDL_Rect getHitBoxOfAttack();
//	void setHitBoxOfAttack(SDL_Rect pRect);
//
//	void adjustShootAnim(const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, float pIntensity);
//
//	bool WeaponIsInView(SDL_Rect pCharCollision) override;
//
//	void shoot() override;
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
//	void setAllAnimationsNull();
//
//private:
//
//	bool manageDelay();
//	void brokenChecker(SDL_Renderer* pRenderer);
//	void defaultParametersKnife();
//	void managePosSlashing();
//
//	//will do nothing...
//	void reload() override;
//private:
//	bool mHitBoxActive{ false };
//
//	int16_t mDelay{ 0 };
//	int16_t mCounterHits{ 0 };
//	SDL_Rect mChar{ 0,0,0,0 };
//	SDL_Rect mHitBoxKnife{ 0,0,0,0 };
//
//	SDL_Renderer* mRenderer{ nullptr };
//
//	RotateMachine mRotateMachine;
//	AnimatedTexture mShootingTexture;
//	Timer mDelayTimer;
//	FactoryObjects mObjects;
//	Randomizer mForRobustness{ 1,4 };
//};
//
