#include "Throwable.h"

void Throwable::initThrowable(SDL_Renderer* pRenderer, const Config::WeaponConfig& pWeaponConfig,
						      SDL_FRect pCharRect)
{
	Weapon::initWeapon(pRenderer);
	Weapon::setCharCollision(pCharRect);
	Weapon::setPaths(pWeaponConfig.mPathBullets, std::filesystem::current_path());
	mConfig.mWeaponConfig = pWeaponConfig;
}

void Throwable::setTexture(const PATH& pPath)
{
	mConfig.mWeaponConfig.mPathBullets = pPath;
}

void Throwable::setRotateFlying(bool pRotateFlying, float pMultiplier)
{
	mRotateFlying = pRotateFlying;
	mMultiplierRotate = pMultiplier;
}

void Throwable::setInFlying(bool pInFlying)
{
	mInFlying = pInFlying;
}

bool Throwable::isInFlying() const noexcept
{
	return mInFlying;
}

bool Throwable::WeaponIsInView(SDL_Rect pCharCollision)
{
	SDL_Rect tmpRect = pCharCollision;
	tmpRect.w += 50;
	tmpRect.h += 50;
	if (mObjects.areColliding(tmpRect, mFactoryObjects.convertFRect(Weapon::getCharCollisions().mWeapon)))
		return true;
	return false;
}

void Throwable::render(SDL_Renderer* pRenderer)
{
	if (!mInFlying)
	{
		SDL_RenderCopyExF(pRenderer, TextureManager::getInstance().getTexture(Weapon::getTextures().mStaticPath),
						  nullptr, &Weapon::getCharCollisions().mWeapon, mRotateMachine.getAngle(), nullptr, SDL_FLIP_NONE);
	}
	else
	{
		if (mRotateFlying)
		{
			static float tmpAngle = mRotateMachine.getAngle();
			SDL_RenderCopyExF(pRenderer, TextureManager::getInstance().getTexture(Weapon::getTextures().mStaticPath),
							  nullptr, &Weapon::getCharCollisions().mWeapon, tmpAngle + mMultiplierRotate, 
							  nullptr, SDL_FLIP_NONE);
		}
		else
		{
			SDL_RenderCopyF(pRenderer, TextureManager::getInstance().getTexture(Weapon::getTextures().mStaticPath), nullptr,
						    &Weapon::getCharCollisions().mWeapon);
		}
	}
}

void Throwable::update(const Vector2f& pPos)
{
	Weapon::setPos(pPos);
	Weapon::setPosChar(pPos);

	manageRotateAround(pPos);
}

void Throwable::manageRotateAround(const Vector2f& pPos)
{
	mRotateMachine.calculateRadians(pPos, InputManager::getInstance().getMousePos());
	SDL_FRect tmpRect = Weapon::getCharCollisions().mWeapon;
	mRotateMachine.rotateAttachedRect(tmpRect, Weapon::getCharCollisions().mChar, mRotateMachine.getAngle(),
									 { static_cast<float>(Weapon::getCharCollisions().mChar.w / 2 - 10),-5 });
	Weapon::setPos({ tmpRect.x, tmpRect.y });
}