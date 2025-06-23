#pragma once
#include "Timer.h"
#include "Loging.h"
#include "AudioSystem.h"
#include "Assets.h"
#include "Game.h"
#include "TextureManager.h"

#define SCREEN_RECT { 0, 0, WIN_WIDTH, WIN_HEIGHT }

class FactoryScenes : protected Assets
{
public:
	virtual ~FactoryScenes() = default;
	
	virtual void setBlackScreen() = 0;

	virtual void loadNewScene(std::string_view pScene, const PATH& pPath) = 0;
	virtual void removeScene(std::string_view pScene) = 0;

	virtual void setScene(std::string_view pScene) = 0;

	virtual void render() = 0;
};


