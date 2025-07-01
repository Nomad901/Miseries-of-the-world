#pragma once
#include "Weapon.h"
#include "ReloadLogic.h"
#include "AnimateStateMachine.h"
#include "FireModeFactory.h"
#include "RotateMachine.h"

class Gun : public Weapon
{
public:
	Gun() = default;
	virtual ~Gun() = default;

	void initGun(SDL_Renderer* pRenderer, SDL_FRect pCharRect,
				 int16_t pReloadingTime, bool pShowReloadingQuote,
				 SDL_Color pColorNumbers = { 255,255,255,255 },
				 int32_t pSizeNumbers = 25);

	bool WeaponIsInView(SDL_Rect pCharCollision) override;
	void render(SDL_Renderer* pRenderer) override;
	void update(const Vector2f& pPos) override;

	virtual void shoot() = 0;
	virtual void checkRobustness() = 0;
	virtual void checkDamage() = 0;
	virtual void setAsASpecialWeapon() = 0;
	
protected:
	virtual bool manageDelay() = 0;
	bool brokenChecker(SDL_Renderer* pRenderer);

	bool manageShootState(SDL_Renderer* pRenderer);
	bool manageReloadState(SDL_Renderer* pRenderer);
	bool manageBrokenState(SDL_Renderer* pRenderer);

	void manageRotateAround(const Vector2f& pPos);

	FireModeFactory& getFireModeFactory();
private:
	int32_t mCurrentRobustness{};

	FireModeFactory mFireModeFactory;
	ReloadLogic mReloadLogic;
	RotateMachine mRotateMachine;
};

