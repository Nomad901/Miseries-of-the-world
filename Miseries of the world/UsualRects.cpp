#include "UsualRects.h"

UsualRects::UsualRects(SDL_Renderer* pRenderer)
{

	mW = 100; mH = 100;
	mPosX = 100; mPosY = 100;
	mRect = { mW, mH, mPosX, mPosY};

	mRenderer = pRenderer;

	SDL_Surface* surface = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, SDL_ALPHA_OPAQUE);
	if (!surface)
		LOG("Cant handle the surface!");
	mTexture = SDL_CreateTextureFromSurface(pRenderer,surface);
	if (!mTexture)
		LOG("Cant handle the texture!");
	SDL_FreeSurface(surface);

}

UsualRects::UsualRects(SDL_Renderer* pRenderer, const PATH& pPath)
{

	mW = 100; mH = 100;
	mPosX = 100; mPosY = 100;
	mRect = { mW, mH, mPosX, mPosY };

	mRenderer = pRenderer;

	SDL_Surface* surface = IMG_Load(pPath.string().c_str());
	if (!surface)
		LOG("Cant handle the surface!");
	mTexture = SDL_CreateTextureFromSurface(pRenderer, surface);
	if (!mTexture)
		LOG("Cant handle the texture!");
	SDL_FreeSurface(surface);

}

UsualRects::~UsualRects()
{
	if(mRenderer)
		SDL_DestroyRenderer(mRenderer);
	if (mTexture)
		SDL_DestroyTexture(mTexture);
}

void UsualRects::render()
{
	if (mTexture && mRenderer)
		SDL_RenderCopy(mRenderer, mTexture, nullptr, &mRect);
}

void UsualRects::apploadTexture(SDL_Renderer* pRenderer, const PATH& pPath)
{
	if (mTexture)
		SDL_DestroyTexture(mTexture);
	SDL_Surface* surface = IMG_Load(pPath.string().c_str());
	mTexture = SDL_CreateTextureFromSurface(pRenderer, surface);
	SDL_FreeSurface(surface);
}

void UsualRects::setDimension(const int pWidth, const int pHeight)
{
	mRect.w = pWidth; mW = pWidth;
	mRect.h = pHeight; mH = pHeight;
}

void UsualRects::setPosition(const int pPosX, const int pPosY)
{
	mRect.x = pPosX; mPosX = pPosX;
	mRect.y = pPosY; mPosY = pPosY;
}

