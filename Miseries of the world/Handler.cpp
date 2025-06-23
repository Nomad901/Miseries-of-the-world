#include "Handler.h"
#include "InputManager.h"
#include "Timer.h"
#include "Assets.h"
#include "AnimatedTexture.h"
#include "../GameStates.h"
#include "../Menu.h"
#include "../InGame.h"
#include "BulletsPool.h"
#include "Bullets.h"
#include "Weapon.h"
#include "Pistol.h"
#include "Knife.h"
#include "Boulder.h"

Handler::Handler(Game* pGame)
	:mGame(pGame),
	mInterpolation{0.0f}
{
 	Assets::init();
	TextureManager::init();
	InputManager::init();
	FactoryOfFonts::init();
	//mBulletsPool = std::make_unique<BulletsPool>();
	//mFactoryObjects = std::make_unique<FactoryObjects>();
	//mRandomizerX = std::make_unique<Randomizer>(0, WIN_WIDTH);
	//mRandomizerY = std::make_unique<Randomizer>(0, WIN_HEIGHT);
	mSequence = std::make_unique<Irregular>();
}

Handler::~Handler()
{
	Assets::shutDown();
	InputManager::shutDown();
	TextureManager::shutDown();
	FactoryOfFonts::shutDown();
}

void Handler::loopBack()
{
	mSequence->init(mGame->getRenderer(), 500, mGame->getPath() / "Assets" / "photos and ttf" / "bulletV2.png", 100, 60, 6, { 200.0f,300.0f }, 30, 30, 10);
	mSequence->setAsSpecial();
	mSequence->setQuantityBulletsPerTime(3);
	mSequence->setBurstCooldown(500);

}

void Handler::actions()
{
	static int x = 0, y = 0;

	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		InputManager::getInstance().update(mGame, events);

		if (InputManager::getInstance().isMouseHeld(MouseButton::LEFT))
			mSequence->shoot({ 200,300,100,100 }, { 200,300,50,50 }, false);

		InputManager::getInstance().updatePrevStates();
    }
}

void Handler::outro()
{
    mTimer.startTimer();

	mSequence->render();
	mSequence->update(mGame->getRenderer(),{200.0f, 300.0f});
	
	mTimer.setProperFPS(16);
}

