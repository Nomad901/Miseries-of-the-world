#pragma once
#include <filesystem>

#include <SDL.h>
#include <SDL_image.h>

#include "Loging.h"

#define LOG(msg) Loging::log(msg, __FILE__, __LINE__)

using PATH = std::filesystem::path;

class UsualRects 
{
public:
	UsualRects(SDL_Renderer* pRenderer);
	UsualRects(SDL_Renderer* pRenderer, const PATH& pPath);
	~UsualRects();
	
	void render();
	void render(const float pInterpolation) {}
	// actually idk what i can update with staic rects, but i
	// will leave this alone, maybe i can create an animation of grass
	void update() {}

	void apploadTexture(SDL_Renderer* pRenderer,
						const PATH& pPath);

	void setDimension(const int pWidth, const int pHeight);
	void setPosition(const int pPosX, const int pPosY);
	
	SDL_Rect getRect() const          { return mRect; }
	int getWidth()     const		  { return mW;    }
	int getHeight()    const          { return mH;    }
	int getPosX()      const          { return mPosX; }
	int getPosY()      const          { return mPosY; }

private:
	SDL_Renderer* mRenderer{ nullptr };
	SDL_Texture* mTexture{ nullptr };
	SDL_Rect mRect;

	// Position and dimension of rectangles
	int mPosX, mPosY;
	int mW, mH;

	////for interpolation
	//float mPrev_x, mCurr_x;
};

