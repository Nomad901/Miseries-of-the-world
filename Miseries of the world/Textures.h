#pragma once
#include <filesystem>
#include <unordered_map>
#include <memory>

#include <SDL.h>
#include <SDL_image.h>

#include "Loging.h"

#define LOG(msg) Loging::log(msg, __FILE__, __LINE__)

using PATH = std::filesystem::path;

enum class Side{UP,DOWN,LEFT,RIGHT};

class Textures
{
public:
	Textures(SDL_Renderer* pRenderer, const Side pSide);
	~Textures();

	void render();
	void update(const Side pSide);

	void setDimensions(const int pW, const int pH);
	void setPosition(const float pX, const float pY);

	inline PATH getPath()     const { return mPath; }
	inline SDL_Rect getRect() const { return mRect; }
	inline int getWidth()     const { return mW;    }
	inline int getHeight()    const { return mH;    }
	inline int getPosX()      const { return mX;    }
	inline int getPosY()      const { return mY;    }

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	SDL_Rect mRect;

	float mW, mH, mX, mY;

	std::unordered_map<Side, PATH> mStorageOfTextures;

	PATH mPath{ std::filesystem::current_path() };
};

