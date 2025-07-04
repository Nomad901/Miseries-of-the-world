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
#include "Rifle.h"
#include "Shotgun.h"
#include "Tango.h"

Handler::Handler(Game* pGame)
	:mGame(pGame),
	mInterpolation{ 0.0f }
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
	mRifle = std::make_unique<Rifle>();
	mShotgun = std::make_unique<Shotgun>();
	mTango = std::make_unique<Tango>();
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
	mFactoryObjects->appendObject("Enemy", { 800, 600, 100,100 }, { 0,0,0,255 });
	
	mTango->initTangoAutomaticaly(mGame->getRenderer(), mFactoryObjects->convertRect(mFactoryObjects->getRect("Character")));
	//mShotgun->initShotgunAutomaticaly(mGame->getRenderer(), mFactoryObjects->convertRect(mFactoryObjects->getRect("Character")));
	//mRifle->initRifleAutomaticaly(mGame->getRenderer(), RifleType::IRREGULAR, mFactoryObjects->convertRect(mFactoryObjects->getRect("Character")));
	//mPistol->initPistolAutomaticaly(mGame->getRenderer(), PistolType::FAST, mFactoryObjects->convertRect(mFactoryObjects->getRect("Character")));
}

void Handler::actions()
{
	static int x = 0, y = 0;

	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		InputManager::getInstance().update(mGame, events);

		if (InputManager::getInstance().isMouseHeld(MouseButton::LEFT) ||
			InputManager::getInstance().isMousePressed(MouseButton::LEFT))
		{
			if (mTango->getWeaponStates().mIsFreezed)
			{
				if (mTango->WeaponIsInView(mFactoryObjects->getRect("Character")))
					mTango->makeFreezed(false);
			}
			else
			{
				mTango->getFireMode().setSparing(true);
				mTango->setTangoIsCharging(true);
				mTango->getFireMode().shoot(mFactoryObjects->getRect("Character"),
											mFactoryObjects->convertFRect(mTango->getCharCollisions().mWeapon),
											mTango->getWeaponStates().mRealodingState);
			}
		}
		else if (InputManager::getInstance().isMouseReleased(MouseButton::LEFT))
		{
			if (!mTango->getWeaponStates().mIsFreezed)
			{
				mTango->shoot();
				mTango->getFireMode().setSparing(false);
				mTango->setTangoIsCharging(false);
			}
		}
		if (InputManager::getInstance().isMousePressed(MouseButton::RIGHT))
			mTango->reload();
		if (InputManager::getInstance().isPressed(SDL_SCANCODE_T))
		{
			mTango->makeFreezed(true);
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
	if (InputManager::getInstance().isMouseHeld(MouseButton::LEFT) ||
		InputManager::getInstance().isMousePressed(MouseButton::LEFT))
	{
		if (mTango->getWeaponStates().mIsFreezed)
		{
			if (mTango->WeaponIsInView(mFactoryObjects->getRect("Character")))
				mTango->makeFreezed(false);
		}
		else
		{
			mTango->getFireMode().setSparing(true);
			mTango->getFireMode().shoot(mFactoryObjects->getRect("Character"),
				mFactoryObjects->convertFRect(mTango->getCharCollisions().mWeapon),
				mTango->getWeaponStates().mRealodingState);
		}
	}
	else if (InputManager::getInstance().isMouseReleased(MouseButton::LEFT))
	{
		if (!mTango->getWeaponStates().mIsFreezed)
		{
			mTango->shoot();
			mTango->getFireMode().setSparing(false);
		}
	}
}

void Handler::outro()
{
	mTimer.startTimer();

	static int32_t tmpNumber = 100;

	mFactoryObjects->render("Character", mGame->getRenderer(), false);
	mFactoryObjects->render("Enemy", mGame->getRenderer(), false);
	
	auto tmpValue = mTango->manageDamage(mFactoryObjects->convertRect(mFactoryObjects->getRect("Enemy")));
	if (tmpValue.second)
		tmpNumber -= tmpValue.first;

	mTango->render(mGame->getRenderer());
	mTango->update(mFactoryObjects->getPos("Character"));
	mTango->updateBullets(mGame->getRenderer());
	mTango->renderCharge(mGame->getRenderer());

	mTimer.setProperFPS(1);
}

