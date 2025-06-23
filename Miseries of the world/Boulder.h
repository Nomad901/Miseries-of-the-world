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
//class BulletsPool;
//
//class Boulder : public Weapon
//{
//public:
//	Boulder(SDL_Renderer* pRenderer,
//			const Vector2f& pPos, int pW, int pH, std::pair<int32_t, int32_t> pPower, int32_t pDelay,
//			const PATH& pStaticPath, SDL_Rect pChar);
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
//
//private:
//	bool manageDelay();
//	void defaultParametersBoulder();
//
//	void reload() override;
//
//private:
//	SDL_Renderer* mRenderer{ nullptr };
//
//	RotateMachine mRotateMachine;
//	FactoryObjects mFactoryObjects;
//	Timer mTimer;
//
//	std::unique_ptr<BulletsPool> mBullets{ nullptr };
//
//};
//
