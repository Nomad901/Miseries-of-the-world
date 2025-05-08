#include "Moving.h"
#include "Textures.h"

Moving::Moving(SDL_Renderer* pRednerer, Textures* pTextures)
{
	mRenderer = pRednerer;
	mTextures = pTextures;
}

void Moving::actions(const Uint8* keystate)
{
	bool moved = false;
	if (keystate[SDL_SCANCODE_W])
	{
		mTextures->update(Side::UP);
		mPosition.mY -= mSpeed;
		mTextures->setPosition(mPosition.mX, mPosition.mY);
	}
	else if (keystate[SDL_SCANCODE_D])
	{
		mTextures->update(Side::RIGHT);
		mPosition.mX += mSpeed;
		mTextures->setPosition(mPosition.mX, mPosition.mY);
	}
	else if (keystate[SDL_SCANCODE_A])
	{
		mTextures->update(Side::LEFT);
		mPosition.mX -= mSpeed;
		mTextures->setPosition(mPosition.mX, mPosition.mY);
	}
	else if (keystate[SDL_SCANCODE_S])
	{
		mTextures->update(Side::DOWN);
		mPosition.mY += mSpeed;
		mTextures->setPosition(mPosition.mX, mPosition.mY);
	}

}

	//const Uint8* keystate = SDL_GetKeyboardState(NULL);
	//if (keystate[SDL_SCANCODE_W])
	//{
	//	mTextures->update(Side::UP);
	//	mPosition.mY+=5;
	//	mTextures->setPosition(mPosition.mX, mPosition.mY);
	//}
	//else if (keystate[SDL_SCANCODE_D])
	//{
	//	mTextures->update(Side::RIGHT);
	//	mPosition.mX+=5;
	//	mTextures->setPosition(mPosition.mX, mPosition.mY);
	//}
	//else if (keystate[SDL_SCANCODE_A])
	//{
	//	mTextures->update(Side::LEFT);
	//	mPosition.mX-=5;
	//	mTextures->setPosition(mPosition.mX, mPosition.mY);
	//}
	//else if (keystate[SDL_SCANCODE_S])
	//{
	//	mTextures->update(Side::DOWN);
	//	mPosition.mY+=5;
	//	mTextures->setPosition(mPosition.mX, mPosition.mY);
	//}