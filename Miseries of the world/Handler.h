#pragma once
#include <filesystem>
#include <array>

#include <SDL.h>

#include "UsualRects.h"
#include "Bullets.h"
#include "Weapons.h"
#include "TouchableObjects.h"
#include "Moving.h"
#include "Textures.h"

#include "Game.h"

using PATH = std::filesystem::path;

class Handler
{
public:
	Handler(Game* pGame);
	~Handler();

	void loopBack();
	void actions();
	void outro();
	void updateAll() {}

private:
	Game* mGame;
	std::unique_ptr<Textures> mTextures;
	Moving* mMoving;

	
	int iterate = 0;

	PATH mCurrentPath{std::filesystem::current_path()};

	Uint32 lastUpdate;
	Uint32 currentTime;

	//update stuff
	const int TICKS_PER_SECOND = 60;
	const int MS_PER_SEC = 1000 / TICKS_PER_SECOND;
	float mInterpolation;
	bool shouldUpdate{ false };
};

