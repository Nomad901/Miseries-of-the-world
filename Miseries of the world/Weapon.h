#pragma once
#include "AudioSystem.h"
#include "Vector2f.h"
#include "Randomizer.h"
#include "Assets.h"
#include "TextureManager.h"
#include "AnimateStateMachine.h"
#include "FactoryObjects.h"

class WeaponManager;

//---------------System of Weapons-----------------
//-------------------------------------------------
//
//	the character has 60 (as usual quantity of bullets) bullets and 
//  he can by all means shoot into the enemies and so on. but also
//  the character can find some bullets on the ground and at the same time
//	all weapons have a robustness. the character can shoot as much time as he wants.
//  BUT! if robustness of the weapon is null - this weapon will be broken and the character
//  needs to press the button in order to throw away this weapon. cuz this is not available anymore
// 
//	
//	TODO: upgrade the weapons in order to set some improvements(fire buttons and so on)
// 
// 
//-------------------------------------------------

// when the character take some bullets(i will implement this in the bullets class)
// i will change quantity of bullets here

// setting and getting parameters of Weapons

class Weapon : protected Assets
{
protected:
	struct WeaponStates;
	struct WeaponStats;
	struct CharCollision;
	struct Textures;
public:
	Weapon() = default;
	virtual ~Weapon() = default;
	
	void initWeapon(SDL_Renderer* pRenderer);

	void setAllParameteres(const Vector2f pPos, int32_t pW, int32_t pH,
						   float pRobustness, std::pair<int32_t, int32_t> pPower,
						   int16_t pWeight);

	const WeaponStates&   getWeaponStates()	  const noexcept;
	const WeaponStats&    getWeaponStats()	  const noexcept;
	const CharCollision&  getCharCollisions() const noexcept;
	const Textures&		  getTextures()		  const noexcept;
	AnimateStateMachine&  getAnimatedStateMachine();
	float getNumberRobustness();
	int32_t getPower();

	void setActive(bool pActive);
	void setAvailable(bool pAvailable);
	void setWasDamage(bool pWasDamage);
	
	void makeFreezed(bool pFreezed);
	void makeBroken(bool pBroken);
	void makeShoot(bool pShoot);
	void makeReload(bool pReload);

	void setRobustness(float pRobustness);
	void setWeight(int16_t pWeight);
	void setSize(const int32_t pW, const int32_t pH);
	void setPos(const Vector2f& pPos);
	void setPosChar(const Vector2f& pPosChar);
	void setPower(std::pair<int32_t, int32_t> pPowerRange);

	void setCharCollision(SDL_FRect pCharCollision);
	void setWeaponCollision(SDL_FRect pWeaponCollision);
	
	void setPaths(const PATH& pStaticPath, const PATH& pBrokenPath);

	void setShootPath(const PATH& pShootPath,
					  const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers,  int32_t pDelay, float pIntensity);
	void setReloadPath(const PATH& pReloadPath, 
					   const std::unordered_map<SideOfChar, std::vector<uint32_t>>& pNumbers, int32_t pDelay, float pIntensity);
	
	int32_t wasDamage();
	int32_t getSpeedOfChar(int32_t pHisSpeed);

	void updatePositions(const Vector2f& pPosChar, const Vector2f& pPosWeapon);

	//virtual void setAsADefaultWeapon() = 0;
	virtual bool WeaponIsInView(SDL_Rect pCharCollision) = 0;
	virtual void render(SDL_Renderer* pRenderer) = 0;
	virtual void update(const Vector2f& pPos) = 0;

//protected:
//	void defaultParametersWeapons();

protected:
	struct WeaponStates
	{
		bool mShootingState{ false };
		bool mRealodingState{ false };

		bool mIsActive{ false };
		bool mIsAvailable{ false };
		bool mWasDamage{ false };

		bool mIsFreezed{ false };
		bool mIsBroken{ false };
	};

	struct WeaponStats
	{
		//no more than 100. but 101 - an infinite Robustness, unbreakable
		float mScaleOfRobustness{ 100.0f };
		Randomizer mRobustness{ 3,6 };
		int16_t mWeight{ 0 };
		int32_t mW{ 0 }, mH{ 0 };
		Vector2f mPos{ 0.0f,0.0f };
		Randomizer mPower{ 0,5 };
	};

	struct CharCollision
	{
		// set size and pos - will affect on the weapon collision
		SDL_FRect mWeapon{ 0,0,0,0 };
		SDL_FRect mChar{ 0,0,0,0 };
	};

	// this will be used by animStateMachine. implement there getrect()
	struct Textures
	{
		PATH mStaticPath{ std::filesystem::current_path() };
		PATH mReloadingPath{ std::filesystem::current_path() };
		PATH mShootingPath{ std::filesystem::current_path() };
		PATH mBrokenWeapon{ std::filesystem::current_path() };
	};

	FactoryObjects mObjects;

private:
	SDL_Renderer* mRenderer;

	WeaponStates mWeaponStates;
	WeaponStats mWeaponStats;
	CharCollision mCharCollision;
	Textures mTextures;

	AnimateStateMachine mAnimateStateMachine;
};

