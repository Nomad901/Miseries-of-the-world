#pragma once
#include "Weapon.h"
#include "ReloadLogic.h"
#include "AnimateStateMachine.h"
#include "FireModeFactory.h"

class Gun : public Weapon
{
public:
	Gun() = default;
	
	bool isReloading();
	void reload();
	void neededToReload();
	void setRelodingTime(int32_t pReloadingTime);
	int32_t getReloadingTime();

	void setAsADefaultWeapon() override;
	bool WeaponIsInView(SDL_Rect pCharCollision) override;
	void render(SDL_Renderer* pRenderer) override;
	void update() override;

	void setShiootAnim(const PATH& pShootPath, 
					   const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, float pIntensity);
	void setReloadAnim(const PATH& pReloadPath, 
					   const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, float pIntensity);

	void manageRotate();

	virtual void shoot() = 0;
	virtual void checkRobustness() = 0;
	virtual void checkDamage() = 0;
	virtual void setAsASpecialWeapon() = 0;

protected:
	virtual bool manageDelay() = 0;
	void brokenChecker(SDL_Renderer* pRenderer);

	FireModeFactory& getFireModeFactory();
	AnimateStateMachine& getAnimationStateMachine();
private:
	AnimateStateMachine mAnimateStateMachine;
	FireModeFactory mFireModeFactory;
	ReloadLogic mReloadLogic;

};

