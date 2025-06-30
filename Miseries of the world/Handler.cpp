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
	mFactoryObjects = std::make_unique<FactoryObjects>();
	//mRandomizerX = std::make_unique<Randomizer>(0, WIN_WIDTH);
	//mRandomizerY = std::make_unique<Randomizer>(0, WIN_HEIGHT);
	mPistol = std::make_unique<Pistol>();
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
	mFactoryObjects->appendObject("Character", { 600,600, 100,100 }, { 255,255,255,255 });
	
	mPistol->initGun(mGame->getRenderer(), mFactoryObjects->getRect("Character"), 3, false);
	mPistol->setAllParameteres(mFactoryObjects->getPos("Character"), 100, 50, 100, std::make_pair(0, 5), 5);
	mPistol->setPaths(mGame->getPath() / "Assets" / "photos and ttf" / "Pistol.png", mGame->getPath() / "Assets" / "photos and ttf" / "brokenPistol.png");
	mPistol->setShootPath(mGame->getPath() / "Assets" / "photos and ttf" / "PistolSh.png", 70, 50,
						 { {SideOfChar::RIGHT, {0,1,2}} }, 50, 300);
	mPistol->setReloadPath(mGame->getPath() / "Assets" / "photos and ttf" / "PistolRel.png", 70, 50,
						 { {SideOfChar::RIGHT, {0,1,2,3,4,5,6,7,8,9,10,11,12}} }, 50, 200);
}

void Handler::actions()	
{
	static int x = 0, y = 0;

	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		InputManager::getInstance().update(mGame, events);

		if (InputManager::getInstance().isMousePressed(MouseButton::LEFT))
			mPistol->makeShoot(true);
		if (InputManager::getInstance().isMousePressed(MouseButton::RIGHT))
			mPistol->makeReload(true);

		if (InputManager::getInstance().isPressed(SDL_SCANCODE_X))
		{
			mPistol->makeShoot(false);
			mPistol->makeReload(false);
		}

		if (InputManager::getInstance().isHeld(SDL_SCANCODE_W))
			mFactoryObjects->setPosition("Character", { mFactoryObjects->getPos("Character").mX, mFactoryObjects->getPos("Character").mY - 5 });
		if (InputManager::getInstance().isHeld(SDL_SCANCODE_S))
			mFactoryObjects->setPosition("Character", { mFactoryObjects->getPos("Character").mX, mFactoryObjects->getPos("Character").mY + 5 });
		if (InputManager::getInstance().isHeld(SDL_SCANCODE_A))
			mFactoryObjects->setPosition("Character", { mFactoryObjects->getPos("Character").mX - 5, mFactoryObjects->getPos("Character").mY });
		if (InputManager::getInstance().isHeld(SDL_SCANCODE_D))
			mFactoryObjects->setPosition("Character", { mFactoryObjects->getPos("Character").mX + 5, mFactoryObjects->getPos("Character").mY });
		

		InputManager::getInstance().updatePrevStates();
    }

} 

void Handler::outro()
{
    mTimer.startTimer();
	
	mFactoryObjects->render("Character", mGame->getRenderer(), false);
	
	mPistol->render(mGame->getRenderer());
	mPistol->update(mFactoryObjects->getPos("Character"));

	mTimer.setProperFPS(1);
}

