#pragma once
#include "Weapon.h"
#include "ReloadLogic.h"
#include "AnimateStateMachine.h"
#include "FireModeFactory.h"

class Gun : public Weapon
{
public:
	Gun() = default;

	bool WeaponIsInView(SDL_Rect pCharCollision) override;
	void render(SDL_Renderer* pRenderer) override;
	void update() override;

	void manageRotate();

	virtual void shoot() = 0;
	virtual void checkRobustness() = 0;
	virtual void checkDamage() = 0;
	virtual void setAsASpecialWeapon() = 0;
	
protected:
	virtual bool manageDelay() = 0;
	bool brokenChecker(SDL_Renderer* pRenderer);

	FireModeFactory& getFireModeFactory();
	AnimateStateMachine& getAnimationStateMachine();
private:
	int32_t mCurrentRobustness{};

	AnimateStateMachine mAnimateStateMachine;
	FireModeFactory mFireModeFactory;
	ReloadLogic mReloadLogic;

};

