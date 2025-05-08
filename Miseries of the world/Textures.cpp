#include "Textures.h"

Textures::Textures(SDL_Renderer* pRenderer, const Side pSide)
	:mH{ 100 }, mW{ 100 }, mX{ 100 }, mY{ 100 },
	mTexture{ nullptr }
{
	mStorageOfTextures = 
	{
		{ Side::UP, mPath / "photos and ttf" / "back.png" },
		{ Side::DOWN,  mPath / "photos and ttf" / "down.png" },
		{ Side::LEFT,  mPath / "photos and ttf" / "left.png" },
		{ Side::RIGHT, mPath / "photos and ttf" / "right.png" }
	}; //TODO: maybe i can optimize this: just instead of paths send textures;
	mRenderer = pRenderer;
	mRect = { 1280/2,720/2,200,200 };
	
	auto it = mStorageOfTextures.find(pSide);
	if (it == mStorageOfTextures.end())
	{
		LOG("Couldnt find the side!");
		return;
	}

	SDL_Surface* surface = IMG_Load(it->second.string().c_str());
	if (!surface)
		LOG("Couldnt initilize the surface!");
	mTexture = SDL_CreateTextureFromSurface(pRenderer, surface);
	if(!mTexture)
		LOG("Couldnt initilize the texture!");
	SDL_FreeSurface(surface);
}

Textures::~Textures()
{
	if (mTexture)
		SDL_DestroyTexture(mTexture);
	if (mRenderer)
		SDL_DestroyRenderer(mRenderer);
}

void Textures::render()
{
	SDL_RenderCopy(mRenderer, mTexture, nullptr, &mRect);
}

void Textures::update(const Side pSide)
{
	auto it = mStorageOfTextures.find(pSide);
	if (it == mStorageOfTextures.end())
		return;
	SDL_Surface* surface = IMG_Load(it->second.string().c_str());
	if(!surface)
		LOG("Couldnt initilize the surface!");
	mTexture = SDL_CreateTextureFromSurface(mRenderer, surface);
	if (!mTexture)
		LOG("Couldnt initilize the texture!");
	SDL_FreeSurface(surface);
}

void Textures::setDimensions(const int pW, const int pH)
{
	mW = pW; mH = pH;
	mRect.w = pW; mRect.h = pH;
}

void Textures::setPosition(const float pX, const float pY)
{
	mX = pX; mY = pY;
	mRect.x = pX; mRect.y = pY;
}



