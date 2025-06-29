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
#include "FireModeFactory.h"
#include "SpreadMode.h";
#include "SingleOrSequence.h";
#include "Irregular.h";
#include "BurstMode.h"

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
	mFireModeFactory = std::make_unique<FireModeFactory>();
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
	FactoryOfFonts::getInstance().appendNewFont(mGame->getRenderer(), 
					mGame->getPath() / "Assets" / "photos and ttf" / "Arial.ttf", "Mode was changed", { 255,255,255,255 }, 25);

	TextureManager::getInstance().appendTexture(mGame->getRenderer(), mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png", { 600,600, 100,100 });

	mFireModeFactory->appendMode("Spread", std::make_unique<SpreadMode>());
	mFireModeFactory->appendMode("SingleOrSequence", std::make_unique<SingleOrSequence>());
	mFireModeFactory->appendMode("Irregular", std::make_unique<Irregular>());
	mFireModeFactory->appendMode("Burst", std::make_unique<BurstMode>(mGame->getRenderer()));

	for (auto& i : mFireModeFactory->getStorageLabels())
	{
		mFireModeFactory->getMode(i).value().get().init(mGame->getRenderer(), 500,
			mGame->getPath() / "Assets" / "photos and ttf" / "bulletV2.png",
			100, 60, 6, { 200.0f,300.0f }, 30, 30, 3);
		mFireModeFactory->getMode(i).value().get().setAsSpecial();
		mFireModeFactory->getMode(i).value().get().setQuantityBullets(300);
	}

	mFireModeFactory->getExactMode<BurstMode>("Burst").value().get().loadAnim(mGame->getRenderer(),
								   TextureManager::getInstance().getPosition(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png"),
								   mGame->getPath() / "Assets" / "photos and ttf" / "BurstCharging.png",
								   mGame->getPath() / "Assets" / "photos and ttf" / "BurstDone.png");

	mFactoryObjects->appendObject("Character", { 600,600, 100,100 }, { 255,255,255,255 });
}

void Handler::actions()
{
	static int x = 0, y = 0;

	SDL_Event events;
	while (SDL_PollEvent(&events))
	{
		InputManager::getInstance().update(mGame, events);

		if (InputManager::getInstance().isPressed(SDL_SCANCODE_C))
		{
			mFont = true;
			mFireModeFactory->setMode("Burst");
		}
		if (InputManager::getInstance().isPressed(SDL_SCANCODE_V))
		{
			mFont = true;
			mFireModeFactory->setMode("Spread");
		}
		if (InputManager::getInstance().isPressed(SDL_SCANCODE_B))
		{
			mFont = true;
			mFireModeFactory->setMode("Irregular");
		}
		if (InputManager::getInstance().isPressed(SDL_SCANCODE_N))
		{
			mFont = true;
			mFireModeFactory->setMode("SingleOrSequence");
			mFireModeFactory->getExactMode<SingleOrSequence>().value().get().setMode(Mode::SEQUENCE);
			mFireModeFactory->getMode().value().get().setAsSpecial();
		}
		if (InputManager::getInstance().isPressed(SDL_SCANCODE_M))
		{
			mFont = true;
			mFireModeFactory->setMode("SingleOrSequence");
			mFireModeFactory->getExactMode<SingleOrSequence>().value().get().setMode(Mode::SINGLE);
			mFireModeFactory->getMode().value().get().setAsSpecial();
		}

		if (InputManager::getInstance().isMousePressed(MouseButton::LEFT) ||
			InputManager::getInstance().isMouseHeld(MouseButton::LEFT))
		{
			mFireModeFactory->getMode().value().get().shoot(mFactoryObjects->getRect("Character"), 
													  TextureManager::getInstance().getRect(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png"), false);
			if (mFireModeFactory->getNameCurrentMode() == "Burst")
			{
				mFireModeFactory->getExactMode<BurstMode>().value().get().setSparing(true);
			}
		}
		else if (InputManager::getInstance().isMouseReleased(MouseButton::LEFT))
		{
			if (mFireModeFactory->getNameCurrentMode() == "Burst")
			{
				mFireModeFactory->getExactMode<BurstMode>().value().get().shootChargedBullets(mFactoryObjects->getRect("Character"),
											   TextureManager::getInstance().getRect(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png"));
			}
			if (mFireModeFactory->getNameCurrentMode() == "Burst")
			{
				mFireModeFactory->getExactMode<BurstMode>().value().get().setSparing(false);
			}
		}

		Vector2f pPos = TextureManager::getInstance().getPosition(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png");
		if (InputManager::getInstance().isHeld(SDL_SCANCODE_W))
		{
			mFactoryObjects->setPosition("Character", { mFactoryObjects->getPos("Character").mX, mFactoryObjects->getPos("Character").mY - 5 });
			TextureManager::getInstance().setPosition(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png", 
				{ mFactoryObjects->getPos("Character").mX, mFactoryObjects->getPos("Character").mY - 5 });
		}
		if (InputManager::getInstance().isHeld(SDL_SCANCODE_S))
		{
			mFactoryObjects->setPosition("Character", { mFactoryObjects->getPos("Character").mX, mFactoryObjects->getPos("Character").mY + 5 });
			TextureManager::getInstance().setPosition(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png", 
				{ mFactoryObjects->getPos("Character").mX, mFactoryObjects->getPos("Character").mY + 5 });
		}
		if (InputManager::getInstance().isHeld(SDL_SCANCODE_A))
		{
			mFactoryObjects->setPosition("Character", { mFactoryObjects->getPos("Character").mX - 5, mFactoryObjects->getPos("Character").mY });
			TextureManager::getInstance().setPosition(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png",
				{ mFactoryObjects->getPos("Character").mX - 5, mFactoryObjects->getPos("Character").mY });
		}
		if (InputManager::getInstance().isHeld(SDL_SCANCODE_D))
		{
			mFactoryObjects->setPosition("Character", { mFactoryObjects->getPos("Character").mX + 5, mFactoryObjects->getPos("Character").mY });
			TextureManager::getInstance().setPosition(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png", 
				{ mFactoryObjects->getPos("Character").mX + 5, mFactoryObjects->getPos("Character").mY });
		}

		InputManager::getInstance().updatePrevStates();
    }
	if (InputManager::getInstance().isMousePressed(MouseButton::LEFT) ||
		InputManager::getInstance().isMouseHeld(MouseButton::LEFT))
	{
		mFireModeFactory->getMode().value().get().shoot(mFactoryObjects->getRect("Character"),
			TextureManager::getInstance().getRect(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png"), false);
		if (mFireModeFactory->getNameCurrentMode() == "Burst")
		{
			mFireModeFactory->getExactMode<BurstMode>().value().get().setSparing(true);
		}
	}
	else if (InputManager::getInstance().isMouseReleased(MouseButton::LEFT))
	{
		if (mFireModeFactory->getNameCurrentMode() == "Burst")
		{
			mFireModeFactory->getExactMode<BurstMode>().value().get().shootChargedBullets(mFactoryObjects->getRect("Character"),
				TextureManager::getInstance().getRect(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png"));
		}
		if (mFireModeFactory->getNameCurrentMode() == "Burst")
		{
			mFireModeFactory->getExactMode<BurstMode>().value().get().setSparing(false);
		}
	}
} 

void Handler::outro()
{
    mTimer.startTimer();
	
	mRotate.calculateDegrees(TextureManager::getInstance().getPosition(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png"),
							 InputManager::getInstance().getMousePos());
	if (InputManager::getInstance().getMousePos().mX >= TextureManager::getInstance().getPosition(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png").mX)
	{
		SDL_RenderCopyEx(mGame->getRenderer(), TextureManager::getInstance().getTexture(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png"), nullptr,
						 &TextureManager::getInstance().getRect(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png"), 
						 mRotate.getAngle(), nullptr, SDL_FLIP_NONE);
	}
	else
	{
		SDL_RenderCopyEx(mGame->getRenderer(), TextureManager::getInstance().getTexture(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png"), nullptr,
						 &TextureManager::getInstance().getRect(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png"),
						 mRotate.getAngle(), nullptr, SDL_FLIP_VERTICAL);
	}
	mFactoryObjects->render("Character", mGame->getRenderer(), false);

	mFireModeFactory->getMode().value().get().render();
	mFireModeFactory->getMode().value().get().update(mGame->getRenderer(),
													 TextureManager::getInstance().getPosition(mGame->getPath() / "Assets" / "photos and ttf" / "Shotgun.png"));
	if (mFont)
	{
		if (!mTimerForChanged.isRunning())
			mTimerForChanged.startTimer();
		else
		{
			if (mTimerForChanged.getDeltaTime(false) >= 800)
			{
				mTimerForChanged.stopTimer();
				mFont = false;
			}
		}
		FactoryOfFonts::getInstance().render("Mode was changed", mGame->getRenderer(), { WIN_WIDTH / 2, WIN_HEIGHT / 2, 300,300 });
	}

	
	mTimer.setProperFPS(1);
}

