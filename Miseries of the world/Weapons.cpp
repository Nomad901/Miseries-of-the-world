#include "Weapons.h"

Weapons::Weapons(SDL_Renderer* pRenderer, const PATH& pPath, const WeaponType pType)
{
	mW = 100; mH = 100;
	mPosX = 100; mPosY = 100;
	mRect = { mW, mH, mPosX, mPosY };

	mRenderer = pRenderer;

	mType = pType;

	SDL_Surface* surface = IMG_Load(pPath.string().c_str());
	if (!surface)
		LOG("Cant handle the surface!");
	mTexture = SDL_CreateTextureFromSurface(pRenderer, surface);
	if (!mTexture)
		LOG("Cant handle the texture!");
	SDL_FreeSurface(surface);
}

Weapons::~Weapons()
{
	if (mRenderer)
		SDL_DestroyRenderer(mRenderer);
	if (mTexture)
		SDL_DestroyTexture(mTexture);
}

void Weapons::render()
{
	if (mTexture && mRenderer)
		SDL_RenderCopy(mRenderer, mTexture, nullptr, &mRect);
}

void Weapons::changeWeapon(const PATH& pPath, const WeaponType pType)
{
	mType = pType;
	SDL_Surface* surface = IMG_Load(pPath.string().c_str());
	if (!surface)
		LOG("Cant handle the surface!");
	mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (!mTexture)
		LOG("Cant handle the texture!");
	SDL_FreeSurface(surface);
}

void Weapons::setDimension(const int pWidth, const int pHeight)
{
	mRect.w = pWidth; mW = pWidth;
	mRect.h = pHeight; mH = pHeight;
}

void Weapons::setPosition(const int pPosX, const int pPosY)
{
	mRect.x = pPosX; mPosX = pPosX;
	mRect.y = pPosY; mPosY = pPosY;
}

SDL_bool Weapons::isHardEnough(const WeaponType pType)
{

    return SDL_bool();
}

SDL_bool Weapons::isBroken()
{
    return SDL_bool();
}

SDL_bool Weapons::fastReload()
{
    return SDL_bool();
}
