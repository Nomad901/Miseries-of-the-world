#include "Gun.h"

bool Gun::brokenChecker(SDL_Renderer* pRenderer)
{
	if (mCurrentRobustness == 0)
		return true;
	return false;
}

FireModeFactory& Gun::getFireModeFactory()
{
	return mFireModeFactory;
}

AnimateStateMachine& Gun::getAnimationStateMachine()
{
	return mAnimateStateMachine;
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
	if (!Weapon::getWeaponStates().mIsFreezed)
	{
		
	}
	else
	{
		SDL_RenderCopy(pRenderer, TextureManager::getInstance().getTexture(Weapon::getTextures().mStaticPath),
					   nullptr, &Weapon::getCharCollisions().mWeapon);
	}
}
