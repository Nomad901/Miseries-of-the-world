#include "TouchableObjects.h"

TouchableObjects::TouchableObjects(SDL_Renderer* pRenderer, const PATH& pPath)
{
	mW = 100; mH = 100;
	mPosX = 100; mPosY = 100;
	mRect = { mW, mH, mPosX, mPosY };

	mRenderer = pRenderer;
	mOldPath = pPath;

	SDL_Surface* surface = IMG_Load(pPath.string().c_str());
	if (!surface)
		LOG("Cant handle the surface!");
	mTexture = SDL_CreateTextureFromSurface(pRenderer, surface);
	if (!mTexture)
		LOG("Cant handle the texture!");
	SDL_FreeSurface(surface);
}

TouchableObjects::~TouchableObjects()
{
	if (mTexture)
		SDL_DestroyTexture(mTexture);
	if (mRenderer)
		SDL_DestroyRenderer(mRenderer);
}

void TouchableObjects::render()
{
	if (mTexture && mRenderer)
		SDL_RenderCopy(mRenderer, mTexture, nullptr, &mRect);
}

void TouchableObjects::update()
{
	if (mIsPressed)
		changeTexture(mUpdating);
	else
		changeTexture(mOldPath);
}

void TouchableObjects::setTextureForUpdate(const PATH& pPath)
{
	mUpdating = pPath;
}

void TouchableObjects::setDimension(const int pWidth, const int pHeight)
{
	mRect.w = pWidth; mW = pWidth;
	mRect.h = pHeight; mH = pHeight;
}

void TouchableObjects::setPosition(const int pPosX, const int pPosY)
{
	mRect.x = pPosX; mPosX = pPosX;
	mRect.y = pPosY; mPosY = pPosY;
}

void TouchableObjects::changeTexture(const PATH pPath)
{
	SDL_Surface* surface = IMG_Load(pPath.string().c_str());
	if (!surface)
		LOG("Cant handle the surface!");
	mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (!mTexture)
		LOG("Cant handle the texture!");
	SDL_FreeSurface(surface);
}
