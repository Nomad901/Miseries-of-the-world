#include "Gun.h"

bool Gun::brokenChecker(SDL_Renderer* pRenderer)
{
	if (mCurrentRobustness == 0)
	{
		Weapon::makeBroken(true);
		return true;
	}
	Weapon::makeBroken(false);
	return false;
}

bool Gun::manageShootState(SDL_Renderer* pRenderer)
{
	auto tmpAnimTexture = Weapon::getAnimatedStateMachine().getState("ShootAnimWeapon").value();
	
	if (Weapon::getWeaponStates().mShootingState &&
		!Weapon::getWeaponStates().mIsFreezed)
	{	
		if (!tmpAnimTexture.get().isAnimating())
		{
			tmpAnimTexture.get().setCurrentSide(SideOfChar::RIGHT);
			tmpAnimTexture.get().setActive(true);
			tmpAnimTexture.get().runAnimationOnlyOnce();
		}
		Weapon::getAnimatedStateMachine().render("ShootAnimWeapon", true, mRotateMachine.getAngle());
		return true;
	}
	if (tmpAnimTexture.get().isAnimating())
	{
		tmpAnimTexture.get().setActive(false);
		tmpAnimTexture.get().stopAnimation();
		tmpAnimTexture.get().nullTicks();
	}
	return false;
}

bool Gun::manageReloadState(SDL_Renderer* pRenderer)
{
	auto tmpAnimTexture = Weapon::getAnimatedStateMachine().getState("ReloadAnimWeapon").value();

	if (Weapon::getWeaponStates().mRealodingState &&
		!Weapon::getWeaponStates().mIsFreezed)
	{
		if (!tmpAnimTexture.get().isAnimating())
		{
			tmpAnimTexture.get().setCurrentSide(SideOfChar::RIGHT);
			tmpAnimTexture.get().setActive(true);
			tmpAnimTexture.get().runAnimationOnlyOnce();
		}
		Weapon::getAnimatedStateMachine().render("ReloadAnimWeapon", true, mRotateMachine.getAngle());
		return true;
	}
	if (tmpAnimTexture.get().isAnimating())
	{
		tmpAnimTexture.get().setActive(false);
		tmpAnimTexture.get().stopAnimation();
		tmpAnimTexture.get().nullTicks();
	}
	return false;
}

bool Gun::manageBrokenState(SDL_Renderer* pRenderer)
{
	if (Weapon::getWeaponStates().mIsBroken)
	{
		if (Weapon::getWeaponStates().mIsFreezed)
		{
			SDL_RenderCopyExF(pRenderer, TextureManager::getInstance().getTexture(Weapon::getTextures().mBrokenWeapon),
							  nullptr, &Weapon::getCharCollisions().mWeapon, mRotateMachine.getAngle(), nullptr,
							  InputManager::getInstance().getMousePos().mX >= Weapon::getWeaponStats().mPos.mX ?
							  SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
		}
		else
		{
			SDL_RenderCopyF(pRenderer,
						    Weapon::getWeaponStates().mIsBroken ?
						    TextureManager::getInstance().getTexture(Weapon::getTextures().mStaticPath) :
						    TextureManager::getInstance().getTexture(Weapon::getTextures().mBrokenWeapon),
						    nullptr, &Weapon::getCharCollisions().mWeapon);
		}
		return true;
	}
	return false;
}

FireModeFactory& Gun::getFireModeFactory()
{
	return mFireModeFactory;
}

void Gun::initGun(SDL_Renderer* pRenderer, SDL_FRect pCharRect,
				  int16_t pReloadingTime, bool pShowReloadingQuote,
				  SDL_Color pColorNumbers, int32_t pSizeNumbers)
{
	Weapon::initWeapon(pRenderer);
	Weapon::setCharCollision(pCharRect);
	mReloadLogic.initReloadLogic(pRenderer, pCharRect, pReloadingTime, pShowReloadingQuote, pColorNumbers, pSizeNumbers);
}

bool Gun::WeaponIsInView(SDL_Rect pCharCollision)
{
	SDL_Rect tmpRect = pCharCollision;
	tmpRect.w += 100;
	tmpRect.h += 100;
	if (mObjects.areColliding(tmpRect, TextureManager::getInstance().getRect(Weapon::getTextures().mStaticPath)))
		return true;
	return false;
}

void Gun::render(SDL_Renderer* pRenderer)
{
	mRotateMachine.calculateDegrees(Weapon::getWeaponStats().mPos, InputManager::getInstance().getMousePos());

	if (!manageBrokenState(pRenderer))
	{
		if (!manageShootState(pRenderer) &&
			!manageReloadState(pRenderer))
		{
			if (Weapon::getWeaponStates().mIsFreezed)
				SDL_RenderCopyF(pRenderer, TextureManager::getInstance().getTexture(Weapon::getTextures().mStaticPath),
							   nullptr, &Weapon::getCharCollisions().mWeapon);
			else
				SDL_RenderCopyExF(pRenderer, TextureManager::getInstance().getTexture(Weapon::getTextures().mStaticPath),
								  nullptr, &Weapon::getCharCollisions().mWeapon, mRotateMachine.getAngle(), nullptr,
								  InputManager::getInstance().getMousePos().mX >= Weapon::getWeaponStats().mPos.mX ?
								  SDL_FLIP_NONE : SDL_FLIP_VERTICAL);
		}
	}
}

void Gun::update(const Vector2f& pPos)
{
	Weapon::setPos(pPos);
	Weapon::setPosChar(pPos);
	
	manageRotateAround(pPos);

	Weapon::getAnimatedStateMachine().getState("ShootAnimWeapon").value().get().setPositionRotate(Weapon::getCharCollisions().mChar,
									  mRotateMachine.getAngle(), { static_cast<float>(Weapon::getCharCollisions().mChar.w / 2 - 10),-5 });
	Weapon::getAnimatedStateMachine().getState("ReloadAnimWeapon").value().get().setPositionRotate(Weapon::getCharCollisions().mChar,
									  mRotateMachine.getAngle(), { static_cast<float>(Weapon::getCharCollisions().mChar.w / 2 - 10),-5 });
}

void Gun::manageRotateAround(const Vector2f& pPos)
{
	mRotateMachine.calculateRadians(pPos, InputManager::getInstance().getMousePos());
	SDL_FRect tmpRect = Weapon::getCharCollisions().mWeapon;
	mRotateMachine.rotateAttachedRect(tmpRect, Weapon::getCharCollisions().mChar, mRotateMachine.getAngle(),
									{ static_cast<float>(Weapon::getCharCollisions().mChar.w / 2 - 10),-5 });
	Weapon::setPos({ tmpRect.x, tmpRect.y });
}
