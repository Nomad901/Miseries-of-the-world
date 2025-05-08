#pragma once
#include <filesystem>
#include <random>

#include <SDL.h>
#include <SDL_image.h>

#include "UsualRects.h"

enum class WeaponType{RIFLE, PISTOL};

using PATH = std::filesystem::path;

class Weapons 
{
public:
	Weapons(SDL_Renderer* pRenderer, const PATH& pPath, const WeaponType pType);
	~Weapons();

	void render();
	void update(){}

	void changeWeapon(const PATH& pPath,
					  const WeaponType pType);

	void setDimension(const int pWidth, const int pHeight);
	void setPosition(const int pPosX, const int pPosY);

	void setWeaponType(const WeaponType pType) { mType = pType; }

	//All of this i will implement when game will be working well
	SDL_bool isHardEnough(const WeaponType pType);
	SDL_bool isBroken();
	SDL_bool fastReload();

	WeaponType getWeaponType() const { return mType; }
	SDL_Rect getRect()		   const { return mRect; }
	int getWidth()			   const { return mW;    }
	int getHeight()			   const { return mH;	 }
	int getPosX()			   const { return mPosX; }
	int getPosY()			   const { return mPosY; }

private:
	SDL_Renderer* mRenderer{ nullptr };
	SDL_Texture* mTexture{ nullptr };
	SDL_Rect mRect;

	WeaponType mType;

	PATH mPath;

	// Position and dimension of rectangles
	int mPosX, mPosY;
	int mW, mH;

	//interesting features
	struct Stat
	{
		int weight{ 0 };
		float broken{ 0.0f };
		SDL_bool fastReload{ SDL_FALSE };
	};
};
