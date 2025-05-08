#pragma once
#include <filesystem>
#include <memory>

#include <SDL.h>
#include <SDL_image.h>

#include "Loging.h"
#include "Vector2f.h"

#define LOG(msg) Loging::log(msg, __FILE__, __LINE__)

class Textures;

class Moving
{
public:
	Moving(SDL_Renderer* pRendrer, Textures* pTextures);
	~Moving()
	{
		if(mTextures)
			delete mTextures;
	}
	void actions(const Uint8* keystate);

	float getPosX() const { return mPosition.mX; }
	float getPosY() const { return mPosition.mY; }

private:
	SDL_Renderer* mRenderer;

	Textures* mTextures;

	int mSpeed{ 5 };

	Vector2f mPosition{ 1280 / 2,720 / 2 };
};

