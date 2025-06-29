#pragma once
#include "AudioSystem.h"
#include "Vector2f.h"
#include "Randomizer.h"
#include "Assets.h"
#include "TextureManager.h"
#include "AnimatedTexture.h"
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
	
	void setAllParameteres(const Vector2f pPos, int32_t pW, int32_t pH,
						   float pRobustness, std::pair<int32_t, int32_t> pPower,
						   int16_t pWeight);

	const WeaponStates&   getWeaponStates()	  const noexcept;
	const WeaponStats&    getWeaponStats()	  const noexcept;
	const CharCollision&  getCharCollisions() const noexcept;
	const Textures&		  getTextures()		  const noexcept;

	void setActive(bool pActive);
	void setAvailable(bool pAvailable);
	void setWasDamage(bool pWasDamage);
	void makeFreezed(bool pFreezed);

	void setRobustness(float pRobustness);
	void setWeight(int16_t pWeight);
	void setSize(const int32_t pW, const int32_t pH);
	void setPos(const Vector2f& pPos);
	void setPower(std::pair<int32_t, int32_t> pPowerRange);

	void setCharCollision(SDL_Rect pCharCollision);

	void setPaths(const PATH& pStaticPath, const PATH& pBrokenPath, const PATH& pReloadPath, const PATH& pShootPath);

	int32_t wasDamage();
	int32_t getSpeedOfChar(int32_t pHisSpeed);

	void updatePositions(const Vector2f& pPosChar);

	virtual void setAsADefaultWeapon() = 0;
	virtual bool WeaponIsInView(SDL_Rect pCharCollision) = 0;
	virtual void render(SDL_Renderer* pRenderer) = 0;
	virtual void update() = 0;

protected:
	void defaultParametersWeapons();

protected:
	struct WeaponStates
	{
		bool mIsActive{ false };
		bool mIsAvailable{ false };
		bool mWasDamage{ false };
		bool mIsFreezed{ false };
	};

	struct WeaponStats
	{
		//no more than 100. but 101 - an infinite Robustness, unbreakable
		float mScaleOfRobustness{ 100.0f };
		int16_t mWeight{ 0 };
		int32_t mW{ 0 }, mH{ 0 };
		Vector2f mPos{ 0.0f,0.0f };
		Randomizer mPower{ 0,5 };
	};

	struct CharCollision
	{
		SDL_Rect mChar{ 0,0,0,0 };
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
	SDL_Renderer* mRenderer{ nullptr };

	WeaponStates mWeaponStates;
	WeaponStats mWeaponStats;
	CharCollision mCharCollision;
	Textures mTextures;

};

