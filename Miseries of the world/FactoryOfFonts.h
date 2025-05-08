#pragma once
#include <filesystem>
#include <vector>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "Loging.h"

#define LOG(msg) Loging::log(msg, __FILE__, __LINE__)

using PATH = std::filesystem::path;

class FactoryOfFonts
{
public:
	FactoryOfFonts(SDL_Renderer* pRenderer);
	FactoryOfFonts(SDL_Renderer* pRenderer, std::string_view pText, const SDL_Color& pColor, const int pSize, const PATH& pPath);
	~FactoryOfFonts();

	void setNewFont(std::string_view pText, const SDL_Color& pColor, const int pSize, const PATH& pPath);
	void changeText(std::string_view pText, const SDL_Color& pColor, const int pSize);
	void fontIntoRect(const SDL_Rect pRect);

	void render() {
		SDL_RenderCopy(mRenderer, mTexture, nullptr, &mRect);
	}
	void update() {}

private:
	TTF_Font* mFont{ nullptr };
	SDL_Renderer* mRenderer{ nullptr };
	SDL_Texture* mTexture{ nullptr };
	SDL_Color mColor;
	SDL_Rect mRect;

	std::string mText;
	int mSize;

};

