#pragma once
#include <iostream>
#include <string>
#include <functional>
#include <array>
#include <unordered_map>
#include <vector>

#include <SDL.h>
#include <SDL_image.h>

#include "Loging.h" 
#include "Timer.h"

#define LOG(msg) Loging::log(msg, __FILE__, __LINE__)
//#define WIN_WIDTH 1280;
//#define WIN_HEIGHT 720;

enum class Type{LOOPBACK,ACTIONS,OUTRO};

class Game
{
public:

	Game(const int pFlags, const std::string& pNameOfWindow, Uint32 pX, Uint32 pY, Uint32 pW, Uint32 pH);
	~Game() {
		SDL_DestroyRenderer(mRenderer);
		SDL_DestroyWindow(mWindow);
		IMG_Quit();
		SDL_Quit();
	}

	//enum class Type{LOOPBACK,ACTIONS,OUTRO};
	void setActions(Type pType, std::function<void(void)> pFunc);
	void startLoop();
	void stopLoop();

	void setDimensionOfWindow(const int pW, const int pH);
	void setPositionOfWindow(const int pX, const int pY);
	void setRgbOfWindow(uint8_t pR, uint8_t pG, uint8_t pB, uint8_t pA);
	void setFps(Uint32 FPS);

	std::filesystem::path getPath() const { return std::filesystem::current_path(); }
	inline int getMousePosX() const { return mMouseX; }
	inline int getMousePosY() const { return mMouseY; }
	inline int getWindowsWidth() const { return mWindowsWidth; }
	inline int getWindowsHeight() const { return mWindowsHeight; }
	inline SDL_Window* getWindow() const { return mWindow; }
	inline SDL_Renderer* getRenderer() const { return mRenderer; }
	inline SDL_bool loopIsRunning() const { return mIsRunning; }
	inline Uint32 getFPS() const { return (1000 / mDelay); }

private:
	void seter();

private:
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	SDL_Window* mWindow;
	SDL_bool mIsRunning;

	Timer mTimer;

	uint8_t mR, mG, mB, mA;
	Uint32 mWindowsWidth, mWindowsHeight;
	Uint32 mWindowsX, mWindowsY;
	float mDelay;
	int mMouseX, mMouseY;

	std::unordered_map<Type, std::function<void(void)>> mMapOfFunc;

};

