#pragma once
#include <filesystem>

#include <SDL.h>
#include <SDL_image.h>

#include "UsualRects.h"

using PATH = std::filesystem::path;

class TouchableObjects
{
public:
	TouchableObjects(SDL_Renderer* pRenderer, const PATH& pPath);
	~TouchableObjects();

	void render();
	void update();

	void setTextureForUpdate(const PATH& pPath);
	void setDimension(const int pWidth, const int pHeight);
	void setPosition(const int pPosX, const int pPosY);
	void useTheObject() { mIsPressed = !mIsPressed; }

	SDL_Rect getRect()   const { return mRect;      }
	bool isPressed()     const { return mIsPressed; }
	int getWidth()       const { return mW;         }
	int getHeight()      const { return mH;         }
	int getPosX()        const { return mPosX;      }
	int getPosY()        const { return mPosY;      }

private:
	SDL_Renderer* mRenderer{ nullptr };
	SDL_Texture* mTexture{ nullptr };
	SDL_Rect mRect;

	PATH mPath{ std::filesystem::current_path() };
	PATH mOldPath;
	PATH mUpdating;

	bool mIsPressed{ false };

	int mPosX, mPosY;
	int mW, mH;

	void changeTexture(const PATH pPath);
};
